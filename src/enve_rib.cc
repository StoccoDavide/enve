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
/// file: enve_rib.cc
///

#include "enve_rib.hh"

using namespace acme;

namespace enve
{

  /*\
   |        _ _
   |   _ __(_) |__
   |  | '__| | '_ \
   |  | |  | | |_) |
   |  |_|  |_|_.__/
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::~rib()
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib()
    : disk(NAN_DISK),
      m_width(QUIET_NAN),
      m_angle(QUIET_NAN)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real         radius,
    plane const &plane,
    real         width,
    real         angle)
    : disk(radius, plane),
      m_width(width),
      m_angle(angle)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real         radius,
    plane const &plane)
    : disk(radius, plane),
      m_width(QUIET_NAN),
      m_angle(QUIET_NAN)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real         radius,
    point const &center,
    vec3 const  &normal,
    real         width,
    real         angle)
    : disk(radius, center, normal),
      m_width(width),
      m_angle(angle)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real         radius,
    point const &center,
    vec3 const  &normal)
    : disk(radius, center, normal),
      m_width(QUIET_NAN),
      m_angle(QUIET_NAN)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real radius,
    real center_x,
    real center_y,
    real center_z,
    real normal_x,
    real normal_y,
    real normal_z,
    real width,
    real angle)
    : disk(radius, center_x, center_y, center_z, normal_x, normal_y, normal_z),
      m_width(width),
      m_angle(angle)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real radius,
    real center_x,
    real center_y,
    real center_z,
    real normal_x,
    real normal_y,
    real normal_z)
    : disk(radius, center_x, center_y, center_z, normal_x, normal_y, normal_z),
      m_width(QUIET_NAN),
      m_angle(QUIET_NAN)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib &
  rib::operator=(
    rib const &rib_in)
  {
    if (this == &rib_in)
    {
      return *this;
    }
    else
    {
      this->disk::operator=(rib_in);
      this->m_width       = rib_in.m_width;
      this->m_angle       = rib_in.m_angle;
      return *this;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  rib::copy(
    rib const &rib_in)
  {
    this->radius()      = rib_in.radius();
    this->layingPlane() = rib_in.layingPlane();
    this->m_width       = rib_in.m_width;
    this->m_angle       = rib_in.m_angle;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  rib::width(void) const
  {
    return this->m_width;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  rib::angle(void) const
  {
    return this->m_angle;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  rib::width(void)
  {
    return this->m_width;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  rib::angle(void)
  {
    return this->m_angle;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::isApprox(
    rib const &rib_in,
    real       tolerance)
    const
  {

    return this->disk::isApprox(rib_in) &&
           acme::isApprox(this->m_width, rib_in.m_width, tolerance) &&
           acme::isApprox(this->m_angle, rib_in.m_angle, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_rib.cc
///