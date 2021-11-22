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

#ifndef INCLUDE_SFUN_TYPES
#define INCLUDE_SFUN_TYPES

// Structure containing the input of ENVE
typedef struct
{
  double RFw[16]; // Shell (tire) hub reference frame w.r.t. ground
} shellRF;

// Structure containing the output of ENVE
typedef struct
{
  double RFpc_ground[16]; // Contact point (Pacejka one-rib equivalent) reference frame w.r.t. ground
  double friction;        // Friction coefficient
  double rho;             // Shell (tire) penetration
  double rho_dot;         // Shell (tire) penetration velocity
  double in_mesh;         // Flag to detect if any wheel is outside the ground mesh. (0: at least one wheel is out of ground, 1: every wheels are in the ground)
} groundContact;

#endif
