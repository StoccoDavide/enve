/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Enrico Bertolazzi.       *)
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
(*    Enrico Bertolazzi                                                *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: enrico.bertolazzi@unitn.it                               *)
(*                                                                     *)
(***********************************************************************)
*/

///
/// file: enve_output.hh
///

#pragma once

#ifndef INCLUDE_ENVE_OUTPUT
#define INCLUDE_ENVE_OUTPUT

#include <acme.hh>
#include <acme_point.hh>

#include "enve.hh"

using namespace acme;

namespace enve
{

  /*\
   |               _               _   
   |    ___  _   _| |_ _ __  _   _| |_ 
   |   / _ \| | | | __| '_ \| | | | __|
   |  | (_) | |_| | |_| |_) | |_| | |_ 
   |   \___/ \__,_|\__| .__/ \__,_|\__|
   |                  |_|              
  \*/

  struct output {
    point point    = NAN_POINT; //!< Contact points vector
    vec3  normal   = NAN_VEC3;  //!< Contact normal unit vectors
    real  friction = QUIET_NAN; //!< Contact friction
    real  depth    = QUIET_NAN; //!< Contact depth 
    real  area     = QUIET_NAN; //!< Contact area
    real  volume   = QUIET_NAN; //!< Contact volume
  }; // struct output

} // namespace enve

#endif

///
/// file: enve_output.hh
///