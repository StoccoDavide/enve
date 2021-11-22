/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Enrico Bertolazzi.       *)
(*                                                                     *)
(* The ENVE project and its components are supplied under the terms of *)
(* the open source BSD 2-Clause License. The contents of the ENVE      *)
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
/// file: enve_triangleground.cc
///

#include "enve_triangleground.hh"

namespace enve
{

  /*\
   |   _        _                   _                          _
   |  | |_ _ __(_) __ _ _ __   __ _| | ___ _ __ ___   __ _  __| |
   |  | __| '__| |/ _` | '_ \ / _` | |/ _ \ '__/ _ \ / _` |/ _` |
   |  | |_| |  | | (_| | | | | (_| | |  __/ | | (_) | (_| | (_| |
   |   \__|_|  |_|\__,_|_| |_|\__, |_|\___|_|  \___/ \__,_|\__,_|
   |                          |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangleground::~triangleground(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangleground::triangleground(void)
    : triangle(NAN_TRIANGLE),
      m_friction(QUIET_NAN),
      m_normal(NAN_VEC3),
      m_bbox(NAN_AABB)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangleground::triangleground(
    real vertex0_x,
    real vertex0_y,
    real vertex0_z,
    real vertex1_x,
    real vertex1_y,
    real vertex1_z,
    real vertex2_x,
    real vertex2_y,
    real vertex2_z,
    real friction)
    : triangle(vertex0_x, vertex0_y, vertex0_z, vertex1_x, vertex1_y, vertex1_z, vertex2_x, vertex2_y, vertex2_z),
      m_friction(friction)
  {
    this->updateNormal();
    this->m_bbox.clamp(
      point(vertex0_x, vertex0_y, vertex0_z),
      point(vertex1_x, vertex1_y, vertex1_z),
      point(vertex2_x, vertex2_y, vertex2_z));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangleground::triangleground(
    point const &point0,
    point const &point1,
    point const &point2,
    real         friction)
    : triangle(point0, point1, point2),
      m_friction(friction)
  {
    this->updateNormal();
    this->m_bbox.clamp(point0, point1, point2);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangleground::triangleground(
    point const vertex[3],
    real        friction)
    : triangle(vertex),
      m_friction(friction)
  {
    this->updateNormal();
    this->m_bbox.clamp(vertex);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  triangleground::copy(
    triangleground const &triangleground_in)
  {
    triangle::operator=(triangleground_in);
    this->m_friction  = triangleground_in.m_friction;
    this->m_normal    = triangleground_in.m_normal;
    this->m_bbox      = triangleground_in.m_bbox;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  triangleground::isApprox(
    triangleground const &triangleground_in,
    real                  tolerance)
    const
  {
    return this->vertex(0).isApprox(triangleground_in.vertex(0)) &&
           this->vertex(1).isApprox(triangleground_in.vertex(1)) &&
           this->vertex(2).isApprox(triangleground_in.vertex(2)) &&
           acme::isApprox(this->m_friction, triangleground_in.m_friction, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  triangleground::friction(void)
  {
    return this->m_friction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  triangleground::friction(void)
    const
  {
    return this->m_friction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  aabb const &
  triangleground::bbox(void)
    const
  {
    return this->m_bbox;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3 const &
  triangleground::normal(void)
    const
  {
    return this->m_normal;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  triangleground::updateNormal(void)
  {
    this->m_normal = ((this->vertex(1) - this->vertex(0)).cross(this->vertex(2) - this->vertex(0))).normalized();
    if (this->m_normal.z() < 0.0)
      this->m_normal *= -1;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  triangleground::operator[](
    size_t i)
    const
  {
    return triangle::vertex(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  triangleground::vertex(
    size_t i)
    const
  {
    return triangle::vertex(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  triangleground::operator[](
    size_t i)
  {
    return triangle::vertex(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  triangleground::vertex(
    size_t i)
  {
    return triangle::vertex(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_triangleground.cc
///