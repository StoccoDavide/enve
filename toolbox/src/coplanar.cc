/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * The ACME project                                                    *
 *                                                                     *
 * Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *
 *                                                                     *
 * The ACME project and its components are supplied under the terms of *
 * the open source BSD 2-Clause License. The contents of the ACME      *
 * project and its components may not be copied or disclosed except in *
 * accordance with the terms of the BSD 2-Clause License.              *
 *                                                                     *
 * URL: https://opensource.org/licenses/BSD-2-Clause                   *
 *                                                                     *
 *    Davide Stocco                                                    *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: davide.stocco@unitn.it                                   *
 *                                                                     *
 *    Enrico Bertolazzi                                                *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: enrico.bertolazzi@unitn.it                               *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: coplanar.cc
///

#include "acme.hh"

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
  IsCoplanar(
    entity const *entity0_in,
    entity const *entity1_in,
    real          tolerance
  )
  {
    #define CMD "acme::IsCoplanar(entity, entity): "
    
    integer slide = entity0_in->level() * 100 + entity1_in->level();
    switch (slide)
    {

      // - - - - - - - - - - - - - - LINE - - - - - - - - - - - - - -

    case 303:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<line const *>(entity1_in),
        tolerance);
      break;

    case 304:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<ray const *>(entity1_in),
        tolerance);
      break;

    case 305:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<plane const *>(entity1_in),
        tolerance);
      break;

    case 306:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

    case 307:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<triangle const *>(entity1_in),
        tolerance);
      break;

    case 308:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - RAY - - - - - - - - - - - - - -

    case 403:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<ray const *>(entity0_in),
        tolerance);
      break;

    case 404:
      return IsCoplanar(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<ray const *>(entity1_in),
        tolerance);
      break;

    case 405:
      return IsCoplanar(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<plane const *>(entity1_in),
        tolerance);
      break;

    case 406:
      return IsCoplanar(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

    case 407:
      return IsCoplanar(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<triangle const *>(entity1_in),
        tolerance);
      break;

    case 408:
      return IsCoplanar(
        *dynamic_cast<ray const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - PLANE - - - - - - - - - - - - - -

    case 503:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<plane const *>(entity0_in),
        tolerance);
      break;

    case 504:
      return IsCoplanar(
        *dynamic_cast<ray const *>(entity1_in),
        *dynamic_cast<plane const *>(entity0_in),
        tolerance);
      break;

    case 505:
      return IsCoplanar(
        *dynamic_cast<plane const *>(entity0_in),
        *dynamic_cast<plane const *>(entity1_in),
        tolerance);
      break;

    case 506:
      return IsCoplanar(
        *dynamic_cast<plane const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

    case 507:
      return IsCoplanar(
        *dynamic_cast<plane const *>(entity0_in),
        *dynamic_cast<triangle const *>(entity1_in),
        tolerance);
      break;

    case 508:
      return IsCoplanar(
        *dynamic_cast<plane const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - SEGMENT - - - - - - - - - - - - - -

    case 603:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<segment const *>(entity0_in),
        tolerance);
      break;

    case 604:
      return IsCoplanar(
        *dynamic_cast<ray const *>(entity1_in),
        *dynamic_cast<segment const *>(entity0_in),
        tolerance);
      break;

    case 605:
      return IsCoplanar(
        *dynamic_cast<plane const *>(entity1_in),
        *dynamic_cast<segment const *>(entity0_in),
        tolerance);
      break;

    case 606:
      return IsCoplanar(
        *dynamic_cast<segment const *>(entity0_in),
        *dynamic_cast<segment const *>(entity1_in),
        tolerance);
      break;

    case 607:
      return IsCoplanar(
        *dynamic_cast<segment const *>(entity0_in),
        *dynamic_cast<triangle const *>(entity1_in),
        tolerance);
      break;

    case 608:
      return IsCoplanar(
        *dynamic_cast<segment const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - TRIANGLE - - - - - - - - - - - - - -

    case 703:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<triangle const *>(entity0_in),
        tolerance);
      break;

    case 704:
      return IsCoplanar(
        *dynamic_cast<ray const *>(entity1_in),
        *dynamic_cast<triangle const *>(entity0_in),
        tolerance);
      break;

    case 705:
      return IsCoplanar(
        *dynamic_cast<plane const *>(entity1_in),
        *dynamic_cast<triangle const *>(entity0_in),
        tolerance);
      break;

    case 706:
      return IsCoplanar(
        *dynamic_cast<segment const *>(entity1_in),
        *dynamic_cast<triangle const *>(entity0_in),
        tolerance);
      break;

    case 707:
      return IsCoplanar(
        *dynamic_cast<triangle const *>(entity0_in),
        *dynamic_cast<triangle const *>(entity1_in),
        tolerance);
      break;

    case 708:
      return IsCoplanar(
        *dynamic_cast<triangle const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - DISK - - - - - - - - - - - - - -

    case 803:
      return IsCoplanar(
        *dynamic_cast<line const *>(entity1_in),
        *dynamic_cast<disk const *>(entity0_in),
        tolerance);
      break;

    case 804:
      return IsCoplanar(
        *dynamic_cast<ray const *>(entity1_in),
        *dynamic_cast<disk const *>(entity0_in),
        tolerance);
      break;

    case 805:
      return IsCoplanar(
        *dynamic_cast<plane const *>(entity1_in),
        *dynamic_cast<disk const *>(entity0_in),
        tolerance);
      break;

    case 806:
      return IsCoplanar(
        *dynamic_cast<segment const *>(entity1_in),
        *dynamic_cast<disk const *>(entity0_in),
        tolerance);
      break;

    case 807:
      return IsCoplanar(
        *dynamic_cast<triangle const *>(entity1_in),
        *dynamic_cast<disk const *>(entity0_in),
        tolerance);
      break;

    case 808:
      return IsCoplanar(
        *dynamic_cast<disk const *>(entity0_in),
        *dynamic_cast<disk const *>(entity1_in),
        tolerance);
      break;

      // - - - - - - - - - - - - - - DEFAULT - - - - - - - - - - - - - -

    default:
      // ACME_ERROR(CMD "exception not handled.")
      return false;
      break;
    }

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    line const & line0_in,
    line const & line1_in,
    real         tolerance
  )
  {
    return (line0_in.origin() - line1_in.origin()).isOrthogonal(line0_in.direction().cross(line1_in.direction()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    ray const & ray0_in,
    ray const & ray1_in,
    real        tolerance
  )
  {
    return (ray0_in.origin() - ray1_in.origin()).isOrthogonal(ray0_in.direction().cross(ray1_in.direction()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    plane const & plane0_in,
    plane const & plane1_in,
    real          tolerance
  )
  {
    return IsParallel(plane0_in.normal(), plane1_in.normal(), tolerance) &&
           IsApprox(plane0_in.signedDistance(plane1_in.origin()), real(0.0), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    segment const & segment0_in,
    segment const & segment1_in,
    real            tolerance
  )
  {
    return (segment0_in.vertex(0) - segment1_in.vertex(0)).isOrthogonal(segment0_in.toUnitVector().cross(segment1_in.toUnitVector()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    triangle const & triangle0_in,
    triangle const & triangle1_in,
    real             tolerance
  )
  {
    return IsCoplanar(triangle0_in.layingPlane(), triangle1_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    disk const & disk0_in,
    disk const & disk1_in,
    real         tolerance
  )
  {
    return IsCoplanar(disk0_in.layingPlane(), disk1_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    line const & line_in,
    ray  const & ray_in,
    real         tolerance
  )
  {
    return (line_in.origin() - ray_in.origin()).isOrthogonal(line_in.direction().cross(ray_in.direction()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    line  const & line_in,
    plane const & plane_in,
    real          tolerance
  )
  {
    return line_in.direction().isOrthogonal(plane_in.normal(), tolerance) &&
           plane_in.normal().isOrthogonal(line_in.origin() - plane_in.origin(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    line    const & line_in,
    segment const & segment_in,
    real            tolerance
  )
  {
    return (line_in.origin() - segment_in.vertex(0)).isOrthogonal(line_in.direction().cross(segment_in.toUnitVector()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    line     const & line_in,
    triangle const & triangle_in,
    real             tolerance
  )
  {
    return IsCoplanar(line_in, triangle_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    line const & line_in,
    disk const & disk_in,
    real         tolerance
  )
  {
    return IsCoplanar(line_in, disk_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    ray   const & ray_in,
    plane const & plane_in,
    real          tolerance
  )
  {
    return ray_in.direction().isOrthogonal(plane_in.normal(), tolerance) &&
           plane_in.normal().isOrthogonal(ray_in.origin() - plane_in.origin(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    ray     const & ray_in,
    segment const & segment_in,
    real            tolerance
  )
  {
    return (ray_in.origin() - segment_in.vertex(0)).isOrthogonal(ray_in.direction().cross(segment_in.toUnitVector()), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    ray      const & ray_in,
    triangle const & triangle_in,
    real             tolerance
  )
  {
    return IsCoplanar(ray_in, triangle_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    ray  const & ray_in,
    disk const & disk_in,
    real         tolerance
  )
  {
    return IsCoplanar(ray_in, disk_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    plane   const & plane_in,
    segment const & segment_in,
    real            tolerance
  )
  {
    return segment_in.toUnitVector().isOrthogonal(plane_in.normal(), tolerance) &&
           plane_in.normal().isOrthogonal(segment_in.vertex(0)-plane_in.origin(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    plane    const & plane_in,
    triangle const & triangle_in,
    real             tolerance
  )
  {
    return IsCoplanar(plane_in, triangle_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    plane const & plane_in,
    disk  const & disk_in,
    real          tolerance
  )
  {
    return IsCoplanar(plane_in, disk_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    segment  const & segment_in,
    triangle const & triangle_in,
    real             tolerance
  )
  {
    return IsCoplanar(triangle_in.layingPlane(), segment_in, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    segment const & segment_in,
    disk    const & disk_in,
    real            tolerance
  )
  {
    return IsCoplanar(disk_in.layingPlane(), segment_in, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  IsCoplanar(
    triangle const & triangle_in,
    disk     const & disk_in,
    real             tolerance
  )
  {
    return IsCoplanar(triangle_in.layingPlane(), disk_in.layingPlane(), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

///
/// eof: coplanar.cc
///
