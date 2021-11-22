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
/// file: enve_flat.cc
///

#include "enve_flat.hh"

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

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    flat::~flat(void)
    {
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    flat::flat(void)
    {
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    flat::flat(
      real origin_x,
      real origin_y,
      real origin_z,
      real normal_x,
      real normal_y,
      real normal_z,
      real friction)
      : plane(origin_x, origin_y, origin_z, normal_x, normal_y, normal_z),
        m_friction(friction)
    {
      ENVE_ASSERT(normal_z > 0, "enve::ground::flat::flat(): normal z axis component must be positive.\n");
      this->plane::normalize();
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    flat::flat(
      point const &origin,
      vec3 const  &normal,
      real         friction)
      : plane(origin, normal),
        m_friction(friction)
    {
      ENVE_ASSERT(normal.z() > 0, "enve::ground::flat::flat(): normal z axis component must be positive.\n");
      this->plane::normalize();
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    flat::flat(
      plane const &plane_in,
      real         friction)
      : plane(plane_in),
        m_friction(friction)
    {
      ENVE_ASSERT(this->plane::normal().z() > 0, "enve::ground::flat::flat(): normal z axis component must be positive.\n");
      this->plane::normalize();
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    flat::copy(
      flat const &flat_in)
    {
      plane::operator  =(flat_in);
      this->m_friction = flat_in.m_friction;
      this->plane::normalize();
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool
    flat::isApprox(
      flat const &flat_in,
      real        tolerance)
      const
    {
      return this->plane::isApprox(flat_in) &&
             acme::isApprox(this->m_friction, flat_in.m_friction, tolerance);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    real const &
    flat::friction(void)
      const
    {
      return this->m_friction;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    real &
    flat::friction(void)
    {
      return this->m_friction;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    plane const &
    flat::layingPlane(void)
      const
    {
      return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    plane &
    flat::layingPlane(void)
    {
      return *this;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  } // namespace ground

} // namespace enve

///
/// file: enve_flat.cc
///