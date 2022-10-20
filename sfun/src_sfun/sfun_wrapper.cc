/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * This file is part of the ENVE project.                              *
 *                                                                     *
 * Copyright (c) 2022, Davide Stocco. All rights reserved.             *
 *                                                                     *
 * The ENVE project can not be copied and/or distributed without       *
 * the express permission of Davide Stocco.                            *
 *                                                                     *
 *    Davide Stocco                                                    *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: davide.stocco@unitn.it                                   *
 *                                                                     *
 *    Matteo Larcher                                                   *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: matteo.larcher@unitn.it                                  *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: sfun_wrapper.cc
///

#include "sfun_wrapper.hh"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

ShellVehicle::ShellVehicle(void)
  : m_flat(1.0, point(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0))
{
  this->m_shell = nullptr;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void
ShellVehicle::init(
  const double *size,
  const double *r_x,
  const double *m_x,
  const double *r_y,
  const double *m_y,
  const double *l_y,
  const double *flat_height,
  const double *flat_friction
)
{
  // Shell update
  this->m_shell = new enve::shell(*size, *r_x, *m_x, *r_y, *m_y, *l_y);

  // Flat update
  this->m_flat.origin()   = point(0.0, 0.0, *flat_height);
  this->m_flat.friction() = *flat_friction;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
ShellVehicle::out(
    enve::ground::mesh *ground,
    const double      (&hub_affine)[16],
    const double       *method,
    double            (&shell_affine)[16],
    double             &shell_rho,
    double             &shell_friction,
    double            (&ribs_affine)[16*MAX_RIBS],
    double            (&ribs_rho)[MAX_RIBS],
    double            (&ribs_friction)[MAX_RIBS],
    const double       *flat_enable
)
{
  // Store temporaries
  int size = this->m_shell->size();

  // Copy input shell hub reference frame
  acme::affine tmp_affine;
  for (int n = 0; n < 4; ++n)
  {
    for (int m = 0; m < 4; ++m)
    {
      (tmp_affine.matrix())(n,m) = hub_affine[m+4*n];
    }
  }

  // Extract enveloping method
  std::string method_in;
  if (*method == 0)
    {method_in = "geometric";}
  else if (*method == 1)
    {method_in = "sampling";}
  else
    {method_in = "none";}

  // Use back-up plane for setup routine
  bool in_mesh;
  if (*flat_enable != 0)
  {
    this->m_shell->setup(this->m_flat, tmp_affine, method_in);
    in_mesh = true;
  }
  else
  {
    // Update and check if shell is in mesh
    in_mesh = this->m_shell->setup(*ground, tmp_affine, method_in);

    // If no elements are detected under the tire shadows 'in_mesh = 0'
    // and a setup with the back-up plane is called
    if (!in_mesh)
      {this->m_shell->setup(this->m_flat, tmp_affine, method_in);}
  }

  // Update shell outputs
  this->m_shell->contactPointAffine(tmp_affine);
  this->m_shell->contactDepth(shell_rho);
  this->m_shell->contactFriction(shell_friction);

  for (int n = 0; n < 4; ++n)
  {
    for (int m = 0; m < 4; ++m)
    {
      shell_affine[m+4*n] = (tmp_affine.matrix())(n,m);
    }
  }

  // Update of internal class memebers
  this->m_flat.normal()   = tmp_affine.linear().col(2);
  this->m_flat.origin()   = tmp_affine.translation();
  this->m_flat.friction() = shell_friction;

  // Update ribs outputs
  for (int i = 0; i < MAX_RIBS; ++i)
  {
    if (i < size)
    {
      this->m_shell->contactPointAffine(i, tmp_affine);
      this->m_shell->contactDepth(i, ribs_rho[i]);
      this->m_shell->contactFriction(i, ribs_friction[i]);
      for (int n = 0; n < 4; ++n)
      {
        for (int m = 0; m < 4; ++m)
        {
          ribs_affine[m+4*n+16*i] = (tmp_affine.matrix())(n,m);
        }
      }
    }
    else
    {
      tmp_affine.matrix() = acme::NAN_MAT4;
      ribs_rho[i]         = acme::QUIET_NAN;
      ribs_friction[i]    = acme::QUIET_NAN;
      for (int n = 0; n < 4; ++n)
      {
        for (int m = 0; m < 4; ++m)
        {
          ribs_affine[m+4*n+16*i] = (tmp_affine.matrix())(n,m);
        }
      }
    }
  }

  // Retun if shell in on mesh
  return in_mesh;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

///
/// eof: sfun_wrapper.cc
///
