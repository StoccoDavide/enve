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
/// file: acme_segment.cc
///

#include "acme_segment.hh"

namespace acme
{

  /*\
   |                                       _
   |   ___  ___  __ _ _ __ ___   ___ _ __ | |_
   |  / __|/ _ \/ _` | '_ ` _ \ / _ \ '_ \| __|
   |  \__ \  __/ (_| | | | | | |  __/ | | | |_
   |  |___/\___|\__, |_| |_| |_|\___|_| |_|\__|
   |            |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  segment::~segment(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  segment::segment(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  segment::segment(
    real vertex0_x,
    real vertex0_y,
    real vertex0_z,
    real vertex1_x,
    real vertex1_y,
    real vertex1_z)
    : m_vertex{point(vertex0_x, vertex0_y, vertex0_z), point(vertex1_x, vertex1_y, vertex1_z)}
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  segment::segment(
    point const &vertex0,
    point const &vertex1)
    : m_vertex{vertex0, vertex1}
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  segment::segment(
    point const vertex[2])
    : m_vertex{vertex[0], vertex[1]}
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  segment &
  segment::operator=(
    segment const &segment_in)
  {
    if (this == &segment_in)
    {
      return *this;
    }
    else
    {
      this->m_vertex[0] = segment_in.m_vertex[0];
      this->m_vertex[1] = segment_in.m_vertex[1];
      return *this;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  segment::isApprox(
    segment const &segment_in,
    real           tolerance)
    const
  {
    return this->m_vertex[0].isApprox(segment_in.m_vertex[0], tolerance) &&
           this->m_vertex[1].isApprox(segment_in.m_vertex[1], tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point
  segment::centroid(void)
    const
  {
    return (this->m_vertex[0] + this->m_vertex[1]) / 2.0;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  segment::vertex(
    size_t i)
    const
  {
    return this->m_vertex[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  segment::vertex(
    size_t i)
  {
    return this->m_vertex[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  segment::operator[](
    size_t i)
    const
  {
    return this->m_vertex[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  segment::operator[](
    size_t i)
  {
    return this->m_vertex[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  segment::toVector(void) const
  {
    return point(this->m_vertex[1] - this->m_vertex[0]);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  segment::toUnitVector(void) const
  {
    return (this->m_vertex[1] - this->m_vertex[0]).normalized();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  segment::swap(void)
  {
    point tmp_point(this->m_vertex[0]);
    this->m_vertex[0] = this->m_vertex[1];
    this->m_vertex[1] = tmp_point;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  segment::length(void) const
  {
    return (this->m_vertex[0] - this->m_vertex[1]).norm();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  segment::translate(
    vec3 const &vector_in)
  {
    this->m_vertex[0] = vector_in + this->m_vertex[0];
    this->m_vertex[1] = vector_in + this->m_vertex[1];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  segment::transform(
    affine const &affine_in)
  {
    this->m_vertex[0].transform(affine_in);
    this->m_vertex[1].transform(affine_in);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  segment::isInside(
    point const &query,
    real         tolerance)
    const
  {
    real d0 = this->length();
    real d1 = (query - this->m_vertex[0]).norm();
    real d2 = (query - this->m_vertex[1]).norm();
    return std::abs(d0 - d1 - d2) <= tolerance;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  segment::isDegenerated(
    real tolerance)
    const
  {
    return acme::isApprox((this->m_vertex[0] - this->m_vertex[1]).norm(), 0.0, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  segment::clamp(
    vec3 &min,
    vec3 &max)
    const
  {
    min[0] = std::min(this->m_vertex[0].x(), this->m_vertex[1].x());
    min[1] = std::min(this->m_vertex[0].y(), this->m_vertex[1].y());
    min[2] = std::min(this->m_vertex[0].z(), this->m_vertex[1].z());
    max[0] = std::max(this->m_vertex[0].x(), this->m_vertex[1].x());
    max[1] = std::max(this->m_vertex[0].y(), this->m_vertex[1].y());
    max[2] = std::max(this->m_vertex[0].z(), this->m_vertex[1].z());
    return this->isClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  segment::clamp(
    real &min_x,
    real &min_y,
    real &min_z,
    real &max_x,
    real &max_y,
    real &max_z)
    const
  {
    min_x = std::min(this->m_vertex[0].x(), this->m_vertex[1].x());
    min_y = std::min(this->m_vertex[0].y(), this->m_vertex[1].y());
    min_z = std::min(this->m_vertex[0].z(), this->m_vertex[1].z());
    max_x = std::max(this->m_vertex[0].x(), this->m_vertex[1].x());
    max_y = std::max(this->m_vertex[0].y(), this->m_vertex[1].y());
    max_z = std::max(this->m_vertex[0].z(), this->m_vertex[1].z());
    return this->isClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

///
/// eof: acme_segment.cc
///