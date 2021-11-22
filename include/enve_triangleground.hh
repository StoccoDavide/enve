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
/// file: enve_triangleground.hh
///

#pragma once

#ifndef INCLUDE_ENVE_TRIANGLEGROUND
#define INCLUDE_ENVE_TRIANGLEGROUND

#include <acme.hh>
#include <acme_aabb.hh>
#include <acme_intersection.hh>
#include <acme_segment.hh>
#include <acme_triangle.hh>

#include "enve.hh"

using namespace acme;

namespace enve
{

  /*\
   |   _        _                   _                          _
   |  | |_ _ __(_) __ _ _ __   __ _| | ___ _ __ ___   __ _  __| |
   |  | __| '__| |/ _` | '_ \ / _` | |/ _ \ '__/ _ \ / _` |/ _` |
   |  | |_| |  | | (_| | | | | (_| | |  __/ | | (_) | (_| | (_| |
   |   \__|_|  |_|\__,_|_| |_|\__, |_|\___|_|  \___/ \__,_|\__,_|
   |                          |___/
  \*/

  //! 3D triangles for ground representation
  class triangleground : public triangle
  {
  public:
    typedef std::shared_ptr<triangleground const> ptr;    //!< Pointer to triangleground object
    typedef std::vector<triangleground::ptr>      vecptr; //!< Vector of pointers to triangleground objects

  private:
    real m_friction; //!< Face friction coefficient scaling factor
    vec3 m_normal;   //!< Precalculated face normal
    aabb m_bbox;     //!< Triangle bounding aabb

  public:
    //! Triangleground class destructor
    ~triangleground(void);

    //! Triangleground copy constructor
    triangleground(triangleground const &) = delete;

    //! Triangleground move constructor
    triangleground(triangleground &&) = delete;

    //! Triangleground class constructor
    triangleground(void);

    //! Triangleground class constructor
    triangleground(
      real vertex0_x, //!< Input x value of first triangle vertex
      real vertex0_y, //!< Input y value of first triangle vertex
      real vertex0_z, //!< Input z value of first triangle vertex
      real vertex1_x, //!< Input x value of second triangle vertex
      real vertex1_y, //!< Input y value of second triangle vertex
      real vertex1_z, //!< Input z value of second triangle vertex
      real vertex2_x, //!< Input x value of third triangle vertex
      real vertex2_y, //!< Input y value of third triangle vertex
      real vertex2_z, //!< Input z value of third triangle vertex
      real friction   //!< Friction coefficient scaling factor
    );

    //! Triangleground class constructor
    triangleground(
      point const &point0,  //!< Input first triangle vertex point
      point const &point1,  //!< Input second triangle vertex point
      point const &point2,  //!< Input third triangle vertex point
      real         friction //!< Friction coefficient scaling factor
    );

    //! Triangleground class constructor
    triangleground(
      point const vertex[3], //!< Vertices points
      real        friction   //!< Friction coefficient scaling factor
    );

    //! Copy triangleground object
    void
    copy(
      triangleground const &triangleground_in //!< Input object
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      triangleground const &triangleground_in,      //!< Input object
      real                  tolerance = EPSILON_LOW //!< Tolerance
    ) const;

    //! Equality operator
    triangle &
    operator=(
      triangle const &triangle_in //!< Input triangle object
      ) = delete;

    //! Set friction coefficient scaling factor reference
    real &
    friction(void);

    //! Get friction coefficent scaling factor const reference
    real const &
    friction(void) const;

    //! Get triangle axis-aligned bounding box
    aabb const &
    bbox(void) const;

    //! Get face (normalized) normal
    vec3 const &
    normal(void) const;

    //! Precalculate triangle face normal vector (positive z component)
    void
    updateNormal(void);

    //! Get i-th triangle vertex const reference
    point const &
    operator[](
      size_t i //!< Triangle index (i-th trinagle)
    ) const;

    //! Get i-th triangle vertex const reference
    point const &
    vertex(
      size_t i //!< Triangle index (i-th trinagle)
    ) const;

  private:
    //! Hide get i-th triangle vertex reference
    point &
    operator[](
      size_t i //!< Triangle index (i-th trinagle)
    );

    //! Hide get i-th triangle vertex reference
    point &
    vertex(
      size_t i //!< Triangle index (i-th trinagle)
    );

  }; // class triangleground

} // namespace enve

#endif

///
/// file: enve_triangleground.hh
///