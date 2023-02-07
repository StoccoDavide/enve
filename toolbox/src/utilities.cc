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
/// file: utilities.cc
///

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include "acme.hh"

namespace acme
{
  /*\
   |         _   _ _
   |   _   _| |_(_) |___
   |  | | | | __| | / __|
   |  | |_| | |_| | \__ \
   |   \__,_|\__|_|_|___/
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  std::ostream &
  operator<<(
    std::ostream       & os,
    vec3         const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "[ " << obj(0) << ", " << obj(1) << ", " << obj(2) << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  std::ostream &
  operator<<(
    std::ostream       & os,
    point        const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "[ " << obj(0) << ", " << obj(1) << ", " << obj(2) << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream       & os,
    line       const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "Line origin    = " << obj.origin()
       << "Line direction = " << obj.direction();
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream       & os,
    ray        const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "Ray origin    = " << obj.origin()
       << "Ray direction = " << obj.direction();
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream       & os,
    plane      const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "Plane origin = " << obj.origin()
       << "Plane normal = " << obj.normal();
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream       & os,
    segment    const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "Segment vertex 0 = " << obj.vertex(0)
       << "Segment vertex 1 = " << obj.vertex(1);
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream       & os,
    aabb       const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "Aabb minimum point = " << obj.min()
       << "Aabb maximum point = " << obj.max();
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream       & os,
    triangle   const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "Triangle vertex 0 = " << obj.vertex(0)
       << "Triangle vertex 1 = " << obj.vertex(1)
       << "Triangle vertex 2 = " << obj.vertex(2);
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream       & os,
    disk       const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "Disk radius = " << obj.radius()
       << "Disk center = " << obj.center()
       << "Disk normal = " << obj.normal();
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream       & os,
    ball       const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "Ball radius = " << obj.radius()
       << "Ball center = " << obj.center();
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream       & os,
    affine     const & obj
  )
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "Affine = [ " << obj(0,0) << ", " << obj(0,1) << ", " << obj(0,2) << ", " << obj(0,3) << " ]" << std::endl
       << "         [ " << obj(1,0) << ", " << obj(1,1) << ", " << obj(1,2) << ", " << obj(1,3) << " ]" << std::endl
       << "         [ " << obj(2,0) << ", " << obj(2,1) << ", " << obj(2,2) << ", " << obj(2,3) << " ]" << std::endl
       << "         [ " << obj(3,0) << ", " << obj(3,1) << ", " << obj(3,2) << ", " << obj(3,3) << " ]" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

#endif

///
/// eof: utilities.cc
///
