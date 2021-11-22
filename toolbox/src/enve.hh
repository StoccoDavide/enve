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
/// file: enve.hh
///

#pragma once

#ifndef INCLUDE_ENVE
#define INCLUDE_ENVE

// Print enve errors
#ifndef ENVE_ERROR
#define ENVE_ERROR(MSG)                 \
  {                                     \
    std::ostringstream os;              \
    os << MSG;                          \
    throw std::runtime_error(os.str()); \
  }
#endif

// Check for enve errors
#ifndef ENVE_ASSERT
#define ENVE_ASSERT(COND, MSG) \
  if (!(COND))                 \
  ENVE_ERROR(MSG)
#endif

#include <acme.hh>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace acme;

//! Namepaces containing all objects classes and routines
namespace enve
{

} // namespace enve

#endif

///
/// eof: enve.hh
///