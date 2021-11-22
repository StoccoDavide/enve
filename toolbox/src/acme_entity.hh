/*
(***********************************************************************)
(*                                                                     *)
(* The ACME project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Enrico Bertolazzi.       *)
(*                                                                     *)
(* The ACME project and its components are supplied under the terms of *)
(* the open source BSD 2-Clause License. The contents of the ACME      *)
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
/// file: acme_entity.hh
///

#pragma once

#ifndef INCLUDE_ACME_ENTITY
#define INCLUDE_ACME_ENTITY

#include "acme.hh"

namespace acme
{

  /*\
   |              _   _ _
   |    ___ _ __ | |_(_) |_ _   _
   |   / _ \ '_ \| __| | __| | | |
   |  |  __/ | | | |_| | |_| |_| |
   |   \___|_| |_|\__|_|\__|\__, |
   |                        |___/
  \*/

  //! Geometrical entity class container
  /**
   * Geometrical entity in 3D space.
   */
  class entity
  {
  public:
    typedef std::shared_ptr<entity> ptr;    //!< Shared pointer to entity object
    typedef std::vector<ptr>        vecptr; //!< Vector of pointers to entity objects

    //! Entity class destructor
    virtual ~entity(void);

    //! Entity class destructor
    entity(void);

    //! Translate entity by vector
    virtual void
    translate(
      vec3 const &input //!< Input translation vector
      ) = 0;

    //! Transform entity with affine transformation matrix
    virtual void
    transform(
      affine const &matrix //!< 4x4 affine transformation matrix
      ) = 0;

    //! Rotate entity by a rotation angle around an arbitrary axis
    void
    rotate(
      real        angle, //!< Input angle [rad]
      vec3 const &axis   //!< Input axis
    );

    //! Check if entity is degenerated
    virtual bool
    isDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const = 0;

    //! Return object hierarchical level
    virtual integer
    level(void) const = 0;

    //! Return object type as string
    virtual std::string
    type(void) const = 0;

    //! Check whether the object is an entity
    bool
    isEntity(void) const;

    //! Check whether the object is no entity
    virtual bool
    isNone(void) const = 0;

    //! Check whether the object is a point
    virtual bool
    isPoint(void) const = 0;

    //! Check whether the object is a line
    virtual bool
    isLine(void) const = 0;

    //! Check whether the object is a ray
    virtual bool
    isRay(void) const = 0;

    //! Check whether the object is a plane
    virtual bool
    isPlane(void) const = 0;

    //! Check whether the object is a segment
    virtual bool
    isSegment(void) const = 0;

    //! Check whether the object is a triangle
    virtual bool
    isTriangle(void) const = 0;

    //! Check whether the object is a disk
    virtual bool
    isDisk(void) const = 0;

    //! Check whether the object is a ball
    virtual bool
    isBall(void) const = 0;

    //! Check whether in the entity is clampable
    virtual bool
    isClampable(void) const = 0;

    //! Check whether in the entity is non clampable
    virtual bool
    isNonClampable(void) const = 0;

    //! Get minumum and maximum values along axes
    virtual bool
    clamp(
      vec3 &min, //!< Input minimum point
      vec3 &max  //!< Input maximum point
    ) const = 0;

    //! Get minumum and maximum values along axes
    virtual bool
    clamp(
      real &min_x, //!< Input x value of minimum point
      real &min_y, //!< Input y value of minimum point
      real &min_z, //!< Input z value of minimum point
      real &max_x, //!< Input x value of maximum point
      real &max_y, //!< Input y value of maximum point
      real &max_z  //!< Input z value of maximum point
    ) const = 0;

  }; // class entity

} // namespace acme

#endif

///
/// eof: acme_entity.hh
///