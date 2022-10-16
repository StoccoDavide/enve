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
/// file: parallel.hxx
///

#ifndef INCLUDE_ACME_PARALLEL
#define INCLUDE_ACME_PARALLEL

#include "aabb.hxx"
#include "disk.hxx"
#include "line.hxx"
#include "orthogonal.hxx"
#include "plane.hxx"
#include "ray.hxx"
#include "segment.hxx"
#include "triangle.hxx"

namespace acme
{

  /*\
   |   ____                 _ _      _
   |  |  _ \ __ _ _ __ __ _| | | ___| |
   |  | |_) / _` | '__/ _` | | |/ _ \ |
   |  |  __/ (_| | | | (_| | | |  __/ |
   |  |_|   \__,_|_|  \__,_|_|_|\___|_|
   |
  \*/

  //! Check if geometrical entities are parallel
  bool
  IsParallel(
    entity const * entity0_in,         //!< Input entity 0
    entity const * entity1_in,         //!< Input entity 1
    real           tolerance = EPSILON //!< Tolerance
  );

  //! Check if vectors are parallel
  bool
  IsParallel(
    vec3 const & vector0_in,         //!< Input vector 0
    vec3 const & vector1_in,         //!< Input vector 1
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if vector and line are parallel
  bool
  IsParallel(
    vec3 const & vector_in,          //!< Input ray
    line const & line_in,            //!< Input vector
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if vector and ray are parallel
  bool
  IsParallel(
    vec3 const & vector_in,          //!< Input vector
    ray  const & ray_in,             //!< Input ray
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if vector and plane are parallel
  bool
  IsParallel(
    vec3  const & vector_in,          //!< Input vector
    plane const & plane_in,           //!< Input plane
    real          tolerance = EPSILON //!< Tolerance
  );

  //! Check if vector and segment are parallel
  bool
  IsParallel(
    vec3    const & vector_in,          //!< Input vector
    segment const & segment_in,         //!< Input segment
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if vector and triangle are parallel
  bool
  IsParallel(
    vec3     const & vector_in,          //!< Input vector
    triangle const & triangle_in,        //!< Input triangle
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if vector and disk are parallel
  bool
  IsParallel(
    vec3 const & vector_in,          //!< Input vector
    disk const & disk_in,            //!< Input disk
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if lines are parallel
  bool
  IsParallel(
    line const & line0_in,           //!< Input line 0
    line const & line1_in,           //!< Input line 1
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if rays are parallel
  bool
  IsParallel(
    ray const & ray0_in,            //!< Input ray 0
    ray const & ray1_in,            //!< Input ray 1
    real        tolerance = EPSILON //!< Tolerance
  );

  //! Check if planes are parallel
  bool
  IsParallel(
    plane const & plane0_in,          //!< Input plane 0
    plane const & plane1_in,          //!< Input plane 1
    real          tolerance = EPSILON //!< Tolerance
  );

  //! Check if segments are parallel
  bool
  IsParallel(
    segment const & segment0_in,        //!< Input segment 0
    segment const & segment1_in,        //!< Input segment 1
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if triangles layng planes are are parallel
  bool
  IsParallel(
    triangle const & triangle0_in,       //!< Input triangle 0
    triangle const & triangle1_in,       //!< Input triangle 1
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if disks layng planes are parallel
  bool
  IsParallel(
    disk const & disk0_in,           //!< Input disk 0
    disk const & disk1_in,           //!< Input disk 1
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and ray are parallel
  bool
  IsParallel(
    line const & line_in,            //!< Input line
    ray  const & ray_in,             //!< Input ray
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and plane are parallel
  bool
  IsParallel(
    line  const & line_in,            //!< Input line
    plane const & plane_in,           //!< Input plane
    real          tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and segment are parallel
  bool
  IsParallel(
    line    const & line_in,            //!< Input line
    segment const & segment_in,         //!< Input segment
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and triangle are parallel
  bool
  IsParallel(
    line     const & line_in,            //!< Input line
    triangle const & triangle_in,        //!< Input triangle
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and disk are parallel
  bool
  IsParallel(
    line const & line_in,            //!< Input line
    disk const & disk_in,            //!< Input disk
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if ray and plane are parallel
  bool
  IsParallel(
    ray   const & ray_in,             //!< Input ray
    plane const & plane_in,           //!< Input plane
    real          tolerance = EPSILON //!< Tolerance
  );

  //! Check if ray and segment are parallel
  bool
  IsParallel(
    ray     const & ray_in,             //!< Input ray
    segment const & segment_in,         //!< Input segment
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if ray and triangle are parallel
  bool
  IsParallel(
    ray      const & ray_in,             //!< Input ray
    triangle const & triangle_in,        //!< Input triangle
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if ray and disk are parallel
  bool
  IsParallel(
    ray  const & ray_in,             //!< Input ray
    disk const & disk_in,            //!< Input disk
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if segment and plane are parallel
  bool
  IsParallel(
    plane   const & plane_in,           //!< Input plane
    segment const & segment_in,         //!< Input segment
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if plane and triangle are parallel
  bool
  IsParallel(
    plane    const & plane_in,           //!< Input plane
    triangle const & triangle_in,        //!< Input triangle
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if plane and disk layng plane are parallel
  bool
  IsParallel(
    plane const & plane_in,           //!< Input plane
    disk  const & disk_in,            //!< Input disk
    real          tolerance = EPSILON //!< Tolerance
  );

  //! Check if segment and triangle are parallel
  bool
  IsParallel(
    segment  const & segment_in,         //!< Input segmentz
    triangle const & triangle_in,        //!< Input triangle
    real             tolerance = EPSILON //!< Tolerance
  );

  //! Check if segment and disk are parallel
  bool
  IsParallel(
    segment const & segment_in,         //!< Input segment
    disk    const & disk_in,            //!< Input disk
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if triangle and disk are parallel
  bool
  IsParallel(
    triangle const & triangle_in,        //!< Input triangle
    disk     const & disk_in,            //!< Input disk
    real             tolerance = EPSILON //!< Tolerance
  );

} // namespace acme

#endif

///
/// eof: parallel.hxx
///
