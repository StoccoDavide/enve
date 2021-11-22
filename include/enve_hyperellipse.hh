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
/// file: enve_hyperellipse.hh
///

#pragma once

#ifndef INCLUDE_ENVE_HYPERELLIPSE
#define INCLUDE_ENVE_HYPERELLIPSE

#include <acme.hh>
#include <acme_math.hh>
#include <acme_utils.hh>

#include "enve_shape.hh"

using namespace acme;

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

  //! Symmetric section hyperellipse
  class hyperellipse : public shape
  {
  public:
    typedef std::shared_ptr<hyperellipse const> ptr;    //!< Pointer to hyperellipse object
    typedef std::vector<hyperellipse::ptr>      vecptr; //!< Vector of pointers to hyperellipse objects

  private:
    real m_r_x = QUIET_NAN; //!< Section radius on x axis (m)
    real m_m_x = QUIET_NAN; //!< Section curve degree for x axis
    real m_r_y = QUIET_NAN; //!< Section radius on y axis (m)
    real m_m_y = QUIET_NAN; //!< Section curve degree for y axis
    real m_l_y = QUIET_NAN; //!< Section surface effective half width (m)

  public:
    //! Hyperellipse class destructor
    ~hyperellipse(void);

    //! Hyperellipse copy constructor
    hyperellipse(hyperellipse const &) = default;

    //! Hyperellipse move constructor
    hyperellipse(hyperellipse &&) = default;

    //! Hyperellipse class constructor
    hyperellipse(void);

    //! Hyperellipse class constructor
    hyperellipse(
      real r_x, //!< Surface radius on x axis (m)
      real m_x, //!< Surface curve degree for x axis
      real r_y, //!< Surface radius on y axis (m)
      real m_y, //!< Surface curve degree for y axis
      real l_y  //!< Surface half width on y axis (m)
    );

    //! Copy hyperellipse object
    void
    copy(
      hyperellipse const &hyperellipse_in //!< Hyperellipse object to be copied
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      hyperellipse const &hyperellipse_in,        //!< Input object
      real                tolerance = EPSILON_LOW //!< Tolerance
    ) const;

    //! Get hyperellipse radius on x axis const reference (m)
    real const &
    Rx(void) const;

    //! Get hyperellipse curve degree for x axis const reference
    real const &
    Mx(void) const;

    //! Get hyperellipse radius on y axis const reference (m)
    real const &
    Ry(void) const;

    //! Get hyperellipse curve degree for y axis const reference
    real const &
    My(void) const;

    //! Get hyperellipse half width on y axis const reference (m)
    real const &
    Ly(void) const;

    //! Get hyperellipse radius on x axis reference (m)
    real &
    Rx(void);

    //! Get hyperellipse curve degree for x axis reference
    real &
    Mx(void);

    //! Get hyperellipse radius on y axis reference (m)
    real &
    Ry(void);

    //! Get hyperellipse curve degree for y axis reference
    real &
    My(void);

    //! Get hyperellipse surface half width on y axis reference (m)
    real &
    Ly(void);

    //! Update shell shape bounds
    void
    updateBounds(void);

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

    //! Print hyperellipse data
    void
    print(
      out_stream &os //!< Output stream type
    ) const;

  }; // class hyperellipse

} // namespace enve

#endif

///
/// file: enve_hyperellipse.hh
///