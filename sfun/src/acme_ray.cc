/*
(***********************************************************************)
(*                                                                     *)
(* The ACME project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *)
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
/// file: acme_ray.ccc
///

#include "acme_ray.hh"

namespace acme
{

  /*\
   |
   |   _ __ __ _ _   _
   |  | '__/ _` | | | |
   |  | | | (_| | |_| |
   |  |_|  \__,_|\__, |
   |             |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  ray::~ray(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  ray::ray(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  ray::ray(
    real origin_x,
    real origin_y,
    real origin_z,
    real direction_x,
    real direction_y,
    real direction_z)
    : m_origin(origin_x, origin_y, origin_z),
      m_direction(direction_x, direction_y, direction_z)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  ray::ray(
    point const &origin,
    vec3 const  &direction)
    : m_origin(origin),
      m_direction(direction)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  ray &
  ray::operator=(
    ray const &ray_in)
  {
    if (this == &ray_in)
    {
      return *this;
    }
    else
    {
      this->m_origin    = ray_in.m_origin;
      this->m_direction = ray_in.m_direction;
      return *this;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ray::isApprox(
    ray const &ray_in,
    real       tolerance)
    const
  {
    return this->m_origin.isApprox(ray_in.m_origin, tolerance) &&
           this->m_direction.isApprox(ray_in.m_direction, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  ray::origin(void)
    const
  {
    return this->m_origin;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3 const &
  ray::direction(void)
    const
  {
    return this->m_direction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  ray::origin(void)
  {
    return this->m_origin;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3 &
  ray::direction(void)
  {
    return this->m_direction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ray::normalize(void)
  {
    this->m_direction.normalize();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  ray::toVector(void)
    const
  {
    return this->m_direction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  ray::toUnitVector(void)
    const
  {
    return this->m_direction.normalized();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ray::reverse(void)
  {
    this->m_direction = -this->m_direction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ray::translate(
    vec3 const &vector_in)
  {
    this->m_origin = vector_in + this->m_origin;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ray::transform(
    affine const &affine_in)
  {
    this->m_origin.transform(affine_in);
    acme::transform(this->m_direction, affine_in);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ray::isInside(
    point const &point_in,
    real         tolerance)
    const
  {
    return acme::isApprox((point_in - this->m_origin).normalized().cross(this->m_direction).norm(), 0.0, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ray::isDegenerated(
    real tolerance)
    const
  {
    return acme::isApprox(this->m_direction.norm(), 0.0, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ray::clamp(
    vec3 &min,
    vec3 &max)
    const
  {
    return this->isClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  ray::clamp(
    real &min_x,
    real &min_y,
    real &min_z,
    real &max_x,
    real &max_y,
    real &max_z)
    const
  {
    return this->isClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

///
/// eof: acme_ray.cc
///