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
/// file: collinear.hxx
///

#pragma once
#ifndef INCLUDE_ACME_COLLINEAR_HXX
#define INCLUDE_ACME_COLLINEAR_HXX

#include "line.hxx"
#include "parallel.hxx"
#include "ray.hxx"
#include "segment.hxx"

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

  //! Check if entitys are collinear
  bool
  IsCollinear(
    entity const * entity0_in,         //!< Input entity 0
    entity const * entity1_in,         //!< Input entity 1
    real           tolerance = EPSILON //!< Tolerance
  );

  //! Check if lines are collinear
  bool
  IsCollinear(
    line const & line0_in,           //!< Input line 0
    line const & line1_in,           //!< Input line 1
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if rays are collinear
  bool
  IsCollinear(
    ray const & ray0_in,            //!< Input ray 0
    ray const & ray1_in,            //!< Input ray 1
    real        tolerance = EPSILON //!< Tolerance
  );

  //! Check if segments are collinear
  bool
  IsCollinear(
    segment const & segment0_in,        //!< Input segment 0
    segment const & segment1_in,        //!< Input segment 1
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and ray are collinear
  bool
  IsCollinear(
    line const & line_in,            //!< Input line
    ray  const & ray_in,             //!< Input ray
    real         tolerance = EPSILON //!< Tolerance
  );

  //! Check if line and segment are collinear
  bool
  IsCollinear(
    line    const & line_in,            //!< Input line
    segment const & segment_in,         //!< Input segment
    real            tolerance = EPSILON //!< Tolerance
  );

  //! Check if ray and segment are collinear
  bool
  IsCollinear(
    ray     const & ray_in,             //!< Input ray
    segment const & segment_in,         //!< Input segment
    real            tolerance = EPSILON //!< Tolerance
  );

} // namespace acme

#endif

///
/// eof: collinear.hxx
///
