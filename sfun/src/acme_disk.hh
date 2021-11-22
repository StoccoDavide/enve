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
/// file: acme_disk.hh
///

#pragma once

#ifndef INCLUDE_ACME_DISK
#define INCLUDE_ACME_DISK

#include "acme.hh"
#include "acme_aabb.hh"
#include "acme_plane.hh"
#include "acme_point.hh"

namespace acme
{

  /*\
   |       _ _     _
   |    __| (_)___| | __
   |   / _` | / __| |/ /
   |  | (_| | \__ \   <
   |   \__,_|_|___/_|\_\
   |
  \*/

  //! Disk class container
  /**
   * Disk in 3D space and defined by a radius and a plane (disk center + normal vector).
   */
  class disk : public entity
  {
  private:
    real  m_radius = QUIET_NAN; //!< Disk radius
    plane m_plane  = NAN_PLANE; //!< Disk plane (disk center + normal vector)

  public:
    //! Disk class deconstructor
    ~disk(void);

    //! Disk class constructor
    disk(void);

    //! Disk copy constructor
    disk(disk const &) = default;

    //! Disk move constructor
    disk(disk &&) = default;

    //! Disk class constructor
    disk(
      real         radius, //!< Input disk radius
      plane const &plane   //!< Input disk laying plane
    );

    //! Disk class constructor
    disk(
      real         radius, //!< Input disk radius
      point const &center, //!< Input disk center
      vec3 const  &normal  //!< Input disk normal to the laying plane
    );

    //! Disk class constructor
    disk(
      real radius,   //!< Input disk radius
      real center_x, //!< Input disk center x value
      real center_y, //!< Input disk center y value
      real center_z, //!< Input disk center z value
      real normal_x, //!< Input disk normal x value to the laying plane
      real normal_y, //!< Input disk normal y value to the laying plane
      real normal_z  //!< Input disk normal z value to the laying plane
    );

    //! Equality operator
    disk &
    operator=(
      disk const &disk_in //!< Input disk object
    );

    //! Check if disks are (almost) equal
    bool
    isApprox(
      disk const &disk_in,            //!< Input disk object
      real        tolerance = EPSILON //!< Tolerance
    ) const;

    //! Get disk radius const reference
    real const &
    radius(void) const;

    //! Get disk radius reference
    real &
    radius(void);

    //! Get disk center point const reference
    point const &
    center(void) const;

    //! Get disk center point reference
    point &
    center(void);

    //! Get disk laying plane normal vector const reference
    vec3 const &
    normal(void) const;

    //! Get disk laying plane normal vector reference
    vec3 &
    normal(void);

    //! Get cicle laying plane const reference
    plane const &
    layingPlane(void) const;

    //! Get cicle laying plane reference
    plane &
    layingPlane(void);

    //! Normalize disk normal vector
    void
    normalize(void);

    //! Reverse disk normal vector
    void
    reverse(void);

    //! Calculate disk circumference length
    real
    perimeter(void)
      const;

    //! Calculate disk area
    real
    area(void) const;

    //! Translate by vector
    void
    translate(
      vec3 const &vector_in //!< Input translation vector
      ) override;

    //! Transform disk with affine transformation matrix
    void
    transform(
      affine const &affine_in //!< 4x4 affine transformation matrix
      ) override;

    // Check whether the point is inside the disk
    bool
    isInside(
      point const &point_in,           //!< Query point
      real         tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check if disk is degenerated
    bool
    isDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const override;

    //! Return object hierarchical level
    integer
    level(void) const override
    {
      return 8;
    }

    //! Return object type as string
    std::string
    type(void) const override
    {
      return "disk";
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
      return false;
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
      return true;
    }

    //! Check whether the object is a ball
    bool
    isBall(void) const override
    {
      return false;
    }

    //! Check whether in the disk is clampable
    bool
    isClampable(void) const override
    {
      return true;
    }

    //! Check whether in the disk is non-clampable
    bool
    isNonClampable(void) const override
    {
      return false;
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

  }; // class disk

  static disk const NAN_DISK       = disk(QUIET_NAN, NAN_PLANE); //!< Not-a-Number static const disk object
  static disk       THROWAWAY_DISK = disk(NAN_DISK);             //!< Throwaway static non-const disk object

} // namespace acme

#endif

///
/// eof: acme_disk.hh
///