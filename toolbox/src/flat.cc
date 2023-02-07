/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * The ENVE project                                                    *
 *                                                                     *
 * Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *
 *                                                                     *
 * The ENVE project and its components are supplied under the terms of *
 * the open source BSD 3-Clause License. The contents of the ENVE      *
 * project and its components may not be copied or disclosed except in *
 * accordance with the terms of the BSD 3-Clause License.              *
 *                                                                     *
 * URL: https://opensource.org/licenses/BSD-3-Clause                   *
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
/// file: flat.cc
///

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include "enve.hh"

using namespace acme;

namespace enve
{

  namespace ground
  {

    /*\
     |    __ _       _
     |   / _| | __ _| |_
     |  | |_| |/ _` | __|
     |  |  _| | (_| | |_
     |  |_| |_|\__,_|\__|
     |
    \*/

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    flat::flat(void)
      : plane(NAN_PLANE),
        m_friction(QUIET_NAN)
    {
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    flat::flat(
      real friction,
      real origin_x,
      real origin_y,
      real origin_z,
      real normal_x,
      real normal_y,
      real normal_z
    )
      : plane(origin_x, origin_y, origin_z,
              normal_x, normal_y, normal_z),
        m_friction(friction)
    {
      #define CMD "enve::ground::flat::flat(...): "

      ENVE_ASSERT(this->m_friction >= real(0.0),
        CMD "negative friction coefficient scaling factor detected.");
      ENVE_ASSERT(normal_z > real(0.0),
        CMD "negative normal z-axis detected.");
      this->plane::normalize();

      #undef CMD
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    flat::flat(
      real          friction,
      point const & origin,
      vec3  const & normal
    )
      : plane(origin, normal),
        m_friction(friction)
    {
      #define CMD "enve::ground::flat::flat(...): "

      ENVE_ASSERT(this->m_friction >= real(0.0),
        CMD "negative friction coefficient scaling factor detected.");
      ENVE_ASSERT(normal.z() > real(0.0),
        CMD "negative normal z-axis detected.");
      this->plane::normalize();

      #undef CMD
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    flat::flat(
      real          friction,
      plane const & plane_obj
    )
      : plane(plane_obj),
        m_friction(friction)
    {
      #define CMD "enve::ground::flat::flat(...): "

      ENVE_ASSERT(this->m_friction >= real(0.0),
        CMD "negative friction coefficient scaling factor detected.");
      ENVE_ASSERT(this->plane::normal().z() > real(0.0),
        CMD "negative normal z-axis detected.");
      this->plane::normalize();

      #undef CMD
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    flat::copy(
      flat const & flat_obj
    )
    {
      this->plane::operator=(flat_obj);
      this->m_friction = flat_obj.m_friction;
      this->plane::normalize();
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool
    flat::isApprox(
      flat const & flat_bj,
      real         tolerance
    )
      const
    {
      return this->plane::isApprox(flat_bj) &&
             IsApprox(this->m_friction, flat_bj.m_friction, tolerance);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    real const &
    flat::friction(void)
      const
    {
      return this->m_friction;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    real &
    flat::friction(void)
    {
      return this->m_friction;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    plane const &
    flat::layingPlane(void)
      const
    {
      return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    plane &
    flat::layingPlane(void)
    {
      return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    flat::print(
      out_stream & os
    )
      const
    {
      real  F = this->m_friction;
      point O(this->origin());
      vec3  N(this->normal());
      os
        << "TRINGLEGROUND DATA"
        << "\t F = " << F  << "\t : real - Friction coefficient scaling factor (-)" << std::endl
        << "\t O = [" << O.x() << ", " << O.y() << ", " << O.z() << "]'\t : point - Plane origin point (m)" << std::endl
        << "\t N = [" << N.x() << ", " << N.y() << ", " << N.z() << "]'\t : vec3 - Plane unit normal (-)" << std::endl;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  } // namespace ground

} // namespace enve

#endif

///
/// eof: flat.cc
///
