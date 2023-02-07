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
/// file: triangleground.cc
///

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include "enve.hh"

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

  triangleground::triangleground(void)
    : triangle(NAN_TRIANGLE),
      m_id(integer(0)),
      m_friction(QUIET_NAN),
      m_normal(NAN_VEC3),
      m_bbox(NAN_AABB)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangleground::triangleground(
    integer id,
    real    friction,
    real    vertex_0_x,
    real    vertex_0_y,
    real    vertex_0_z,
    real    vertex_1_x,
    real    vertex_1_y,
    real    vertex_1_z,
    real    vertex_2_x,
    real    vertex_2_y,
    real    vertex_2_z
  )
    : triangle(vertex_0_x, vertex_0_y, vertex_0_z,
               vertex_1_x, vertex_1_y, vertex_1_z,
               vertex_2_x, vertex_2_y, vertex_2_z),
      m_id(id),
      m_friction(friction),
      m_normal(NAN_VEC3),
      m_bbox(NAN_AABB)
  {
    #define CMD "enve::ground::triangleground::triangleground(...): "

    ENVE_ASSERT(this->m_friction >= real(0.0),
      CMD "negative friction coefficient scaling factor detected.");

    this->updateNormal();
    this->updateBBox();

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangleground::triangleground(
    integer         id,
    real            friction,
    point   const & point_0,
    point   const & point_1,
    point   const & point_2
  )
    : triangle(point_0, point_1, point_2),
      m_id(id),
      m_friction(friction),
      m_normal(NAN_VEC3),
      m_bbox(NAN_AABB)
  {
    #define CMD "enve::ground::triangleground::triangleground(...): "

    ENVE_ASSERT(this->m_friction >= real(0.0),
      CMD "negative friction coefficient scaling factor detected.");

    this->updateNormal();
    this->updateBBox();

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangleground::triangleground(
    integer       id,
    real          friction,
    point   const vertex[3]
  )
    : triangle(vertex),
      m_id(id),
      m_friction(friction),
      m_normal(NAN_VEC3),
      m_bbox(NAN_AABB)
  {
    #define CMD "enve::ground::triangleground::triangleground(...): "

    ENVE_ASSERT(this->m_friction >= real(0.0),
      CMD "negative friction coefficient scaling factor detected.");

    this->updateNormal();
    this->updateBBox();

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  triangleground::copy(
    triangleground const & triangleground_obj
  )
  {
    this->triangle::operator=(triangleground_obj);
    this->m_friction = triangleground_obj.m_friction;
    this->m_normal   = triangleground_obj.m_normal;
    this->m_bbox     = triangleground_obj.m_bbox;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  triangleground::isApprox(
    triangleground const & triangleground_obj,
    real                   tolerance
  )
    const
  {
    return this->triangle::isApprox(triangleground_obj) &&
           IsApprox(this->m_friction, triangleground_obj.m_friction, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  triangleground::friction(void)
    const
  {
    return this->m_friction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer const &
  triangleground::id(void)
    const
  {
    return this->m_id;
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

  point const &
  triangleground::operator[](
    size_t i
  )
    const
  {
    return triangle::vertex(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  triangleground::vertex(
    size_t i
  )
    const
  {
    return triangle::vertex(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  triangleground::print(
    out_stream & os
  )
    const
  {
    integer ID = this->m_id;
    real    F  = this->m_friction;
    point   V0(this->vertex(0));
    point   V1(this->vertex(1));
    point   V2(this->vertex(2));
    vec3    N(this->normal());
    point   Max(this->bbox().max());
    point   Min(this->bbox().min());
    os
      << "TRINGLEGROUND DATA"
      << "\t ID  = " << ID << "\t : integer - ID (-)" << std::endl
      << "\t F   = " << F  << "\t : real - Friction coefficient scaling factor (-)" << std::endl
      << "\t V0  = [" << V0.x()  << ", " << V0.y()  << ", " << V0.z()  << "]'\t : point - Vertex 0 (m)" << std::endl
      << "\t V1  = [" << V1.x()  << ", " << V1.y()  << ", " << V1.z()  << "]'\t : point - Vertex 1 (m)" << std::endl
      << "\t V2  = [" << V2.x()  << ", " << V2.y()  << ", " << V2.z()  << "]'\t : point - Vertex 2 (m)" << std::endl
      << "\t N   = [" << N.x()   << ", " << N.y()   << ", " << N.z()   << "]'\t : vec3 - Unit normal (-)" << std::endl
      << "\t Max = [" << Max.x() << ", " << Max.y() << ", " << Max.z() << "]'\t : point - Aabb maximum point (m)" << std::endl
      << "\t Min = [" << Min.x() << ", " << Min.y() << ", " << Min.z() << "]'\t : point - Aabb minimum point (m)" << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  triangleground::updateNormal(void)
  {
    this->m_normal = this->triangle::normal();
    if (this->m_normal.z() < real(0.0))
      {this->m_normal *= real(-1.0);}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  triangleground::updateBBox(void)
  {
    this->m_bbox.id() = this->m_id;
    this->m_bbox.clamp(this->vertex(0), this->vertex(1), this->vertex(2));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  triangleground::operator[](
    size_t i
  )
  {
    return triangle::vertex(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  triangleground::vertex(
    size_t i
  )
  {
    return triangle::vertex(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

#endif

///
/// eof: triangleground.cc
///
