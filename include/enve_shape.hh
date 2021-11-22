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
/// file: enve_shape.hh
///

#pragma once

#ifndef INCLUDE_ENVE_SHAPE
#define INCLUDE_ENVE_SHAPE

#include <acme.hh>
#include <acme_math.hh>

#include "enve.hh"

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

  //! Shell surface geometry
  class shape
  {
  public:
    typedef std::shared_ptr<shape const> ptr;    //!< Pointer to shape object
    typedef std::vector<shape::ptr>      vecptr; //!< Vector of pointers to shape objects
  private:
    real m_maxR = QUIET_NAN; //!< Maximum surface maximum radius (m)
    real m_minY = QUIET_NAN; //!< Minimum surface bound on y axis (m)
    real m_maxY = QUIET_NAN; //!< Maximum surface bound on y axis (m)

  public:
    //! Shape class destructor
    virtual ~shape(void){};

    //! Shape class constructor
    shape(void);

    //! Shape class constructor
    shape(
      real maxR, //!< Maximum surface maximum radius (m)
      real minY, //!< Minimum surface bound on y axis (m)
      real maxY  //!< Maximum surface bound on y axis (m)
    );

    //! Shape class constructor
    shape(
      vecN const &dataR, //!< Vector of radius data (m)
      vecN const &dataY  //!< Vector of y data (m)
    );

    //! Copy shape object
    void
    copy(
      shape const &shape_in //!< Shape object to be copied
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      shape const &shape_in,               //!< Shape object
      real         tolerance = EPSILON_LOW //!< Tolerance
    ) const;

    //! Get surface maximum radius const reference (m)
    real const &
    surfaceMaxRadius(void) const;

    //! Get surface maximum radius on reference (m)
    real &
    surfaceMaxRadius(void);

    //! Get surface maximum width on y axis (m)
    real
    surfaceMaxWidth(void) const;

    //! Get surface minimum width const reference (m)
    real const &
    surfaceWidthLowerBound(void) const;

    //! Get surface minimum width on reference (m)
    real &
    surfaceWidthLowerBound(void);

    //! Get surface maximum width const reference (m)
    real const &
    surfaceWidthUpperBound(void) const;

    //! Get surface maximum width on reference (m)
    real &
    surfaceWidthUpperBound(void);

    //! Get surface width (m)
    real
    surfaceWidth(void) const;

    //! Get surface maximum width on reference (m)
    bool
    checkWidthBound(
      real y //!< Coordinate of y axis
    ) const;

    //! Get surface of revolution rib radius at y axis coordinate
    virtual real
    surfaceRadius(
      real y //!< Coordinate of y axis
    ) const = 0;

    //! Get surface of revolution rib first derivative with respect to y coordinate
    virtual real
    surfaceDerivative(
      real y,                         //!< Coordinate of y axis
      real tolerance = EPSILON_MEDIUM //!< Tolerance
    ) const = 0;

    //! Get surface of revolution rib angle with respect to y axis (rad)
    virtual real
    surfaceAngle(
      real y,                         //!< Coordinate of y axis
      real tolerance = EPSILON_MEDIUM //!< Tolerance
    ) const = 0;

    //! Print surface shape data
    void
    print(
      out_stream &os //!< Output stream type
    ) const;

  }; // class shape

} // namespace enve

#endif

///
/// file: enve_shape.hh
///