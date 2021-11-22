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
/// file: enve_shape.cc
///

#include "enve_shape.hh"

using namespace acme;

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
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shape::shape(
    real maxR,
    real minY,
    real maxY)
    : m_maxR(maxR),
      m_minY(minY),
      m_maxY(maxY)
  {
    ENVE_ASSERT(
      maxR > 0,
      "enve::shape::shape(maxR, minY, maxY): maximum radius must be positive.\n");
    ENVE_ASSERT(
      minY <= maxY,
      "enve::shape::shape(maxR, minY, maxY): inconsistent y axis bounds.\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shape::shape(
    vecN const &dataR,
    vecN const &dataY)
  {
    ENVE_ASSERT(
      dataR.size() == dataY.size(),
      "enve::polynom::fit(dataR, dataY, order): R and Y data vectors have different dimensions.\n");
    for (size_t i = 0; i < dataY.size(); ++i)
    {
      ENVE_ASSERT(
        dataR(i) > 0,
        "enve::shape::shape(dataR, dataY): R data vector components must be positive.\n");
    }
    this->m_maxR = dataR.maxCoeff();
    this->m_minY = dataY.minCoeff();
    this->m_maxY = dataY.maxCoeff();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shape::copy(
    shape const &shape_in)
  {
    this->m_maxR = shape_in.m_maxR;
    this->m_minY = shape_in.m_minY;
    this->m_maxY = shape_in.m_maxY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shape::isApprox(
    shape const &shape_in,
    real         tolerance)
    const
  {
    return acme::isApprox(this->m_maxR, shape_in.m_maxR, tolerance) &&
           acme::isApprox(this->m_minY, shape_in.m_minY, tolerance) &&
           acme::isApprox(this->m_maxY, shape_in.m_maxY, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::surfaceMaxRadius(void)
    const
  {
    return this->m_maxR;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  shape::surfaceMaxRadius(void)
  {
    return this->m_maxR;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shape::surfaceMaxWidth(void)
    const
  {
    return std::max(std::abs(this->m_minY), std::abs(this->m_maxY));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::surfaceWidthLowerBound(void)
    const
  {
    return this->m_minY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  shape::surfaceWidthLowerBound(void)
  {
    return this->m_minY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  shape::surfaceWidthUpperBound(void)
    const
  {
    return this->m_maxY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  shape::surfaceWidthUpperBound(void)
  {
    return this->m_maxY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shape::surfaceWidth(void)
    const
  {
    ENVE_ASSERT(this->m_minY <= this->m_maxY, "enve::shape::surfaceWidth(): inconsistent bounds\n");
    return this->m_maxY - this->m_minY;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shape::checkWidthBound(
    real y)
    const
  {
    if (this->m_minY <= y && y <= this->m_maxY)
    {
      return true;
    }
    else
    {
      ENVE_ERROR("enve::shape::checkWidthBound(y): input y is out of bound.\n")
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shape::print(
    out_stream &os)
    const
  {
    os << "Shell shape parameters:" << std::endl
       << "\tmaxR = " << this->m_maxR << " (m)" << std::endl
       << "\tminY = " << this->m_minY << " (m)" << std::endl
       << "\tmaxY = " << this->m_maxY << " (m)" << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_shape.cc
///