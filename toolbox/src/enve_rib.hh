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
/// file: enve_rib.hh
///

#pragma once

#ifndef INCLUDE_ENVE_RIB
#define INCLUDE_ENVE_RIB

#include <acme.hh>
#include <acme_disk.hh>
#include <acme_utils.hh>

#include "enve.hh"

using namespace acme;

namespace enve
{

  /*\
   |        _ _
   |   _ __(_) |__
   |  | '__| | '_ \
   |  | |  | | |_) |
   |  |_|  |_|_.__/
   |
  \*/

  //! Rib for wheel representation
  class rib : public disk
  {
  public:
    typedef std::shared_ptr<rib const> ptr;    //!< Pointer to rib object
    typedef std::vector<rib::ptr>      vecptr; //!< Vector of pointers to rib objects

  private:
    real m_width; //!< Rib width (m)
    real m_angle; //!< Rib inclination angle (rad)

  public:
    //! Rib class destructor
    ~rib(void);

    //! Rib copy constructor
    rib(rib const &) = default;

    //! Rib move constructor
    rib(rib &&) = default;

    //! Rib class constructor
    rib(void);

    //! Rib class constructor
    rib(real         radius, //!< Input rib radius
        plane const &plane,  //!< Input rib laying plane
        real         width,  //!< Input rib normal to the laying plane
        real         angle   //!< Input rib normal to the laying plane
    );

    //! Rib class constructor
    rib(real         radius, //!< Input rib radius
        plane const &plane   //!< Input rib laying plane
    );

    //! Rib class constructor
    rib(
      real         radius, //!< Input rib radius
      point const &center, //!< Input rib center
      vec3 const  &normal, //!< Input rib normal to the laying plane
      real         width,  //!< Input rib normal to the laying plane
      real         angle   //!< Input rib normal to the laying plane
    );

    //! Rib class constructor
    rib(
      real         radius, //!< Input rib radius
      point const &center, //!< Input rib center
      vec3 const  &normal  //!< Input rib normal to the laying plane
    );

    //! Rib class constructor
    rib(real radius,   //!< Input rib radius
        real center_x, //!< Input rib center x value
        real center_y, //!< Input rib center y value
        real center_z, //!< Input rib center z value
        real normal_x, //!< Input rib normal x value to the laying plane
        real normal_y, //!< Input rib normal y value to the laying plane
        real normal_z, //!< Input rib normal z value to the laying plane
        real width,    //!< Input rib normal to the laying plane
        real angle     //!< Input rib normal to the laying plane
    );

    //! Rib class constructor
    rib(real radius,   //!< Input rib radius
        real center_x, //!< Input rib center x value
        real center_y, //!< Input rib center y value
        real center_z, //!< Input rib center z value
        real normal_x, //!< Input rib normal x value to the laying plane
        real normal_y, //!< Input rib normal y value to the laying plane
        real normal_z  //!< Input rib normal z value to the laying plane
    );

    //! Equality operator
    rib &
    operator=(
      rib const &rib_in //!< Input rib object
    );

    //! Copy rib object
    void
    copy(
      rib const &rib_in //!< Input object
    );

    //! Get width coefficent scaling factor const reference (m)
    real const &
    width(void) const;

    //! Get angle coefficent scaling factor const reference (rad)
    real const &
    angle(void) const;

    //! Set width coefficient scaling factor reference (m)
    real &
    width(void);

    //! Set angle coefficient scaling factor reference (rad)
    real &
    angle(void);

    //! Check if objects are (almost) equal
    bool
    isApprox(
      rib const &rib_in,                 //!< Input object
      real       tolerance = EPSILON_LOW //!< Tolerance
    ) const;

  }; // class rib

} // namespace enve

#endif

///
/// file: enve_rib.hh
///