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
/// file: acme_coplanar.cc
///

#include "acme_coplanar.hh"

namespace acme
{

  /*\
   |    ____            _
   |   / ___|___  _ __ | | __ _ _ __   __ _ _ __
   |  | |   / _ \| '_ \| |/ _` | '_ \ / _` | '__|
   |  | |__| (_) | |_) | | (_| | | | | (_| | |
   |   \____\___/| .__/|_|\__,_|_| |_|\__,_|_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    entity const *entity0_in,
    entity const *entity1_in,
    real          tolerance)
  {
    integer slide = entity0_in->level() * 100 + entity1_in->level();
    switch (slide)
    {

      // - - - - - - - - - - - - - - LINE - - - - - - - - - - - - - -

    case 303:
      return isCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<line const *>(entity1_in),
        tolerance);
      break;

    case 304:
      return isCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<ray const *>(entity1_in),
        tolerance);
      break;

    case 305:
      return isCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<plane const *>(entity1_in),
        tolerance);
      break;

    case 306:
      return isCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

    case 307:
      return isCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<triangle const *>(entity1_in),
        tolerance);
      break;

    case 308:
      return isCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - RAY - - - - - - - - - - - - - -

    case 403:
      return isCoplanar(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<ray const *>(entity0_in),
        tolerance);
      break;

    case 404:
      return isCoplanar(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<ray const *>(entity1_in),
        tolerance);
      break;

    case 405:
      return isCoplanar(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<plane const *>(entity1_in),
        tolerance);
      break;

    case 406:
      return isCoplanar(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

    case 407:
      return isCoplanar(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<triangle const *>(entity1_in),
        tolerance);
      break;

    case 408:
      return isCoplanar(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - PLANE - - - - - - - - - - - - - -

    case 503:
      return isCoplanar(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<plane const *>(entity0_in),
        tolerance);
      break;

    case 504:
      return isCoplanar(
        *dynamic_cast<ray const *>(entity1_in),
        *dynamic_cast<plane const *>(entity0_in),
        tolerance);
      break;

    case 505:
      return isCoplanar(
        *dynamic_cast<plane const *>(entity0_in),
        *dynamic_cast<plane const *>(entity1_in),
        tolerance);
      break;

    case 506:
      return isCoplanar(
        *dynamic_cast<plane const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

    case 507:
      return isCoplanar(
        *dynamic_cast<plane const *>(entity0_in),
        *dynamic_cast<triangle const *>(entity1_in),
        tolerance);
      break;

    case 508:
      return isCoplanar(
        *dynamic_cast<plane const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - SEGMENT - - - - - - - - - - - - - -

    case 603:
      return isCoplanar(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<segment const *>(entity0_in),
        tolerance);
      break;

    case 604:
      return isCoplanar(
        *dynamic_cast<ray const *>(entity1_in),
        *dynamic_cast<segment const *>(entity0_in),
        tolerance);
      break;

    case 605:
      return isCoplanar(
        *dynamic_cast<plane const *>(entity1_in),
        *dynamic_cast<segment const *>(entity0_in),
        tolerance);
      break;

    case 606:
      return isCoplanar(
        *dynamic_cast<segment const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

    case 607:
      return isCoplanar(
        *dynamic_cast<segment const *>(entity0_in),
        *dynamic_cast<triangle const *>(entity1_in),
        tolerance);
      break;

    case 608:
      return isCoplanar(
        *dynamic_cast<segment const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - TRIANGLE - - - - - - - - - - - - - -

    case 703:
      return isCoplanar(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<triangle const *>(entity0_in),
        tolerance);
      break;

    case 704:
      return isCoplanar(
        *dynamic_cast<ray const *>(entity1_in),
        *dynamic_cast<triangle const *>(entity0_in),
        tolerance);
      break;

    case 705:
      return isCoplanar(
        *dynamic_cast<plane const *>(entity1_in),
        *dynamic_cast<triangle const *>(entity0_in),
        tolerance);
      break;

    case 706:
      return isCoplanar(
        *dynamic_cast<segment const *>(entity1_in),
        *dynamic_cast<triangle const *>(entity0_in),
        tolerance);
      break;

    case 707:
      return isCoplanar(
        *dynamic_cast<triangle const *>(entity0_in),
        *dynamic_cast<triangle const *>(entity1_in),
        tolerance);
      break;

    case 708:
      return isCoplanar(
        *dynamic_cast<triangle const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - DISK - - - - - - - - - - - - - -

    case 803:
      return isCoplanar(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<disk const *>(entity0_in),
        tolerance);
      break;

    case 804:
      return isCoplanar(
        *dynamic_cast<ray const *>(entity1_in),
        *dynamic_cast<disk const *>(entity0_in),
        tolerance);
      break;

    case 805:
      return isCoplanar(
        *dynamic_cast<plane const *>(entity1_in),
        *dynamic_cast<disk const *>(entity0_in),
        tolerance);
      break;

    case 806:
      return isCoplanar(
        *dynamic_cast<segment const *>(entity1_in),
        *dynamic_cast<disk const *>(entity0_in),
        tolerance);
      break;

    case 807:
      return isCoplanar(
        *dynamic_cast<triangle const *>(entity1_in),
        *dynamic_cast<disk const *>(entity0_in),
        tolerance);
      break;

    case 808:
      return isCoplanar(
        *dynamic_cast<disk const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - DEFAULT - - - - - - - - - - - - - -

    default:
      // ACME_ERROR("acme::isCoplanar(entity, entity): exception not handled.\n")
      return false;
      break;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    line const &line0_in,
    line const &line1_in,
    real        tolerance)
  {
    return (line0_in.origin() - line1_in.origin()).isOrthogonal(line0_in.direction().cross(line1_in.direction()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    ray const &ray0_in,
    ray const &ray1_in,
    real       tolerance)
  {
    return (ray0_in.origin() - ray1_in.origin()).isOrthogonal(ray0_in.direction().cross(ray1_in.direction()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    plane const &plane0_in,
    plane const &plane1_in,
    real         tolerance)
  {
    return isParallel(plane0_in.normal(), plane1_in.normal(), tolerance) &&
           isApprox(plane0_in.signedDistance(plane1_in.origin()), 0.0, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    segment const &segment0_in,
    segment const &segment1_in,
    real           tolerance)
  {
    return (segment0_in.vertex(0) - segment1_in.vertex(0)).isOrthogonal(segment0_in.toUnitVector().cross(segment1_in.toUnitVector()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    triangle const &triangle0_in,
    triangle const &triangle1_in,
    real            tolerance)
  {
    return isCoplanar(triangle0_in.layingPlane(), triangle1_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    disk const &disk0_in,
    disk const &disk1_in,
    real        tolerance)
  {
    return isCoplanar(disk0_in.layingPlane(), disk1_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    line const &line_in,
    ray const  &ray_in,
    real        tolerance)
  {
    return (line_in.origin() - ray_in.origin()).isOrthogonal(line_in.direction().cross(ray_in.direction()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    line const  &line_in,
    plane const &plane_in,
    real         tolerance)
  {
    return line_in.direction().isOrthogonal(plane_in.normal(), tolerance) &&
           plane_in.normal().isOrthogonal(line_in.origin() - plane_in.origin(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    line const    &line_in,
    segment const &segment_in,
    real           tolerance)
  {
    return (line_in.origin() - segment_in.vertex(0)).isOrthogonal(line_in.direction().cross(segment_in.toUnitVector()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    line const     &line_in,
    triangle const &triangle_in,
    real            tolerance)
  {
    return isCoplanar(line_in, triangle_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    line const &line_in,
    disk const &disk_in,
    real        tolerance)
  {
    return isCoplanar(line_in, disk_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    ray const   &ray_in,
    plane const &plane_in,
    real         tolerance)
  {
    return ray_in.direction().isOrthogonal(plane_in.normal(), tolerance) &&
           plane_in.normal().isOrthogonal(ray_in.origin() - plane_in.origin(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    ray const     &ray_in,
    segment const &segment_in,
    real           tolerance)
  {
    return (ray_in.origin() - segment_in.vertex(0)).isOrthogonal(ray_in.direction().cross(segment_in.toUnitVector()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    ray const      &ray_in,
    triangle const &triangle_in,
    real            tolerance)
  {
    return isCoplanar(ray_in, triangle_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    ray const  &ray_in,
    disk const &disk_in,
    real        tolerance)
  {
    return isCoplanar(ray_in, disk_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    plane const   &plane_in,
    segment const &segment_in,
    real           tolerance)
  {
    return segment_in.toUnitVector().isOrthogonal(plane_in.normal(), tolerance) &&
           plane_in.normal().isOrthogonal(segment_in.vertex(0) - plane_in.origin(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    plane const    &plane_in,
    triangle const &triangle_in,
    real            tolerance)
  {
    return isCoplanar(plane_in, triangle_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    plane const &plane_in,
    disk const  &disk_in,
    real         tolerance)
  {
    return isCoplanar(plane_in, disk_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    segment const  &segment_in,
    triangle const &triangle_in,
    real            tolerance)
  {
    return isCoplanar(triangle_in.layingPlane(), segment_in, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    segment const &segment_in,
    disk const    &disk_in,
    real           tolerance)
  {
    return isCoplanar(disk_in.layingPlane(), segment_in, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  isCoplanar(
    triangle const &triangle_in,
    disk const     &disk_in,
    real            tolerance)
  {
    return isCoplanar(triangle_in.layingPlane(), disk_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

///
/// eof: acme_coplanar.cc
///