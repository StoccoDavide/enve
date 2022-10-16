/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * This file is part of the ENVE project.                              *
 *                                                                     *
 * Copyright (c) 2022, Davide Stocco. All rights reserved.             *
 *                                                                     *
 * The ENVE project can not be copied and/or distributed without       *
 * the express permission of Davide Stocco.                            *
 *                                                                     *
 *    Davide Stocco                                                    *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: davide.stocco@unitn.it                                   *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: shape.cc
///

#include "enve.hh"

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

  shape::shape(void)
    : m_r_x(QUIET_NAN),
      m_m_x(QUIET_NAN),
      m_r_y(QUIET_NAN),
      m_m_y(QUIET_NAN),
      m_l_y(QUIET_NAN)
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
    shape const & shape_obj
  )
  {
    this->m_r_x = shape_obj.m_r_x;
    this->m_m_x = shape_obj.m_m_x;
    this->m_r_y = shape_obj.m_r_y;
    this->m_m_y = shape_obj.m_m_y;
    this->m_l_y = shape_obj.m_l_y;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shape::isApprox(
    shape const & shape_obj,
    real          tolerance 
  )
    const
  {
    return IsApprox(this->m_r_x, shape_obj.m_r_x, tolerance) &&
           IsApprox(this->m_m_x, shape_obj.m_m_x, tolerance) &&
           IsApprox(this->m_r_y, shape_obj.m_r_y, tolerance) &&
           IsApprox(this->m_m_y, shape_obj.m_m_y, tolerance) &&
           IsApprox(this->m_l_y, shape_obj.m_l_y, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  shape::Rx(void)
  {
    return this->m_r_x;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::Rx(void)
    const
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

  real const &
  shape::Mx(void)
    const
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

  real const &
  shape::Ry(void)
    const
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

  real const &
  shape::My(void)
    const
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
  shape::Ly(void)
    const
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
      {return false;}
    else
      {return true;}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shape::surfaceRadius(
    real y
  )
    const
  {
    #define CMD "enve::surfaceRadius(...): "

    ENVE_ASSERT(this->checkWidthBound(y),
      CMD "y coordinate is ouside the interval [-Ly, Ly].");
    return this->m_r_x * std::pow(real(1.0)-std::pow(std::abs(y)/this->m_r_y, this->m_m_y), real(1.0)/this->m_m_x);

    #undef CMD
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
    #define CMD "enve::surfaceDerivative(...): "

    ENVE_ASSERT(this->checkWidthBound(y),
      CMD "y coordinate is ouside the interval [-Ly, Ly].");

    // FIXME: efficient but is it robust?
    real y_abs = std::abs(y);
    if (y_abs > tolerance)
    {
      real sign  = real(real(0.0) < y) - real(y < real(0.0));
      real y_val = sign * y;
      real y_pre = std::pow(y_val/this->m_r_y, this->m_m_y);
      return -sign * std::pow(real(1.0)-y_pre, (real(1.0)-this->m_m_x)/this->m_m_x) * 
             y_pre * this->m_r_x * this->m_m_y / (this->m_m_x * y_val);
    }
    else
    {
      return real(0.0);
    }

    #undef CMD
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
    out_stream & os
  )
    const
  {
    os
      << "SHAPE DATA" << std::endl
      << "\t Rx = " << this->m_r_x << "\t : real - Section radius on x axis (m)" << std::endl
      << "\t Mx = " << this->m_m_x << "\t : real - Section curve degree for x axis (-)" << std::endl
      << "\t Ry = " << this->m_r_y << "\t : real - Section radius on y axis (m)" << std::endl
      << "\t My = " << this->m_m_y << "\t : real - Section curve degree for y axis (-)" << std::endl
      << "\t Ly = " << this->m_l_y << "\t : real - Section surface effective half width (m)" << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// eof: shape.cc
///
