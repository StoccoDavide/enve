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

#pragma once

#ifndef INCLUDE_SFUN_INTEREFACE
#define INCLUDE_SFUN_INTEREFACE

#include <stdlib.h>

#include <iostream>

#include "enve.hh"
#include "enve_flat.hh"
#include "enve_mesh.hh"
#include "enve_shell.hh"

#include "sfun_shellVehicle.hh"
#include "sfun_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

  // Function initializes a ENVE shell object
  void
  sfun_init(
    const double *r_x, // Shell radius on x axis (m)
    const double *m_x, // Shell curve degree for x axis
    const double *r_y, // Shell radius on y axis (m)
    const double *m_y, // Shell curve degree for y axis
    const double *l_y, // Surface half width on y axis (m)
    const double *size // Ribs number
  );

  // Library entry point for step update: update ENVE computation for the one shell (tire)
  void
  sfun_out(
    const shellRF *input,      // Input bus containing the shell reference frame
    groundContact *output,     // Output bus containing the contact point reference frame
    const double  *method,     // method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
    const double  *flat_enable // flat_enable 0: ENVE use ground::mesh (RDF), 1: ENVE use ground::flat
  );

  // Library entry point for delete the allocated memory
  void
  sfun_end(void);

  // Library entry point for delete the allocated memory for shell object
  void
  sfun_destroy_shell(
    void *shell_sf // Shell object pointer to be deleted
  );

  // Library entry point for delete the allocated memory for ground object
  void
  sfun_destroy_ground(
    void *ground_sf // Ground object pointer to be deleted
  );

#ifdef __cplusplus
}
#endif

#endif
