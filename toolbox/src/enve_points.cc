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
/// file: enve_points.cc
///

#include "enve_points.hh"

using namespace acme;

namespace enve
{

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  points::~points(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  points::points(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  points::points(
    vecN const &dataR,
    vecN const &dataY)
    : shape(dataR, dataY),
      m_dataR(dataR),
      m_dataY(dataY)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  points::copy(
    points const &points_in)
  {
    this->shape::copy(points_in);
    this->m_dataR = points_in.m_dataR;
    this->m_dataY = points_in.m_dataY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  points::isApprox(
    points const &points_in,
    real          tolerance)
    const
  {
    if (!this->shape::isApprox(points_in, tolerance))
      return false;
    if (this->m_dataR.size() != points_in.m_dataR.size() && this->m_dataY.size() != points_in.m_dataY.size())
      return false;
    return this->m_dataR.isApprox(points_in.m_dataR, tolerance) &&
           this->m_dataY.isApprox(points_in.m_dataY, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vecN const &
  points::dataR(void)
    const
  {
    return this->m_dataR;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  points::dataR(
    size_t i)
    const
  {
    return this->m_dataR(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vecN const &
  points::dataY(void)
    const
  {
    return this->m_dataY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  points::dataY(
    size_t i)
    const
  {
    return this->m_dataY(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vecN &
  points::dataR(void)
  {
    return this->m_dataR;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  points::dataR(
    size_t i)
  {
    return this->m_dataR(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vecN &
  points::dataY(void)
  {
    return this->m_dataY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  points::dataY(
    size_t i)
  {
    return this->m_dataY(i);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  size_t
  points::size(void)
    const
  {
    return this->m_dataY.size();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  size_t
  points::lowerBound(
    real y)
    const
  {
    this->checkWidthBound(y);
    size_t i;
    real   lower = ((this->m_dataY - vecN::Constant(this->m_dataY.size(), y)).cwiseAbs()).minCoeff(&i);
    if (lower - this->m_dataY(i) < 0)
      return i;
    else
      return i - 1;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  size_t
  points::upperBound(
    real y)
    const
  {
    this->checkWidthBound(y);
    size_t i;
    real   upper = ((this->m_dataY - vecN::Constant(this->m_dataY.size(), y)).cwiseAbs()).minCoeff(&i);
    if (this->m_dataY(i) - upper <= 0)
      return i;
    else
      return i + 1;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  points::surfaceRadius(
    real y)
    const
  {
    this->checkWidthBound(y);
    size_t lower = this->lowerBound(y);
    return this->m_dataR(lower) + surfaceDerivative(y) * (y - this->m_dataY(lower));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  points::surfaceDerivative(
    real y,
    real tolerance)
    const
  {
    this->checkWidthBound(y);
    size_t lower = this->lowerBound(y);
    size_t upper = this->upperBound(y);
    return (this->m_dataR(upper) - this->m_dataR(lower)) / (this->m_dataY(upper) - this->m_dataY(lower));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  points::surfaceAngle(
    real y,
    real tolerance)
    const
  {
    return std::atan(this->surfaceDerivative(y, tolerance));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  points::print(
    out_stream &os) const
  {
    this->shape::print(os);
    os << "Shell points parameters:" << std::endl;
    for (size_t i = 0; i < this->m_dataR.size(); ++i)
    {
      os << "\tR(" << i << ") = " << this->m_dataR(i)
         << "\tY(" << i << ") = " << this->m_dataY(i)
         << std::endl;
    }
    os << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_points.cc
///