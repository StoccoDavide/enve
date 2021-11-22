/*
(***********************************************************************)
(*                                                                     *)
(* The ACME project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Enrico Bertolazzi.       *)
(*                                                                     *)
(* The ACME project and its components are supplied under the terms of *)
(* the open source BSD 2-Clause License. The contents of the ACME      *)
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
/// file: acme_collinear.cc
///

#include "acme_collinear.hh"

namespace acme
{

  /*\
   |    ____      _ _ _
   |   / ___|___ | | (_)_ __   ___  __ _ _ __
   |  | |   / _ \| | | | '_ \ / _ \/ _` | '__|
   |  | |__| (_) | | | | | | |  __/ (_| | |
   |   \____\___/|_|_|_|_| |_|\___|\__,_|_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCollinear(
    entity const *entity0_in,
    entity const *entity1_in,
    real          tolerance)
  {
    integer slide = entity0_in->level() * 100 + entity1_in->level();
    switch (slide)
    {

      // - - - - - - - - - - - - - - LINE - - - - - - - - - - - - - -

    case 303:
      return isCollinear(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<line const *>(entity1_in),
        tolerance);
      break;

    case 304:
      return isCollinear(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<ray const *>(entity1_in),
        tolerance);
      break;

    case 306:
      return isCollinear(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - RAY - - - - - - - - - - - - - -

    case 403:
      return isCollinear(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<ray const *>(entity0_in),
        tolerance);
      break;

    case 404:
      return isCollinear(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<ray const *>(entity1_in),
        tolerance);
      break;

    case 406:
      return isCollinear(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - SEGMENT - - - - - - - - - - - - - -

    case 603:
      return isCollinear(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<segment const *>(entity0_in),
        tolerance);
      break;

    case 604:
      return isCollinear(
        *dynamic_cast<ray const *>(entity1_in),
        *dynamic_cast<segment const *>(entity0_in),
        tolerance);
      break;

    case 606:
      return isCollinear(
        *dynamic_cast<segment const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - DEFAULT - - - - - - - - - - - - - -

    default:
      // ACME_ERROR("acme::isCollinear(entity, entity): exception not handled.\n")
      return false;
      break;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCollinear(
    line const &line0_in,
    line const &line1_in,
    real        tolerance)
  {
    return isParallel(line0_in.direction(), line0_in.origin() - line1_in.origin(), tolerance) &&
           isParallel(line0_in.direction(), line1_in.direction(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCollinear(
    ray const &ray0_in,
    ray const &ray1_in,
    real       tolerance)
  {
    return isParallel(ray0_in.direction(), ray0_in.origin() - ray1_in.origin(), tolerance) &&
           isParallel(ray1_in.direction(), ray1_in.direction(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCollinear(
    segment const &segment0_in,
    segment const &segment1_in,
    real           tolerance)
  {
    return isParallel(segment0_in.toUnitVector(), segment0_in.vertex(0) - segment1_in.vertex(0), tolerance) &&
           isParallel(segment0_in.toUnitVector(), segment1_in.toUnitVector(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCollinear(
    line const &line_in,
    ray const  &ray_in,
    real        tolerance)
  {
    return isParallel(line_in.direction(), line_in.origin() - ray_in.origin(), tolerance) &&
           isParallel(line_in.direction(), ray_in.direction(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCollinear(
    line const    &line_in,
    segment const &segment_in,
    real           tolerance)
  {
    return isParallel(line_in.direction(), line_in.origin() - segment_in.vertex(0), tolerance) &&
           isParallel(line_in.direction(), segment_in.toUnitVector(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCollinear(
    ray const     &ray_in,
    segment const &segment_in,
    real           tolerance)
  {
    return isParallel(ray_in.direction(), ray_in.origin() - segment_in.vertex(0), tolerance) &&
           isParallel(ray_in.direction(), segment_in.toUnitVector(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

///
/// eof: acme_collinear.cc
///