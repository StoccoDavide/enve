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
/// file: plane.cc
///

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include "acme.hh"

namespace acme
{

  /*\
   |         _
   |   _ __ | | __ _ _ __   ___
   |  | '_ \| |/ _` | '_ \ / _ \
   |  | |_) | | (_| | | | |  __/
   |  | .__/|_|\__,_|_| |_|\___|
   |  |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  plane::plane(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  plane::plane(
    real origin_x,
    real origin_y,
    real origin_z,
    real normal_x,
    real normal_y,
    real normal_z
  )
    : m_origin(origin_x, origin_y, origin_z),
      m_normal(normal_x, normal_y, normal_z)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  plane::plane(
    point const & origin,
    vec3  const & normal
  )
    : m_origin(origin),
      m_normal(normal)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  plane::isApprox(
    plane const & plane_in,
    real          tolerance
  )
    const
  {
    return this->m_origin.isApprox(plane_in.m_origin, tolerance) &&
           this->m_normal.isApprox(plane_in.m_normal, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  plane::origin(void)
    const
  {
    return this->m_origin;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  plane::origin(void)
  {
    return this->m_origin;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3 const &
  plane::normal(void)
    const
  {
    return this->m_normal;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3 &
  plane::normal(void)
  {
    return this->m_normal;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  plane::unitNormal(void)
    const
  {
    return this->m_normal.normalized();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  plane::normalize(void)
  {
    this->m_normal.normalize();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  plane::reverse(void)
  {
    this->m_normal = -this->m_normal;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  plane::d(void)
    const
  {
    return -this->m_origin.dot(this->m_normal);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  plane::distance(
    point const & point_in
  )
    const
  {
    return std::abs(this->signedDistance(point_in));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  plane::squaredDistance(
    point const & point_in
  )
    const
  {
    real distance = this->signedDistance(point_in);
    return distance * distance;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  plane::signedDistance(
    point const & point_in
  )
    const
  {
    return (point_in - this->m_origin).dot(this->m_normal);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  plane::translate(
    vec3 const & vector_in
  )
  {
    this->m_origin = vector_in + this->m_origin;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  plane::transform(
    affine const & affine_in
  )
  {
    this->m_origin.transform(affine_in);
    Transform(this->m_normal, affine_in);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  plane::isInside(
    point const & point_in,
    real          tolerance
  )
    const
  {
    return this->distance(point_in) < tolerance;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  plane::isDegenerated(
    real tolerance
  )
    const
  {
    return IsApprox(this->m_normal.norm(), real(0.0), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  plane::clamp(
    vec3 & /*min*/,
    vec3 & /*max*/
  )
    const
  {
    return this->isClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  plane::clamp(
    real & /*min_x*/,
    real & /*min_y*/,
    real & /*min_z*/,
    real & /*max_x*/,
    real & /*max_y*/,
    real & /*max_z*/
  )
    const
  {
    return this->isClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

#endif

///
/// eof: plane.cc
///
