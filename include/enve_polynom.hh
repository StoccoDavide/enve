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
/// file: enve_polynom.hh
///

#pragma once

#ifndef INCLUDE_ENVE_POLYNOM
#define INCLUDE_ENVE_POLYNOM

#include <acme.hh>
#include <acme_math.hh>
#include <acme_utils.hh>

#include "enve_shape.hh"

using namespace acme;

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

  //! Polynomial section shape
  class polynom : public shape
  {
  public:
    typedef std::shared_ptr<polynom const> ptr;    //!< Pointer to polynom object
    typedef std::vector<polynom::ptr>      vecptr; //!< Vector of pointers to polynom objects

  private:
    vecN m_coeffs; //!< Polynomial regression coefficients

  public:
    //! Polynom class destructor
    ~polynom(void);

    //! Polynom copy constructor
    polynom(polynom const &) = default;

    //! Polynom move constructor
    polynom(polynom &&) = default;

    //! Polynom class constructor
    polynom(void);

    //! Polynom class constructor
    polynom(
      vecN coeffs, //!< Polynomial regression coefficients
      real maxR,   //!< Maximum surface maximum radius (m)
      real minY,   //!< Minimum surface bound on y axis (m)
      real maxY    //!< Maximum surface bound on y axis (m)
    );

    //! Polynom class constructor
    polynom(
      vecN const &dataR,                     //!< Vector of radius data (m)
      vecN const &dataY,                     //!< Vector of y data (m)
      size_t      order,                     //!< Polynom order
      real        tolerance = EPSILON_MEDIUM //!< Tolerance
    );

    //! Copy polynom object
    void
    copy(
      polynom const &polynom_in //!< Polynom object to be copied
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      polynom const &polynom_in,             //!< Input object
      real           tolerance = EPSILON_LOW //!< Tolerance
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

    void
    fit(
      vecN   dataR,                     //!< Vector of radius data (m)
      vecN   dataY,                     //!< Vector of y data (m)
      size_t order,                     //!< Polynom order
      real   tolerance = EPSILON_MEDIUM //!< Tolerance
    );

  }; // class polynom

} // namespace enve

#endif

///
/// file: enve_polynom.hh
///