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
/// file: utils.hxx
///

#pragma once
#ifndef INCLUDE_ACME_UTILS_HXX
#define INCLUDE_ACME_UTILS_HXX

#include "aabb.hxx"
#include "ball.hxx"
#include "disk.hxx"
#include "line.hxx"
#include "plane.hxx"
#include "point.hxx"
#include "ray.hxx"
#include "segment.hxx"
#include "triangle.hxx"

namespace acme
{
  /*\
   |   _   _ _   _ _
   |  | | | | |_(_) |___
   |  | | | | __| | / __|
   |  | |_| | |_| | \__ \
   |   \___/ \__|_|_|___/
   |
  \*/

  //! Stream out operator for vec3 object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    vec3       const & obj //!< Point vec3
  );

  //! Stream out operator for point object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    point      const & obj //!< Point object
  );

  //! Stream out operator for line object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    line       const & obj //!< Line object
  );

  //! Stream out operator for ray object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    ray        const & obj //!< Ray object
  );

  //! Stream out operator for plane object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    plane      const & obj //!< Plane object
  );

  //! Stream out operator for segment object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    segment    const & obj //!< Segment object
  );

  //! Stream out operator for aabb object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    aabb       const & obj //!< Box object
  );

  //! Stream out operator for triangle object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    triangle   const & obj //!< Triangle object
  );

  //! Stream out operator for disk object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    disk       const & obj //!< Disk object
  );

  //! Stream out operator for ball object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    ball       const & obj //!< Ball object
  );

  //! Stream out operator for affine object
  out_stream &
  operator<<(
    out_stream       & os, //!< Output stream
    affine     const & obj //!< Affine object
  );

} // namespace acme

#endif

///
/// eof: utils.hxx
///
