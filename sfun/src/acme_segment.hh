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
/// file: acme_segment.hh
///

#pragma once

#ifndef INCLUDE_ACME_SEGMENT
#define INCLUDE_ACME_SEGMENT

#include "acme.hh"
#include "acme_aabb.hh"
#include "acme_point.hh"

namespace acme
{

  /*\
   |                                       _
   |   ___  ___  __ _ _ __ ___   ___ _ __ | |_
   |  / __|/ _ \/ _` | '_ ` _ \ / _ \ '_ \| __|
   |  \__ \  __/ (_| | | | | | |  __/ | | | |_
   |  |___/\___|\__, |_| |_| |_|\___|_| |_|\__|
   |            |___/
  \*/

  //! Segment class container
  /**
   * Segment in 3D space. The segment is defined by two arbitrary points.
   */
  class segment : public entity
  {
  private:
    point m_vertex[2] = {NAN_POINT, NAN_POINT}; //!< Segment extrema points

  public:
    //! Segment class destructor
    ~segment(void);

    //! Segment class constructor
    segment(void);

    //! Segment copy constructor
    segment(segment const &) = default;

    //! Segment move constructor
    segment(segment &&) = default;

    //! Segment class constructor
    segment(
      real vertex0_x, //!< Input x value of first segment vertex
      real vertex0_y, //!< Input y value of first segment vertex
      real vertex0_z, //!< Input z value of first segment vertex
      real vertex1_x, //!< Input x value of second segment vertex
      real vertex1_y, //!< Input y value of second segment vertex
      real vertex1_z  //!< Input z value of second segment vertex
    );

    //! Segment class constructor
    segment(
      point const &vertex0, //!< Input first segment vertex
      point const &vertex1  //!< Input second segment vertex
    );

    //! Segment class constructor
    segment(
      point const vertex[2] //!< Input segment vertices
    );

    //! Equality operator
    segment &
    operator=(
      segment const &segment_in //!< Input segment object
    );

    //! Check if segments are (almost) equal
    bool
    isApprox(
      segment const &segment_in,         //!< Input segment object
      real           tolerance = EPSILON //!< Tolerance
    ) const;

    //! Get segment centroid
    point
    centroid(void) const;

    //! Get segment i-th vertex const reference
    point const &
    vertex(
      size_t i //!< Intput segment i-th vertex index
    ) const;

    //! Get segment i-th vertex reference
    point &
    vertex(
      size_t i //!< Intput segment i-th vertex index
    );

    //! Get segment i-th vertex const reference
    point const &
    operator[](
      size_t i //!< Intput segment i-th vertex index
    ) const;

    //! Get segment i-th vertex reference
    point &
    operator[](
      size_t i //!< Intput segment i-th vertex index
    );

    //! Convert segment to vector
    vec3
    toVector(void) const;

    //! Convert segment to normalized vector
    vec3
    toUnitVector(void) const;

    //! Swap segment points
    void
    swap(void);

    //! Calculate segment length
    real
    length(void) const;

    //! Translate segment by vector
    void
    translate(
      vec3 const &vector_in //!< Input translation vector
      ) override;

    //! Transform segment with affine transformation matrix
    void
    transform(
      affine const &affine_in //!< 4x4 affine transformation matrix
      ) override;

    // Check whether the point is inside the segment
    bool
    isInside(
      point const &point_in,           //!< Query point
      real         tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check if segment is degenerated to point
    bool
    isDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const override;

    //! Return object hierarchical level
    integer
    level(void) const override
    {
      return 6;
    }

    //! Return object type as string
    std::string
    type(void) const override
    {
      return "segment";
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
      return true;
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

    //! Check whether in the segment is clampable
    bool
    isClampable(void) const override
    {
      return true;
    }

    //! Check whether in the segment is non-clampable
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

  }; // class segment

  static segment const NAN_SEGMENT       = segment(NAN_POINT, NAN_POINT); //!< Not-a-Number static const segment object
  static segment       THROWAWAY_SEGMENT = segment(NAN_SEGMENT);          //!< Throwaway static non-const segment object

} // namespace acme

#endif

///
/// eof: acme_segment.hh
///