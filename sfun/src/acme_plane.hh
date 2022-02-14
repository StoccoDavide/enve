/*
(***********************************************************************)
(*                                                                     *)
(* The ACME project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *)
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
/// file: acme_plane.hh
///

#pragma once

#ifndef INCLUDE_ACME_PLANE
#define INCLUDE_ACME_PLANE

#include "acme.hh"
#include "acme_point.hh"

namespace acme
{

  /*\
   |         _
   |   _ __ | | __ _ _ __   ___
   |  | '_ \| |/ _` | '_ \ / _ \
   |  | |_) | | (_| | | | |  __/
   |  | .__/|_|\__,_|_| |_|\___|
   |  |_|
  \*/

  //! Plane class container
  /**
   * 3D plane defined by the normal vector to plane and an arbitraty point laying on the plane.
   */
  class plane : public entity
  {
  private:
    point m_origin = NAN_POINT; //!< Plane origin point
    vec3  m_normal = NAN_VEC3;  //!< Plane normal vector

  public:
    //! Plane class destructor
    ~plane();

    //! Plane class constructor
    plane();

    //! Plane copy constructor
    plane(plane const &) = default;

    //! Plane move constructor
    plane(plane &&) = default;

    //! Plane class constructor for plane
    plane(
      real origin_x, //!< Input x value of plane origin point
      real origin_y, //!< Input y value of plane origin point
      real origin_z, //!< Input z value of plane origin point
      real normal_x, //!< Input x value of plane normal vector
      real normal_y, //!< Input y value of plane normal vector
      real normal_z  //!< Input z value of plane normal vector
    );

    //! Plane class constructor
    plane(
      point const &origin, //!< Input plane origin point
      vec3 const  &normal  //!< Input plane normal vector
    );

    //! Equality operator
    plane &
    operator=(
      plane const &plane_in //!< Input plane object
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      plane const &plane_in,           //!< Input plane object
      real         tolerance = EPSILON //!< Tolerance
    ) const;

    //! Return plane origin point const reference
    point const &
    origin(void) const;

    //! Return plane origin point reference
    point &
    origin(void);

    //! Return plane normal vector const reference
    vec3 const &
    normal(void) const;

    //! Return plane normal vector reference
    vec3 &
    normal(void);

    //! Return plane normal unit vector
    vec3
    unitNormal(void) const;

    //! Normalize plane normal vector
    void
    normalize(void);

    //! Return plane equation d value (ax + by + cz + d = 0)
    real
    d(void) const;

    //! Distance between point and plane
    real
    distance(
      point const &point_in //!< Input
    ) const;

    //! Squared distance between point and plane
    real
    squaredDistance(
      point const &point_in //!< Input
    ) const;

    //! Signed distance between point and plane
    real
    signedDistance(
      point const &point_in //!< Input
    ) const;

    //! Reverse plane normal vector
    void
    reverse(void);

    //! Translate plane by vector
    void
    translate(
      vec3 const &vector_in //!< Input translation vector
      ) override;

    //! Transform plane from with affine transformation matrix
    void
    transform(
      affine const &affine_in //!< 4x4 affine transformation matrix
      ) override;

    // Check whether a point lays on the plane
    bool
    isInside(
      point const &point_in,           //!< Query point
      real         tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check if plane is degenerated (normal has zero norm)
    bool
    isDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const override;

    //! Return object hierarchical level
    integer
    level(void) const override
    {
      return 5;
    }

    //! Return object type as string
    std::string
    type(void) const override
    {
      return "plane";
    }

    //! Check whether the object is no entity
    bool
    isNone(void) const override
    {
      return false;
    }

    //! Check whether the object is a point
    bool
    isPoint(void) const override
    {
      return false;
    }

    //! Check whether the object is a line
    bool
    isLine(void) const override
    {
      return false;
    }

    //! Check whether the object is a ray
    bool
    isRay(void) const override
    {
      return false;
    }

    //! Check whether the object is a plane
    bool
    isPlane(void) const override
    {
      return true;
    }

    //! Check whether the object is a segment
    bool
    isSegment(void) const override
    {
      return false;
    }

    //! Check whether the object is a triangle
    bool
    isTriangle(void) const override
    {
      return false;
    }

    //! Check whether the object is a disk
    bool
    isDisk(void) const override
    {
      return false;
    }

    //! Check whether the object is a ball
    bool
    isBall(void) const override
    {
      return false;
    }

    //! Check whether in the plane is clampable
    bool
    isClampable(void) const override
    {
      return false;
    }

    //! Check whether in the plane is non-clampable
    bool
    isNonClampable(void) const override
    {
      return true;
    }

    //! Get minumum and maximum values along axes
    bool
    clamp(
      vec3 &min, //!< Input minimum point
      vec3 &max  //!< Input maximum point
    ) const override;

    //! Get minumum and maximum values along axes
    bool
    clamp(
      real &min_x, //!< Input x value of minimum point
      real &min_y, //!< Input y value of minimum point
      real &min_z, //!< Input z value of minimum point
      real &max_x, //!< Input x value of maximum point
      real &max_y, //!< Input y value of maximum point
      real &max_z  //!< Input z value of maximum point
    ) const override;

  }; // class plane

  static plane const NAN_PLANE  = plane(NAN_POINT, NAN_VEC3); //!< Not-a-Number static const plane object
  static plane       plane_goat = plane(NAN_PLANE);           //!< Throwaway static non-const plane object

} // namespace acme

#endif

///
/// eof: acme_plane.hh
///