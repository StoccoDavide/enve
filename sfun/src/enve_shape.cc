/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *)
(*                                                                     *)
(* The ENVE project can not be copied and/or distributed without the   *)
(* express permission of Davide Stocco and Enrico Bertolazzi.          *)
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
/// file: enve_shape.cc
///

#include "enve_shape.hh"

namespace enve
{

  /*\
   |       _
   |   ___| |__   __ _ _ __   ___
   |  / __| '_ \ / _` | '_ \ / _ \
   |  \__ \ | | | (_| | |_) |  __/
   |  |___/_| |_|\__,_| .__/ \___|
   |                  |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shape::~shape(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shape::shape(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shape::shape(
    real r_x,
    real m_x,
    real r_y,
    real m_y,
    real l_y
  )
    : m_r_x(r_x),
      m_m_x(m_x),
      m_r_y(r_y),
      m_m_y(m_y),
      m_l_y(l_y)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shape::copy(
    shape const &shape_in
  )
  {
    this->m_r_x = shape_in.m_r_x;
    this->m_m_x = shape_in.m_m_x;
    this->m_r_y = shape_in.m_r_y;
    this->m_m_y = shape_in.m_m_y;
    this->m_l_y = shape_in.m_l_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shape::isApprox(
    shape const &shape_in,
    real         tolerance 
  )
    const
  {
    return acme::isApprox(this->m_r_x, shape_in.m_r_x, tolerance) &&
           acme::isApprox(this->m_m_x, shape_in.m_m_x, tolerance) &&
           acme::isApprox(this->m_r_y, shape_in.m_r_y, tolerance) &&
           acme::isApprox(this->m_m_y, shape_in.m_m_y, tolerance) &&
           acme::isApprox(this->m_l_y, shape_in.m_l_y, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::Rx(void)
    const
  {
    return this->m_r_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::Mx(void)
    const
  {
    return this->m_m_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::Ry(void)
    const
  {
    return this->m_r_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::My(void)
    const
  {
    return this->m_m_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::Ly(void)
    const
  {
    return this->m_l_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  shape::Rx(void)
  {
    return this->m_r_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  shape::Mx(void)
  {
    return this->m_m_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  shape::Ry(void)
  {
    return this->m_r_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  shape::My(void)
  {
    return this->m_m_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  shape::Ly(void)
  {
    return this->m_l_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::surfaceMaxRadius(void)
    const
  {
    return this->m_r_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::surfaceMaxWidth(void)
    const
  {
    return this->m_l_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shape::checkWidthBound(
    real y
  )
    const
  {
    if (std::abs(y) > this->m_l_y)
      return false;
    else
      return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shape::surfaceRadius(
    real y
  )
    const
  {
    real y_abs = std::abs(y);
    ENVE_ASSERT(y_abs <= this->m_l_y, "enve::surfaceRadius(y): y coordinate is out of shape overall volume.\n");
    return std::pow(1.0 - std::pow(y_abs / this->m_r_y, this->m_m_y), 1.0 / this->m_m_x) * this->m_r_x;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::surfaceWidth(void)
    const
  {
    return this->m_l_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shape::surfaceDerivative(
    real y,
    real tolerance
  )
    const
  {
    real y_abs = std::abs(y);
    ENVE_ASSERT(this->checkWidthBound(y), "enve::surfaceDerivative(y, tolerance): y coordinate is out of shape overall volume.\n");
    if (y_abs > tolerance)
    {
      real sign  = y / y_abs;
      real y_val = sign * y;
      real y_pre = std::pow(y_val / this->m_r_y, this->m_m_y);
      return -sign * std::pow(1.0 - y_pre, (1.0 - this->m_m_x) / this->m_m_x) * y_pre * this->m_r_x * this->m_m_y / (this->m_m_x * y_val);
    }
    else
    {
      return 0.0;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shape::surfaceAngle(
    real y,
    real tolerance
  )
    const
  {
    return std::atan(this->surfaceDerivative(y, tolerance));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shape::print(
    out_stream &os
  )
    const
  {
    os << "Shell shape parameters:" << std::endl
       << "R_x = " << this->m_r_x << " m" << std::endl
       << "m_x = " << this->m_m_x << std::endl
       << "R_y = " << this->m_r_y << " m" << std::endl
       << "m_y = " << this->m_m_y << std::endl
       << "L_y = " << this->m_l_y << std::endl
       << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_shape.cc
///