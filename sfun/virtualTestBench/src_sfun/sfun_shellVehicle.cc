/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Matteo Larcher, Davide Stocco and          *)
(* Enrico Bertolazzi.                                                  *)
(*                                                                     *)
(* The ENVE project and its components are supplied under the terms of *)
(* the open source BSD 2-Clause License. The contents of the ENVE      *)
(* project and its components may not be copied or disclosed except in *)
(* accordance with the terms of the BSD 2-Clause License.              *)
(*                                                                     *)
(* URL: https://opensource.org/licenses/BSD-2-Clause                   *)
(*                                                                     *)
(*    Matteo Larcher                                                   *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: matteo.larcher@unitn.it                                  *)
(*                                                                     *)
(*    Davide Stocco                                                    *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: davide.stocco@unitn.it                                   *)
(*                                                                     *)
(*    Enrico Bertolazzi                                                *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: enrico.bertolazzi@unitn.it                               *)
(*                                                                     *)
(***********************************************************************)
*/

#include "sfun_shellVehicle.hh"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

shellVehicle::shellVehicle(void)
  : m_groundFlat(point(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), 1.0)
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void
shellVehicle::init(
  const double *r_x,
  const double *m_x,
  const double *r_y,
  const double *m_y,
  const double *l_y,
  const double *size,
  const double *threshold)
{
  this->m_threshold = *threshold;
  this->m_enveShell = new enve::shell(*size, *r_x, *m_x, *r_y, *m_y, *l_y);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
shellVehicle::out(
  enve::ground::mesh *ground,
  const double (&RFw)[16],
  double (&RFpc)[16],
  double       &rho,
  double       &rho_dot,
  double       &friction,
  const double *flat_enable,
  const double *time_step)
{
  // Copy input reference frame
  acme::affine RFw_in;
  int          j = 0;
  for (int n = 0; n < 4; ++n)
  {
    for (int m = 0; m < 4; ++m)
    {
      (RFw_in.matrix())(m, n) = RFw[j];
      ++j;
    }
  }

  // ENVE computation plane
  bool in_mesh;
  if (*flat_enable != 0)
  {
    this->m_enveShell->setup(this->m_groundFlat, RFw_in);
    in_mesh = true;
  }
  else
  {
    // Update and check if there are elements under the tire shadow
    in_mesh = this->m_enveShell->setup(*ground, RFw_in, this->m_threshold, "triangle");

    if (!in_mesh)
    {
      // If no elements are detected under the tire shadows 'in_mesh' is equal to zero and a setup with a virtual plane is called
      this->m_enveShell->setup(this->m_groundFlat, RFw_in);
    }
  }

  // Update function outputs
  acme::affine RFpc_out;
  this->m_enveShell->contactPointRibAffine(RFpc_out);
  this->m_enveShell->contactDepthRib(rho, rho_dot, this->m_rho_old, *time_step);
  this->m_enveShell->contactFriction(friction);

  // Update of internal class memebers
  this->m_groundFlat.normal()   = RFpc_out.linear().col(2);
  this->m_groundFlat.origin()   = RFpc_out.translation();
  this->m_groundFlat.friction() = friction;

  // Output RF contact points
  j = 0;
  for (int n = 0; n < 4; ++n)
  {
    for (int m = 0; m < 4; ++m)
    {
      RFpc[j] = (RFpc_out.matrix())(m, n);
      ++j;
    }
  }

  return in_mesh;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
