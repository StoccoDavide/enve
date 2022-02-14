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

#pragma once

#ifndef INCLUDE_SFUN_SHELLVEHICLE
#define INCLUDE_SFUN_SHELLVEHICLE

#include "acme.hh"

#include "enve.hh"
#include "enve_flat.hh"
#include "enve_mesh.hh"
#include "enve_shell.hh"

#include "sfun_interface.h"

class shellVehicle
{
private:
  enve::shell       *m_enveShell;  // Tire object used by TireGround
  enve::ground::flat m_groundFlat; // Ground flat object pointer

public:
  // Default class constructor
  shellVehicle(void);

  // Function initializes virtual plane and tire model for one tire
  void
  init(
    const double *size,        // Ribs number
    const double *r_x,         // Shell radius on x axis (m)
    const double *m_x,         // Shell curve degree for x axis
    const double *r_y,         // Shell radius on y axis (m)
    const double *m_y,         // Shell curve degree for y axis
    const double *l_y,         // Surface half width on y axis (m)
    const double *flatHeight,  // Flat ground surface height (m)
    const double *flatFriction // Flat ground surface friction scaling coefficient (-)
  );

  // Function outputs the computation of ENVE for one tire, including logic for out-mesh conditions.
  // If there are no triangles under the tire shadow, ENVE will work with a virtual plane created from the last contact point
  bool
  out(
    enve::ground::mesh *ground,     // Ground object
    const double      (&RFw)[16],   // Wheel hub reference frame
    const double       *method,     // method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
    double            (&RFpc)[16],  // Contact point reference frame
    double             &rho,        // Shell penetration (m)
    double             &friction,   // Friction coefficient
    const double       *flat_enable // flat_enable 0: ENVE use ground::mesh (RDF), 1: ENVE use ground::flat
  );
};

#endif
