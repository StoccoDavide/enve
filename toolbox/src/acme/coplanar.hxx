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
/// file: coplanar.hxx
///

#ifndef INCLUDE_ACME_COPLANAR
#define INCLUDE_ACME_COPLANAR

#include "aabb.hxx"
#include "disk.hxx"
#include "line.hxx"
#include "parallel.hxx"
#include "plane.hxx"
#include "ray.hxx"
#include "segment.hxx"
#include "triangle.hxx"

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

  //! Check if entitys are coplanar
  bool
  IsCoplanar(
    entity const * entity0_in,         //!< Input entity 0
    entity const * entity1_in,         //!< Input entity 1
    real           tolerance = EPSILON //!< Tolerance
  );

  //! Check if lines are coplanar
  bool
  IsCoplanar(
    line const & line0_in,           //!< Input line 0
    line const & line1_in,           //!< Input line 1
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if rays are coplanar
  bool
  IsCoplanar(
    ray const & ray0_in,            //!< Input ray 0
    ray const & ray1_in,            //!< Input ray 1
    real        tolerance = EPSILON //!< Tolerance
  );

  //! Check if planes are coplanar
  bool
  IsCoplanar(
    plane const & plane0_in,          //!< Input plane 0
    plane const & plane1_in,          //!< Input plane 1
    real          tolerance = EPSILON //!< Tolerance
  );

  //! Check if segments are coplanar
  bool
  IsCoplanar(
    segment const & segment0_in,        //!< Input segment 0
    segment const & segment1_in,        //!< Input segment 1
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if triangles layng planes are are coplanar
  bool
  IsCoplanar(
    triangle const & triangle0_in,       //!< Input triangle 0
    triangle const & triangle1_in,       //!< Input triangle 1
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if disks layng planes are coplanar
  bool
  IsCoplanar(
    disk const & disk0_in,           //!< Input disk 0
    disk const & disk1_in,           //!< Input disk 1
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and ray are coplanar
  bool
  IsCoplanar(
    line const & line_in,            //!< Input line
    ray  const & ray_in,             //!< Input ray
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and plane are coplanar
  bool
  IsCoplanar(
    line  const & line_in,            //!< Input line
    plane const & plane_in,           //!< Input plane
    real          tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and segment are coplanar
  bool
  IsCoplanar(
    line    const & line_in,            //!< Input line
    segment const & segment_in,         //!< Input segment
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and tringle laying plane are coplanar
  bool
  IsCoplanar(
    line     const & line_in,            //!< Input line
    triangle const & triangle_in,        //!< Input triangle
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and disk are coplanar
  bool
  IsCoplanar(
    line const & line_in,            //!< Input line
    disk const & disk_in,            //!< Input disk
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if ray and plane are coplanar
  bool
  IsCoplanar(
    ray   const & ray_in,             //!< Input ray
    plane const & plane_in,           //!< Input plane
    real          tolerance = EPSILON //!< Tolerance
  );

  //! Check if ray and segment are coplanar
  bool
  IsCoplanar(
    ray     const & ray_in,             //!< Input ray
    segment const & segment_in,         //!< Input segment
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if ray and triangle are coplanar
  bool
  IsCoplanar(
    ray      const & ray_in,             //!< Input ray
    triangle const & triangle_in,        //!< Input triangle
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if ray and disk are coplanar
  bool
  IsCoplanar(
    ray  const & ray_in,             //!< Input ray
    disk const & disk_in,            //!< Input disk
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if segment and plane are coplanar
  bool
  IsCoplanar(
    plane   const & plane_in,           //!< Input plane
    segment const & segment_in,         //!< Input segment
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if plane and triangle are coplanar
  bool
  IsCoplanar(
    plane    const & plane_in,           //!< Input plane
    triangle const & triangle_in,        //!< Input triangle
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if plane and disk layng plane are coplanar
  bool
  IsCoplanar(
    plane const & plane_in,           //!< Input plane
    disk  const & disk_in,            //!< Input disk
    real          tolerance = EPSILON //!< Tolerance
  );

  //! Check if segment and triangle are coplanar
  bool
  IsCoplanar(
    segment  const & segment_in,         //!< Input segment
    triangle const & triangle_in,        //!< Input triangle
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if segment and disk are coplanar
  bool
  IsCoplanar(
    segment const & segment_in,         //!< Input segment
    disk    const & disk_in,            //!< Input disk
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if triangle and disk are coplanar
  bool
  IsCoplanar(
    triangle const & triangle_in,        //!< Input triangle
    disk     const & disk_in,            //!< Input disk
    real             tolerance = EPSILON //!< Tolerance
  );

} // namespace acme

#endif

///
/// eof: coplanar.hxx
///
