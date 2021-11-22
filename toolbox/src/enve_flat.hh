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
/// file: enve_flat.hh
///

#pragma once

#ifndef INCLUDE_ENVE_FLAT
#define INCLUDE_ENVE_FLAT

#include <acme.hh>
#include <acme_plane.hh>

#include "enve.hh"

using namespace acme;

namespace enve
{

  namespace ground
  {

    /*\
     |    __ _       _
     |   / _| | __ _| |_
     |  | |_| |/ _` | __|
     |  |  _| | (_| | |_
     |  |_| |_|\__,_|\__|
     |
    \*/

    //! Triangular flat class
    class flat : public plane
    {
    public:
      typedef std::shared_ptr<flat const> ptr;    //!< Shared pointer to flat object
      typedef std::vector<flat::ptr>      vecptr; //!< Vector of shared pointers to flat objects

    private:
      real m_friction = QUIET_NAN; //!< Face friction coefficient scaling factor

      flat(flat const &) = delete; //!< Deleted copy constructor

    public:
      //! Flat class destructor
      ~flat(void);

      //! Flat class constructor
      flat(void);

      //! Flat class constructor
      flat(
        real origin_x, //!< Input x value of ground plane origin point
        real origin_y, //!< Input y value of ground plane origin point
        real origin_z, //!< Input z value of ground plane origin point
        real normal_x, //!< Input x value of ground plane normal vector
        real normal_y, //!< Input y value of ground plane normal vector
        real normal_z, //!< Input z value of ground plane normal vector
        real friction  //!< Friction coefficient scaling factor
      );

      //! Flat class constructor
      flat(
        point const &origin,  //!< Input plane origin point
        vec3 const  &normal,  //!< Input plane normal vector
        real         friction //!< Friction coefficient scaling factor
      );

      //! Flat class constructor
      flat(
        plane const &plane_in, //!< Input flat object
        real         friction  //!< Friction coefficient scaling factor
      );

      //! Copy flat object
      void
      copy(
        flat const &flat_in //!< Flat object to be copied
      );

      //! Check if objects are (almost) equal
      bool
      isApprox(
        flat const &flat_in,                //!< Input flat object
        real        tolerance = EPSILON_LOW //!< Tolerance
      ) const;

      //! Get friction coefficent scaling factor const reference
      real const &
      friction(void) const;

      //! Set friction coefficent scaling factor reference
      real &
      friction(void);

      //! Get laying plane
      plane const &
      layingPlane(void) const;

      //! Set laying plane
      plane &
      layingPlane(void);
    };

  } // namespace ground

} // namespace enve

#endif

///
/// eof: enve_flat.hh
///