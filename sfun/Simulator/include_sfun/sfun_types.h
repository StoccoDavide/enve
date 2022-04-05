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

#ifndef INCLUDE_SFUN_TYPES
#define INCLUDE_SFUN_TYPES

// Structure containing the input of ENVE
typedef struct
{
  double RFw_rr[16]; // Rear-Right shell (tire) hub reference frame w.r.t. ground
  double RFw_rl[16]; // Rear-Left shell (tire) hub reference frame w.r.t. ground
  double RFw_fr[16]; // Front-Right shell (tire) hub reference frame w.r.t. ground
  double RFw_fl[16]; // Front-Left shell (tire) hub reference frame w.r.t. ground
} shellsRF;

// Structure containing the output of ENVE
typedef struct
{
  double RFpc_rr_ground[16]; // Rear-Right contact point (Pacejka one-rib equivalent) reference frame w.r.t. ground
  double RFpc_rl_ground[16]; // Rear-Left contact point (Pacejka one-rib equivalent) reference frame w.r.t. ground
  double RFpc_fr_ground[16]; // Front-Right contact point (Pacejka one-rib equivalent) reference frame w.r.t. ground
  double RFpc_fl_ground[16]; // Front-Left contact point (Pacejka one-rib equivalent) reference frame w.r.t. ground
  double friction_rr;        // Rear-Right friction coefficient
  double friction_rl;        // Rear-Left friction coefficient
  double friction_fr;        // Front-Right friction coefficient
  double friction_fl;        // Front-Left friction coefficient
  double rho_rr;             // Rear-Right shell (tire) penetration
  double rho_rl;             // Rear-Left shell (tire) penetration
  double rho_fr;             // Front-Right shell (tire) penetration
  double rho_fl;             // Front-Left shell (tire) penetration
  double rho_dot_rr;         // Rear-Right shell (tire) penetration velocity
  double rho_dot_rl;         // Rear-Left shell (tire) penetration velocity
  double rho_dot_fr;         // Front-Right shell (tire) penetration velocity
  double rho_dot_fl;         // Front-Left shell (tire) penetration velocity
  double in_mesh;            // Flag to detect if any wheel is outside the ground mesh. (0: at least one wheel is out of ground, 1: every wheels are in the ground)
} groundContact;

#endif
