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
/// file: acme_aabb.cc
///

#include "acme_aabb.hh"

namespace acme
{

  /*\
   |               _     _
   |    __ _  __ _| |__ | |_
   |   / _` |/ _` | '_ \| '_ \
   |  | (_| | (_| | |_) | |_) |
   |   \__,_|\__,_|_.__/|_.__/
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  aabb::~aabb(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  aabb::aabb(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  aabb::aabb(
    real    min_x,
    real    min_y,
    real    min_z,
    real    max_x,
    real    max_y,
    real    max_z,
    integer id,
    integer ipos)
    : m_min(min_x, min_y, min_z),
      m_max(max_x, max_y, max_z),
      m_id(id),
      m_pos(ipos)
  {
    this->updateMaxMin();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  aabb::aabb(
    point const &min,
    point const &max,
    integer      id,
    integer      ipos)
    : m_min(min),
      m_max(max),
      m_id(id),
      m_pos(ipos)
  {
    this->updateMaxMin();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  aabb::aabb(
    std::vector<aabb::ptr> const &boxes,
    integer                       id,
    integer                       ipos)
    : m_min(NAN_POINT),
      m_max(NAN_POINT),
      m_id(id),
      m_pos(ipos)
  {
    this->merged(boxes);
    this->updateMaxMin();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  aabb &
  aabb::operator=(
    aabb const &aabb_in)
  {
    if (this == &aabb_in)
    {
      return *this;
    }
    else
    {
      this->m_min = aabb_in.m_min;
      this->m_max = aabb_in.m_max;
      this->m_id  = aabb_in.m_id;
      this->m_pos = aabb_in.m_pos;
      return *this;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  aabb::clear(
    void)
  {
    this->m_min = NAN_POINT;
    this->m_max = NAN_POINT;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  aabb::isApprox(
    aabb const &aabb_in,
    real        tolerance)
    const
  {
    return this->m_min.isApprox(aabb_in.m_min, tolerance) &&
           this->m_max.isApprox(aabb_in.m_max, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  aabb::checkMaxMin(void)
    const
  {
    return this->m_max.x() >= this->m_min.x() &&
           this->m_max.y() >= this->m_min.y() &&
           this->m_max.z() >= this->m_min.z();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  aabb::updateMaxMin(void)
  {
    bool output = true;
    real point_max_tmp, point_min_tmp;
    for (size_t i = 0; i < 3; ++i)
    {
      point_max_tmp = this->m_max[i];
      point_min_tmp = this->m_min[i];
      if (point_max_tmp < point_min_tmp)
      {
        this->m_max[i] = point_min_tmp;
        this->m_min[i] = point_max_tmp;
        output         = false;
      }
    }
    return output;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  aabb::min(void)
    const
  {
    return this->m_min;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  aabb::min(void)
  {
    return this->m_min;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  aabb::min(
    size_t i)
    const
  {
    return this->m_min[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  aabb::min(
    size_t i)
  {
    return this->m_min[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  aabb::min(
    real x,
    real y,
    real z)
  {
    this->m_min.x() = x;
    this->m_min.y() = y;
    this->m_min.z() = z;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  aabb::max(void)
    const
  {
    return this->m_max;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  aabb::max(void)
  {
    return this->m_max;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  aabb::max(
    size_t i)
    const
  {
    return this->m_max[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  aabb::max(
    size_t i)
  {
    return this->m_max[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  aabb::max(
    real x,
    real y,
    real z)
  {
    this->m_max.x() = x;
    this->m_max.y() = y;
    this->m_max.z() = z;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  aabb::intersects(
    aabb const &aabb_in)
    const
  {
    return this->m_min.x() <= aabb_in.m_max.x() && this->m_max.x() >= aabb_in.m_min.x() &&
           this->m_min.y() <= aabb_in.m_max.y() && this->m_max.y() >= aabb_in.m_min.y() &&
           this->m_min.z() <= aabb_in.m_max.z() && this->m_max.z() >= aabb_in.m_min.z();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  aabb::merged(
    std::vector<aabb::ptr> const &boxes)
  {
    if (boxes.empty())
    {
      this->m_min = point::Constant(0.0);
      this->m_max = point::Constant(0.0);
    }
    else
    {
      std::vector<aabb::ptr>::const_iterator it = boxes.begin();

      this->m_min = (*it)->m_min;
      this->m_max = (*it)->m_max;

      for (++it; it != boxes.end(); ++it)
      {
        aabb const &cur_box = **it;
        if (cur_box.m_min.x() < this->m_min.x())
          this->m_min.x() = cur_box.m_min.x();
        if (cur_box.m_min.y() < this->m_min.y())
          this->m_min.y() = cur_box.m_min.y();
        if (cur_box.m_min.z() < this->m_min.z())
          this->m_min.z() = cur_box.m_min.z();
        if (cur_box.m_max.x() > this->m_max.x())
          this->m_max.x() = cur_box.m_max.x();
        if (cur_box.m_max.y() > this->m_max.y())
          this->m_max.y() = cur_box.m_max.y();
        if (cur_box.m_max.z() > this->m_max.z())
          this->m_max.z() = cur_box.m_max.z();
      }
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  aabb::centerDistance(
    point const &point_in)
    const
  {
    point center((this->m_max + this->m_min) / 2);
    point point_max_centered(this->m_max - center);
    point point_centered(point_in - center);
    real  x_scale = std::abs(1.0 / point_max_centered.x());
    real  y_scale = std::abs(1.0 / point_max_centered.y());
    real  z_scale = std::abs(1.0 / point_max_centered.z());
    real  dx      = std::max(0.0, std::abs(point_centered.x()) * x_scale - 1.0) / x_scale;
    real  dy      = std::max(0.0, std::abs(point_centered.y()) * y_scale - 1.0) / y_scale;
    real  dz      = std::max(0.0, std::abs(point_centered.z()) * z_scale - 1.0) / z_scale;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  aabb::exteriorDistance(
    point const &point_in)
    const
  {
    real dx = std::max(std::abs(point_in.x() - this->m_min.x()), std::abs(point_in.x() - this->m_max.x()));
    real dy = std::max(std::abs(point_in.y() - this->m_min.y()), std::abs(point_in.y() - this->m_max.y()));
    real dz = std::max(std::abs(point_in.z() - this->m_min.z()), std::abs(point_in.z() - this->m_max.z()));
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  aabb::clamp(
    point const &point0_in,
    point const &point1_in,
    point const &point2_in)
  {
    this->m_min.x() = std::min(point0_in.x(), std::min(point1_in.x(), point2_in.x()));
    this->m_min.y() = std::min(point0_in.y(), std::min(point1_in.y(), point2_in.y()));
    this->m_min.z() = std::min(point0_in.z(), std::min(point1_in.z(), point2_in.z()));
    this->m_max.x() = std::max(point0_in.x(), std::max(point1_in.x(), point2_in.x()));
    this->m_max.y() = std::max(point0_in.y(), std::max(point1_in.y(), point2_in.y()));
    this->m_max.z() = std::max(point0_in.z(), std::max(point1_in.z(), point2_in.z()));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  aabb::clamp(
    point const point_in[3])
  {
    this->m_min.x() = std::min(point_in[0].x(), std::min(point_in[1].x(), point_in[2].x()));
    this->m_min.y() = std::min(point_in[0].y(), std::min(point_in[1].y(), point_in[2].y()));
    this->m_min.z() = std::min(point_in[0].z(), std::min(point_in[1].z(), point_in[2].z()));
    this->m_max.x() = std::max(point_in[0].x(), std::max(point_in[1].x(), point_in[2].x()));
    this->m_max.y() = std::max(point_in[0].y(), std::max(point_in[1].y(), point_in[2].y()));
    this->m_max.z() = std::max(point_in[0].z(), std::max(point_in[1].z(), point_in[2].z()));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer const &
  aabb::id(void)
    const
  {
    return this->m_id;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer &
  aabb::id(void)
  {
    return this->m_id;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer const &
  aabb::pos(void)
    const
  {
    return this->m_pos;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer &
  aabb::pos(void)
  {
    return this->m_pos;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  aabb::translate(
    point const &vector_in)
  {
    this->m_min = vector_in + this->m_min;
    this->m_max = vector_in + this->m_max;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  aabb::isInside(
    point const &point_in,
    real         tolerance)
    const
  {
    return this->m_min.x() <= point_in.x() &&
           this->m_min.y() <= point_in.y() &&
           this->m_min.z() <= point_in.z() &&
           this->m_max.x() >= point_in.x() &&
           this->m_max.y() >= point_in.y() &&
           this->m_max.z() >= point_in.z();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  aabb::isDegenerated(
    real tolerance)
    const
  {
    return this->m_min.isApprox(this->m_max, tolerance) &&
           this->checkMaxMin();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

///
/// eof: acme_aabb.cc
///