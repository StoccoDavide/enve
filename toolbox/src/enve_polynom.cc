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
/// file: enve_polynom.cc
///

#include "enve_polynom.hh"

namespace enve
{

  /*\
   |               _
   |   _ __   ___ | |_   _ _ __   ___  _ __ ___
   |  | '_ \ / _ \| | | | | '_ \ / _ \| '_ ` _ \
   |  | |_) | (_) | | |_| | | | | (_) | | | | | |
   |  | .__/ \___/|_|\__, |_| |_|\___/|_| |_| |_|
   |  |_|            |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  polynom::~polynom(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  polynom::polynom(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  polynom::polynom(
    vecN coeffs,
    real maxR,
    real minY,
    real maxY)
    : shape(maxR, minY, maxY),
      m_coeffs(coeffs)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  polynom::polynom(
    vecN const &dataR,
    vecN const &dataY,
    size_t      order,
    real        tolerance)
    : shape(dataR, dataY)
  {
    this->fit(dataR, dataY, order, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  polynom::copy(
    polynom const &polynom_in)
  {
    this->shape::copy(polynom_in);
    this->m_coeffs = polynom_in.m_coeffs;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  polynom::isApprox(
    polynom const &polynom_in,
    real           tolerance)
    const
  {
    if (!this->shape::isApprox(polynom_in))
      return false;
    if (this->m_coeffs.size() != polynom_in.m_coeffs.size())
      return false;
    return this->m_coeffs.isApprox(polynom_in.m_coeffs, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  polynom::surfaceRadius(
    real y)
    const
  {
    this->checkWidthBound(y);
    real y_val = 0.0;
    for (size_t i = 0; i < this->m_coeffs.size(); ++i)
      y_val += this->m_coeffs[i] * std::pow(y, i);
    return y_val;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  polynom::surfaceDerivative(
    real y,
    real tolerance)
    const
  {
    this->checkWidthBound(y);
    real y_der = 0.0;
    for (size_t i = 0; i < this->m_coeffs.size(); ++i)
      y_der += this->m_coeffs(i) * std::pow(y, i - 1);
    return y_der;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  polynom::surfaceAngle(
    real y,
    real tolerance)
    const
  {
    return std::atan(this->surfaceDerivative(y, tolerance));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  polynom::print(
    out_stream &os)
    const
  {
    this->shape::print(os);
    os << "Shell polynom parameters:" << std::endl;
    for (size_t i = 0; i < this->m_coeffs.size(); ++i)
      os << "\tcoeff(" << i << ") = " << this->m_coeffs(i) << std::endl;
    os << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  polynom::fit(
    vecN   dataR,
    vecN   dataY,
    size_t order,
    real   tolerance)
  {
    ENVE_ASSERT(
      dataR.size() == dataY.size(),
      "enve::polynom::fit(dataR, dataY, order): R and Y data vectors have different dimensions.\n");
    ENVE_ASSERT(
      order >= 1 && order <= dataR.size() - 1,
      "enve::polynom::fit(dataR, dataY, order): invalid polynom order.\n");

    matN A(dataY.size(), order + 1);

    for (size_t i = 0; i < dataY.size(); ++i)
    {
      ENVE_ASSERT(
        dataR(i) > 0,
        "enve::polynom::fit(dataR, dataY, order): R data vector components must be positive.\n");

      for (size_t j = 0; j < order + 1; ++j)
        A(i, j) = std::pow(dataY(i), j);
    }
    this->m_coeffs = A.householderQr().solve(dataR);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_polynom.cc
///