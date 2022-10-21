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
/// file: intersection.hxx
///

#pragma once
#ifndef INCLUDE_ACME_Intersection_HXX
#define INCLUDE_ACME_Intersection_HXX

#include "aabb.hxx"
#include "ball.hxx"
#include "collinear.hxx"
#include "coplanar.hxx"
#include "disk.hxx"
#include "line.hxx"
#include "none.hxx"
#include "plane.hxx"
#include "ray.hxx"
#include "segment.hxx"
#include "triangle.hxx"

namespace acme
{

  /*\
   |   ___       _                          _   _
   |  |_ _|_ __ | |_ ___ _ __ ___  ___  ___| |_(_) ___  _ __
   |   | || '_ \| __/ _ \ '__/ __|/ _ \/ __| __| |/ _ \| '_ \
   |   | || | | | ||  __/ |  \__ \  __/ (__| |_| | (_) | | | |
   |  |___|_| |_|\__\___|_|  |___/\___|\___|\__|_|\___/|_| |_|
   |
  \*/

  //! Intersection between two geometrical entities
  entity *
  Intersection(
    entity const * entity0_in,         //!< Input entity 0
    entity const * entity1_in,         //!< Input entity 1
    real           tolerance = EPSILON //!< Tolerance
  );

  /*\
   |   ____                   _               _
   |  |  _ \ _   _ _ __   ___| |_ _   _  __ _| |
   |  | |_) | | | | '_ \ / __| __| | | |/ _` | |
   |  |  __/| |_| | | | | (__| |_| |_| | (_| | |
   |  |_|    \__,_|_| |_|\___|\__|\__,_|\__,_|_|
   |
  \*/

