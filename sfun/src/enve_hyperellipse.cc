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
/// file: enve_hyperellipse.cc
///

#include "enve_hyperellipse.hh"

namespace enve
{

  /*\
   |   _                               _ _ _
   |  | |__  _   _ _ __   ___ _ __ ___| | (_)_ __  ___  ___
   |  | '_ \| | | | '_ \ / _ \ '__/ _ \ | | | '_ \/ __|/ _ \
   |  | | | | |_| | |_) |  __/ | |  __/ | | | |_) \__ \  __/
   |  |_| |_|\__, | .__/ \___|_|  \___|_|_|_| .__/|___/\___|
   |         |___/|_|                       |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  hyperellipse::~hyperellipse(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  hyperellipse::hyperellipse(void)
    : shape()
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  hyperellipse::hyperellipse(
    real r_x,
    real m_x,
    real r_y,
    real m_y,
    real l_y)
    : shape(r_x, -l_y, +l_y),
      m_r_x(r_x),
      m_m_x(m_x),
      m_r_y(r_y),
      m_m_y(m_y),
      m_l_y(l_y)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  hyperellipse::copy(
    hyperellipse const &hyperellipse_in)
  {
    this->shape::copy(hyperellipse_in);
    this->m_r_x = hyperellipse_in.m_r_x;
    this->m_m_x = hyperellipse_in.m_m_x;
    this->m_r_y = hyperellipse_in.m_r_y;
    this->m_m_y = hyperellipse_in.m_m_y;
    this->m_l_y = hyperellipse_in.m_l_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  hyperellipse::isApprox(
    hyperellipse const &hyperellipse_in,
    real                tolerance)
    const
  {
    return this->shape::isApprox(hyperellipse_in, tolerance) &&
           acme::isApprox(this->m_r_x, hyperellipse_in.m_r_x, tolerance) &&
           acme::isApprox(this->m_m_x, hyperellipse_in.m_m_x, tolerance) &&
           acme::isApprox(this->m_r_y, hyperellipse_in.m_r_y, tolerance) &&
           acme::isApprox(this->m_m_y, hyperellipse_in.m_m_y, tolerance) &&
           acme::isApprox(this->m_l_y, hyperellipse_in.m_l_y, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  hyperellipse::Rx(void)
    const
  {
    return this->m_r_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  hyperellipse::Mx(void)
    const
  {
    return this->m_m_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  hyperellipse::Ry(void)
    const
  {
    return this->m_r_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  hyperellipse::My(void)
    const
  {
    return this->m_m_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  hyperellipse::Ly(void)
    const
  {
    return this->m_l_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  hyperellipse::Rx(void)
  {
    return this->m_r_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  hyperellipse::Mx(void)
  {
    return this->m_m_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  hyperellipse::Ry(void)
  {
    return this->m_r_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  hyperellipse::My(void)
  {
    return this->m_m_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  hyperellipse::Ly(void)
  {
    return this->m_l_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  hyperellipse::updateBounds(void)
  {
    this->shape::surfaceMaxRadius()       = this->m_r_x;
    this->shape::surfaceWidthLowerBound() = -this->m_l_y;
    this->shape::surfaceWidthUpperBound() = +this->m_l_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  hyperellipse::surfaceRadius(
    real y)
    const
  {
    this->checkWidthBound(y);
    real y_abs = std::abs(y);
    ENVE_ASSERT(y_abs <= this->m_l_y, "enve::surfaceRadius(y): y coordinate is out of hyperellipse overall volume.");
    return std::pow(1.0 - std::pow(y_abs / this->m_r_y, this->m_m_y), 1.0 / this->m_m_x) * this->m_r_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  hyperellipse::surfaceDerivative(
    real y,
    real tolerance)
    const
  {
    this->checkWidthBound(y);
    real y_abs = std::abs(y);
    if (y_abs > tolerance)
    {
      real sign  = y / std::abs(y);
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
  hyperellipse::surfaceAngle(
    real y,
    real tolerance)
    const
  {
    return std::atan(this->surfaceDerivative(y, tolerance));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  hyperellipse::print(
    out_stream &os)
    const
  {
    this->shape::print(os);
    os << "Shell hyperellipse parameters:" << std::endl
       << "\tR_x = " << this->m_r_x << " m" << std::endl
       << "\tm_x = " << this->m_m_x << std::endl
       << "\tR_y = " << this->m_r_y << " m" << std::endl
       << "\tm_y = " << this->m_m_y << std::endl
       << "\tL_y = " << this->m_l_y << " m" << std::endl
       << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_hyperellipse.cc
///