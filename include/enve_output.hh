/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *)
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
    acme::point point    = acme::NAN_POINT; //!< Contact points vector
    acme::vec3  normal   = acme::NAN_VEC3;  //!< Contact normal unit vectors
    acme::real  friction = acme::QUIET_NAN; //!< Contact friction
    acme::real  depth    = acme::QUIET_NAN; //!< Contact depth 
    acme::real  area     = acme::QUIET_NAN; //!< Contact area
    acme::real  volume   = acme::QUIET_NAN; //!< Contact volume
  }; // struct output

} // namespace enve

#endif

///
/// file: enve_output.hh
///