  //! Intersection between two points
  bool
  Intersection(
    point const & point0_in,               //!< Input point 0
    point const & point1_in,               //!< Input point 1
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection between point and line
  bool
  Intersection(
    point const & point_in,                //!< Input point
    line  const & line_in,                 //!< Input line
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection between point and ray
  bool
  Intersection(
    point const & point_in,                //!< Input point
    ray   const & ray_in,                  //!< Input ray
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection between point and plane
  bool
  Intersection(
    point const & point_in,                //!< Input point
    plane const & plane_in,                //!< Input plane
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection between point and segment
  bool
  Intersection(
    point   const & point_in,                //!< Input point
    segment const & segment_in,              //!< Input segment
    point         & point_out = DUMMY_POINT, //!< Output point
    real            tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection between point and triangle
  bool
  Intersection(
    point    const & point_in,                //!< Input point
    triangle const & triangle_in,             //!< Input triangle
    point          & point_out = DUMMY_POINT, //!< Output point
    real             tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection between point and disk
  bool
  Intersection(
    point const & point_in,                //!< Input point
    disk  const & disk_in,                 //!< Input disk
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  /*\
   |    ____      _ _ _
   |   / ___|___ | | (_)_ __   ___  __ _ _ __
   |  | |   / _ \| | | | '_ \ / _ \/ _` | '__|
   |  | |__| (_) | | | | | | |  __/ (_| | |
   |   \____\___/|_|_|_|_| |_|\___|\__,_|_|
   |
  \*/

  //! Intersection between two lines \n
  //! WARNING: This function only support collinear objects!
  bool
  Intersection(
    line const & line0_in,               //!< Input line 0
    line const & line1_in,               //!< Input line 1
    line       & line_out  = DUMMY_LINE, //!< Output line
    real         tolerance = EPSILON     //!< Tolerance
  );

  //! Intersection between two rays \n
  //! WARNING: This function only support collinear objects!
  bool
  Intersection(
    ray  const & ray0_in,               //!< Input ray 0
    ray  const & ray1_in,               //!< Input ray 1
    ray        & ray_out   = DUMMY_RAY, //!< Output ray
    real         tolerance = EPSILON    //!< Tolerance
  );

  //! Intersection between two opposite rays \n
  //! WARNING: This function only support collinear objects!
  bool
  Intersection(
    ray     const & ray0_in,                     //!< Input ray 0
    ray     const & ray1_in,                     //!< Input ray 1
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection between two segments \n
  //! WARNING: This function only support collinear objects!
  bool
  Intersection(
    segment const & segment0_in,                 //!< Input segment 0
    segment const & segment1_in,                 //!< Input segment 1
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection between line and ray \n
  //! WARNING: This function only support collinear objects!
  bool
  Intersection(
    line const & line_in,               //!< Input line
    ray  const & ray_in,                //!< Input ray
    ray        & ray_out   = DUMMY_RAY, //!< Output ray
    real         tolerance = EPSILON    //!< Tolerance
  );

  //! Intersection between line and segment \n
  //! WARNING: This function only support collinear objects!
  bool
  Intersection(
    line    const & line_in,                     //!< Input line
    segment const & segment_in,                  //!< Input segment
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection between ray and segment \n
  //! WARNING: This function only support collinear objects!
  bool
  Intersection(
    ray     const & ray_in,                      //!< Input ray
    segment const & segment_in,                  //!< Input segment
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  /*\
   |    ____                      _
   |   / ___| ___ _ __   ___ _ __(_) ___
   |  | |  _ / _ \ '_ \ / _ \ '__| |/ __|
   |  | |_| |  __/ | | |  __/ |  | | (__
   |   \____|\___|_| |_|\___|_|  |_|\___|
   |
  \*/

  //! Intersection between two lines \n
  //! WARNING: This function does not support collinear objects!
  bool
  Intersection(
    line  const & line0_in,                //!< Input line 0
    line  const & line1_in,                //!< Input line 1
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection between two rays \n
  //! WARNING: This function does not support collinear objects!
  bool
  Intersection(
    ray   const & ray0_in,                 //!< Input ray 0
    ray   const & ray1_in,                 //!< Input ray 1
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection between two segments \n
  //! WARNING: This function does not support collinear objects!
  bool
  Intersection(
    segment const & segment0_in,             //!< Input segment 0
    segment const & segment1_in,             //!< Input segment 1
    point         & point_out = DUMMY_POINT, //!< Output point
    real            tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection line with ray \n
  //! WARNING: This function does not support collinear objects!
  bool
  Intersection(
    line  const & line_in,                 //!< Input line
    ray   const & ray_in,                  //!< Input ray
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection line with segment  \n
  //! WARNING: This function does not support collinear objects!
  bool
  Intersection(
    line    const & line_in,                 //!< Input line
    segment const & segment,                 //!< Input segment
    point         & point_out = DUMMY_POINT, //!< Output point
    real            tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection ray with segment \n
  //! WARNING: This function does not support collinear objects!
  bool
  Intersection(
    ray     const & ray_in,                  //!< Input ray
    segment const & segment,                 //!< Input segment
    point         & point_out = DUMMY_POINT, //!< Output point
    real            tolerance = EPSILON      //!< Tolerance
  );

  /*\
   |    ____            _
   |   / ___|___  _ __ | | __ _ _ __   __ _ _ __
   |  | |   / _ \| '_ \| |/ _` | '_ \ / _` | '__|
   |  | |__| (_) | |_) | | (_| | | | | (_| | |
   |   \____\___/| .__/|_|\__,_|_| |_|\__,_|_|
   |             |_|
  \*/

  //! Intersection between planes \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    plane const & plane0_in,               //!< Input plane 0
    plane const & plane1_in,               //!< Input plane 1
    plane       & plane_out = DUMMY_PLANE, //!< Output plane
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection triangle with disk \n
  //! WARNING: This function not supported!
  bool
  Intersection(
    triangle const & triangle0_in,           //!< Input triangle
    triangle const & triangle1_in,           //!< Input triangle
    none           & none_out  = DUMMY_NONE, //!< Output none
    real             tolerance = EPSILON     //!< Tolerance
  );

  //! Intersection triangle with disk \n
  //! WARNING: This function not supported!
  bool
  Intersection(
    disk const & disk0_in,               //!< Input disk
    disk const & disk1_in,               //!< Input disk
    none       & none_out  = DUMMY_NONE, //!< Output none
    real         tolerance = EPSILON     //!< Tolerance
  );

  //! Intersection line with plane \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    line  const & line_in,                //!< Input line
    plane const & plane_in,               //!< Input plane
    line        & line_out  = DUMMY_LINE, //!< Output line
    real          tolerance = EPSILON     //!< Tolerance
  );

  //! Intersection line with triangle \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    line     const & line_in,                     //!< Input line
    triangle const & triangle_in,                 //!< Input triangle
    segment        & segment_out = DUMMY_SEGMENT, //!< Output segment
    real             tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection line with disk \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    line    const & line_in,                     //!< Input line
    disk    const & disk_in,                     //!< Input disk
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection ray with plane \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    ray   const & ray_in,                //!< Input ray
    plane const & plane_in,              //!< Input plane
    ray         & ray_out   = DUMMY_RAY, //!< Output ray
    real          tolerance = EPSILON    //!< Tolerance
  );

  //! Intersection ray with triangle \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    ray      const & ray_in,                      //!< Input ray
    triangle const & triangle_in,                 //!< Input triangle
    segment        & segment_out = DUMMY_SEGMENT, //!< Output segment
    real             tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection ray with disk \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    ray     const & ray_in,                      //!< Input ray
    disk    const & disk_in,                     //!< Input disk
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection ray with plane \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    plane   const & plane_in,                    //!< Input plane
    segment const & segment_in,                  //!< Input segment
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection plane with triangle \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    plane    const & plane_in,                      //!< Input plane
    triangle const & triangle_in,                   //!< Input triangle
    triangle       & triangle_out = DUMMY_TRIANGLE, //!< Output triangle
    real             tolerance    = EPSILON         //!< Tolerance
  );

  //! Intersection plane with disk \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    plane const & plane_in,               //!< Input plane
    disk  const & disk_in,                //!< Input disk
    disk        & disk_out  = DUMMY_DISK, //!< Output disk
    real          tolerance = EPSILON     //!< Tolerance
  );

  //! Intersection segment with triangle \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    segment  const & segment_in,                  //!< Input segment
    triangle const & triangle_in,                 //!< Input triangle
    segment        & segment_out = DUMMY_SEGMENT, //!< Output segment
    real             tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection segment with disk \n
  //! WARNING: This function does only support coplanar objects!
  bool
  Intersection(
    segment const & segment_in,                  //!< Input segment
    disk    const & disk_in,                     //!< Input disk
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection triangle with disk \n
  //! WARNING: This function not supported!
  bool
  Intersection(
    triangle const & triangle_in,            //!< Input triangle
    disk     const & disk_in,                //!< Input disk
    none           & none_out  = DUMMY_NONE, //!< Output none
    real             tolerance = EPSILON     //!< Tolerance
  );

  /*\
   |   _   _              ____            _
   |  | \ | | ___  _ __  / ___|___  _ __ | | __ _ _ __   __ _ _ __
   |  |  \| |/ _ \| '_ \| |   / _ \| '_ \| |/ _` | '_ \ / _` | '__|
   |  | |\  | (_) | | | | |__| (_) | |_) | | (_| | | | | (_| | |
   |  |_| \_|\___/|_| |_|\____\___/| .__/|_|\__,_|_| |_|\__,_|_|
   |                               |_|
  \*/

  //! Intersection between two planes \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    plane const & plane0_in,              //!< Input plane 0
    plane const & plane1_in,              //!< Input plane 1
    line        & line_out  = DUMMY_LINE, //!< Output line
    real          tolerance = EPSILON     //!< Tolerance
  );

  //! Intersection between three planes \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    plane const & plane0_in,               //!< Input plane 0
    plane const & plane1_in,               //!< Input plane 1
    plane const & plane2_in,               //!< Input plane 1
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection between triangles \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    triangle const & triangle0_in,                //!< Input triangle 0
    triangle const & triangle1_in,                //!< Input triangle 1
    segment        & segment_out = DUMMY_SEGMENT, //!< Output segment
    real             tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection between disks \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    disk    const & disk0_in,                    //!< Input disk 0
    disk    const & disk1_in,                    //!< Input disk 1
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection between balls \n
  //! WARNING: This function not supported!
  bool
  Intersection(
    ball const & ball0_in,               //!< Input ball 0
    ball const & ball1_in,               //!< Input ball 1
    none       & none_out  = DUMMY_NONE, //!< Output none
    real         tolerance = EPSILON     //!< Tolerance
  );

  //! Intersection line with plane \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    line  const & line_in,                 //!< Input line
    plane const & plane_in,                //!< Input plane
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection line with triangle \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    line     const & line_in,                 //!< Input line
    triangle const & triangle_in,             //!< Input triangle
    point          & point_out = DUMMY_POINT, //!< Output point
    real             tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection line and disk \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    line  const & line_in,                 //!< Input line
    disk  const & disk_in,                 //!< Input disk
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection line and ball \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    line    const & line_in,                     //!< Input line
    ball    const & ball_in,                     //!< Input ball
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection ray with plane \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    ray   const & ray_in,                  //!< Input ray
    plane const & plane_in,                //!< Input plane
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection ray with triangle \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    ray      const & ray_in,                  //!< Input ray
    triangle const & triangle_in,             //!< Input triangle
    point          & point_out = DUMMY_POINT, //!< Output point
    real             tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection ray with disk \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    ray   const & ray_in,                  //!< Input ray
    disk  const & disk_in,                 //!< Input disk
    point       & point_out = DUMMY_POINT, //!< Output point
    real          tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection ray and ball \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    ray     const & ray_in,                      //!< Input ray
    ball    const & ball_in,                     //!< Input ball
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection plane with segment \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    plane   const & plane_in,                //!< Input plane
    segment const & segment,                 //!< Input segment
    point         & point_out = DUMMY_POINT, //!< Output point
    real            tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection plane with triangle \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    plane    const & plane_in,                    //!< Input plane
    triangle const & triangle_in,                 //!< Input triangle
    segment        & segment_out = DUMMY_SEGMENT, //!< Output segment
    real             tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection plane with disk \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    plane   const & plane_in,                    //!< Input plane
    disk    const & disk_in,                     //!< Input disk
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection plane and ball \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    plane const & plane_in,               //!< Input plane
    ball  const & ball_in,                //!< Input ball
    disk        & disk_out  = DUMMY_DISK, //!< Output disk
    real          tolerance = EPSILON     //!< Tolerance
  );

  //! Intersection ray with triangle \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    segment  const & segment_in,              //!< Input segment
    triangle const & triangle_in,             //!< Input triangle
    point          & point_out = DUMMY_POINT, //!< Output point
    real             tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection segment with disk \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    segment const & segment_in,              //!< Input segment
    disk    const & disk_in,                 //!< Input disk
    point         & point_out = DUMMY_POINT, //!< Output point
    real            tolerance = EPSILON      //!< Tolerance
  );

  //! Intersection segment and ball \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    segment const & segment_in,                  //!< Input segment
    ball    const & ball_in,                     //!< Input ball
    segment       & segment_out = DUMMY_SEGMENT, //!< Output segment
    real            tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection triangle with disk \n
  //! WARNING: This function does not support coplanarity!
  bool
  Intersection(
    triangle const & triangle_in,                 //!< Input triangle
    disk     const & disk_in,                     //!< Input disk
    segment        & segment_out = DUMMY_SEGMENT, //!< Output segment
    real             tolerance   = EPSILON        //!< Tolerance
  );

  //! Intersection triangle and ball \n
  //! WARNING: Function not supported!
  bool
  Intersection(
    triangle const & triangle_in,            //!< Input triangle
    ball     const & ball_in,                //!< Input ball
    none           & none_out  = DUMMY_NONE, //!< Output none
    real             tolerance = EPSILON     //!< Tolerance
  );

  //! Intersection disk and ball \n
  //! WARNING: Function not supported!
  bool
  Intersection(
    disk const & disk_in,                //!< Input disk
    ball const & ball_in,                //!< Input ball
    none       & none_out  = DUMMY_NONE, //!< Output none
    real         tolerance = EPSILON     //!< Tolerance
  );

  /*\
   |   __  __ _              _ _
   |  |  \/  (_)___  ___ ___| | | __ _ _ __   ___  ___  _   _ ___
   |  | |\/| | / __|/ __/ _ \ | |/ _` | '_ \ / _ \/ _ \| | | / __|
   |  | |  | | \__ \ (_|  __/ | | (_| | | | |  __/ (_) | |_| \__ \
   |  |_|  |_|_|___/\___\___|_|_|\__,_|_| |_|\___|\___/ \__,_|___/
   |
  \*/

  //! Intersection between two axis aligned boxes
  bool
  Intersection(
    aabb const & aabb0_in,               //!< Input aabb 0
    aabb const & aabb1_in,               //!< Input aabb 1
    aabb       & aabb_out  = DUMMY_AABB, //!< Output aabb
    real         tolerance = EPSILON     //!< Tolerance
  );

} // namespace acme

#endif

///
/// eof: intersection.hxx
///
