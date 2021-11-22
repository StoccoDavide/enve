/*
(***********************************************************************)
(*                                                                     *)
(* The ACME project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Enrico Bertolazzi.       *)
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
/// file: acme_line.cc
///

#include "acme_line.hh"

namespace acme
{

  /*\
   |   _ _
   |  | (_)_ __   ___
   |  | | | '_ \ / _ \
   |  | | | | | |  __/
   |  |_|_|_| |_|\___|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  line::~line(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  line::line(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  line::line(
    real ox,
    real oy,
    real oz,
    real dx,
    real dy,
    real dz)
    : m_origin(ox, oy, oz),
      m_direction(dx, dy, dz)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  line::line(
    point const &origin,
    vec3 const  &direction)
    : m_origin(origin),
      m_direction(direction)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  line &
  line::operator=(
    line const &line_in)
  {
    if (this == &line_in)
    {
      return *this;
    }
    else
    {
      this->m_origin    = line_in.m_origin;
      this->m_direction = line_in.m_direction;
      return *this;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  line::isApprox(
    line const &line_in,
    real        tolerance)
    const
  {
    return this->m_origin.isApprox(line_in.m_origin, tolerance) &&
           this->m_direction.isApprox(line_in.m_direction, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  line::origin(void)
    const
  {
    return this->m_origin;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  line::origin(void)
  {
    return this->m_origin;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3 const &
  line::direction(void)
    const
  {
    return this->m_direction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3 &
  line::direction(void)
  {
    return this->m_direction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  line::normalize(void)
  {
    this->m_direction.normalize();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  line::toVector(void)
    const
  {
    return this->m_direction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  line::toUnitVector(void)
    const
  {
    return this->m_direction.normalized();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  line::reverse(void)
  {
    this->m_direction = -this->m_direction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  line::translate(
    vec3 const &vector_in)
  {
    this->m_origin = vector_in + this->m_origin;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  line::transform(
    affine const &affine_in)
  {
    this->m_origin.transform(affine_in);
    acme::transform(this->m_direction, affine_in);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  line::isInside(
    point const &point_in,
    real         tolerance)
    const
  {
    return acme::isApprox(((point_in - this->m_origin).normalized().cross(this->m_direction)).norm(), 0.0, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  line::isDegenerated(
    real tolerance)
    const
  {
    return acme::isApprox(this->m_direction.norm(), 0.0, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  line::clamp(
    vec3 &min,
    vec3 &max)
    const
  {
    return this->isClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  line::clamp(
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
/// eof: acme_line.cc
///