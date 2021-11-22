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
/// file: enve_points.hh
///

#pragma once

#ifndef INCLUDE_ENVE_POINTS
#define INCLUDE_ENVE_POINTS

#include <acme.hh>
#include <acme_math.hh>
#include <acme_utils.hh>

#include "enve_shape.hh"

using namespace acme;

namespace enve
{

  /*\
   |               _       _
   |   _ __   ___ (_)_ __ | |_ ___
   |  | '_ \ / _ \| | '_ \| __/ __|
   |  | |_) | (_) | | | | | |_\__ \
   |  | .__/ \___/|_|_| |_|\__|___/
   |  |_|
  \*/

  //! Raw points section shape
  class points : public shape
  {
  public:
    typedef std::shared_ptr<points const> ptr;    //!< Pointer to points object
    typedef std::vector<points::ptr>      vecptr; //!< Vector of pointers to points objects

  private:
    vecN m_dataR; //!< Vector of radius data (m)
    vecN m_dataY; //!< Vector of y data (m)

  public:
    //! Polynom class destructor
    ~points(void);

    //! Polynom copy constructor
    points(points const &) = default;

    //! Polynom move constructor
    points(points &&) = default;

    //! Polynom class constructor
    points(void);

    //! Polynom class constructor
    points(
      vecN const &dataR, //!< Vector of radius data (m)
      vecN const &dataY  //!< Vector of y data (m)
    );

    //! Copy points object
    void
    copy(
      points const &points_in //!< Polynom object to be copied
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      points const &points_in,              //!< Input object
      real          tolerance = EPSILON_LOW //!< Tolerance
    ) const;

    //! Get radius vector const reference (m)
    vecN const &
    dataR(void) const;

    //! Get radius vector const reference (m)
    real const &
    dataR(
      size_t i //!< Input i-th index
    ) const;

    //! Get width vector const reference (m)
    vecN const &
    dataY(void) const;

    //! Get width vector const reference (m)
    real const &
    dataY(
      size_t i //!< Input i-th index
    ) const;

    //! Get radius vector reference (m)
    vecN &
    dataR(void);

    //! Get radius vector reference (m)
    real &
    dataR(
      size_t i //!< Input i-th index
    );

    //! Get width vector reference (m)
    vecN &
    dataY(void);

    //! Get width vector reference (m)
    real &
    dataY(
      size_t i //!< Input i-th index
    );

    //! Get data vector size (m)
    size_t
    size(void) const;

    size_t
    lowerBound(
      real y //!< Coordinate of y axis
    ) const;

    size_t
    upperBound(
      real y //!< Coordinate of y axis
    ) const;

    //! Get surface of revolution rib radius at y axis coordinate
    real
    surfaceRadius(
      real y //!< Coordinate of y axis
    ) const override;

    //! Get surface of revolution rib first derivative with respect to y coordinate
    real
    surfaceDerivative(
      real y,                         //!< Coordinate of y axis
      real tolerance = EPSILON_MEDIUM //!< Tolerance
    ) const override;

    //! Get surface of revolution rib angle with respect to y axis (rad)
    real
    surfaceAngle(
      real y,                         //!< Coordinate of y axis
      real tolerance = EPSILON_MEDIUM //!< Tolerance
    ) const override;

    //! Print surface shape data
    void
    print(
      out_stream &os //!< Output stream type
    ) const;

  }; // class points

} // namespace enve

#endif

///
/// file: enve_points.hh
///