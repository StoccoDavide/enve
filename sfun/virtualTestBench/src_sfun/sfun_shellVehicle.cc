/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020, Davide Stocco, Matteo Larcher and Enrico        *)
(* Bertolazzi.                                                         *)
(*                                                                     *)
(* The ENVE project and its components are supplied under the terms of *)
(* the open source BSD 2-Clause License. The contents of the ENVE      *)
(* project and its components may not be copied or disclosed except in *)
(* accordance with the terms of the BSD 2-Clause License.              *)
(*                                                                     *)
(* URL: https://opensource.org/licenses/BSD-2-Clause                   *)
(*                                                                     *)
(*    Davide Stocco                                                    *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: davide.stocco@unitn.it                                   *)
(*                                                                     *)
(*    Matteo Larcher                                                   *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: matteo.larcher@unitn.it                                  *)
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
  const double *size,
  const double *r_x,
  const double *m_x,
  const double *r_y,
  const double *m_y,
  const double *l_y
)
{
  this->m_enveShell = new enve::shell(*size, *r_x, *m_x, *r_y, *m_y, *l_y);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

bool
shellVehicle::out(
  enve::ground::mesh *groundMesh,
  const double      (&RFw)[16],
  const double       *method,
  double            (&RFpc)[16],
  double             &rho,
  double             &friction,
  const double       *flat_enable
)
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

  // Extract enveloping method
  std::string method_in;
  if (*method == 0)
    method_in = "geometric";
  else if (*method == 1)
    method_in = "sampling";
  else
    method_in = "none";


  // ENVE computation plane
  bool in_mesh;
  if (*flat_enable != 0)
  {
    this->m_enveShell->setup(this->m_groundFlat, RFw_in, method_in);
    in_mesh = true;
  }
  else
  {
    // Update and check if there are elements under the tire shadow
    in_mesh = this->m_enveShell->setup(*groundMesh, RFw_in, method_in);

    if (!in_mesh)
    {
      // If no elements are detected under the tire shadows 'in_mesh' is equal to zero and a setup with a virtual plane is called
      this->m_enveShell->setup(this->m_groundFlat, RFw_in, method_in);
    }
  }

  // Update function outputs
  acme::affine RFpc_out;
  this->m_enveShell->contactPointAffine(RFpc_out);
  this->m_enveShell->contactDepth(rho);
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
