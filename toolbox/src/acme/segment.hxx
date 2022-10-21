/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * The ACME project                                                    *
 *                                                                     *
 * Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *
 *                                                                     *
 * The ACME project and its components are supplied under the terms of *
 * the open source BSD 2-Clause License. The contents of the ACME      *
 * project and its components may not be copied or disclosed except in *
 * accordance with the terms of the BSD 2-Clause License.              *
 *                                                                     *
 * URL: https://opensource.org/licenses/BSD-2-Clause                   *
 *                                                                     *
 *    Davide Stocco                                                    *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: davide.stocco@unitn.it                                   *
 *                                                                     *
 *    Enrico Bertolazzi                                                *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: enrico.bertolazzi@unitn.it                               *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: segment.hxx
///

#pragma once
#ifndef INCLUDE_ACME_SEGMENT_HXX
#define INCLUDE_ACME_SEGMENT_HXX

#include "aabb.hxx"
#include "point.hxx"

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
    //! Segment copy constructor
    segment(segment const &) = default;

    //! Segment move constructor
    segment(segment &&) = default;

    //! Segment assignment operator
    segment & operator=(const segment &) = default;

    //! Segment move assignment operator
    segment & operator=(segment &&) = default;

    //! Segment class destructor
    ~segment(void) override = default;

    //! Segment class constructor
    segment(void);

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
      point const & vertex0, //!< Input first segment vertex
      point const & vertex1  //!< Input second segment vertex
    );

    //! Segment class constructor
    segment(
      point const vertex[2] //!< Input segment vertices
    );

    //! Check if segments are (almost) equal
    bool
    isApprox(
      segment const & segment_in,         //!< Input segment object
      real            tolerance = EPSILON //!< Tolerance
    ) const;

    //! Get segment centroid
    point
    centroid(void)
    const;

    //! Get segment i-th vertex const reference
    point const &
    vertex(
      integer i //!< Intput segment i-th vertex index
    ) const;

    //! Get segment i-th vertex reference
    point &
    vertex(
      integer i //!< Intput segment i-th vertex index
    );

    //! Get segment i-th vertex const reference
    point const &
    operator[](
      integer i //!< Intput segment i-th vertex index
    ) const;

    //! Get segment i-th vertex reference
    point &
    operator[](
      integer i //!< Intput segment i-th vertex index
    );

    //! Convert segment to vector
    vec3
    toVector(void)
    const;

    //! Convert segment to normalized vector
    vec3
    toUnitVector(void)
    const;

    //! Swap segment points
    void
    swap(void);

    //! Calculate segment length
    real
    length(void)
    const;

    //! Translate segment by vector
    void
    translate(
      vec3 const & vector_in //!< Input translation vector
    ) override;

    //! Transform segment with affine transformation matrix
    void
    transform(
      affine const & affine_in //!< 4x4 affine transformation matrix
    ) override;

    // Check whether the point is inside the segment
    bool
    isInside(
      point const & point_in,           //!< Query point
      real          tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check if segment is degenerated to point
    bool
    isDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const override;

    //! Return object hierarchical level
    inline
    integer
    level(void)
      const override
    {
      return integer(6);
    }

    //! Return object type as string
    inline
    std::string
    type(void)
      const override
    {
      return "segment";
    }

    //! Check whether the object is no entity
    inline
    bool
    isNone(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a point
    inline
    bool
    isPoint(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a line
    inline
    bool
    isLine(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a ray
    inline
    bool
    isRay(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a plane
    inline
    bool
    isPlane(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a segment
    inline
    bool
    isSegment(void)
      const override
    {
      return true;
    }

    //! Check whether the object is a triangle
    inline
    bool
    isTriangle(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a disk
    inline
    bool
    isDisk(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a ball
    inline
    bool
    isBall(void)
      const override
    {
      return false;
    }

    //! Check whether in the segment is clampable
    inline
    bool
    isClampable(void)
      const override
    {
      return true;
    }

    //! Check whether in the segment is non-clampable
    inline
    bool
    isNonClampable(void)
      const override
    {
      return false;
    }

    //! Get minumum and maximum values along axes
    bool
    clamp(
      vec3 & min, //!< Input minimum point
      vec3 & max  //!< Input maximum point
    ) const override;

    //! Get minumum and maximum values along axes
    bool
    clamp(
      real & min_x, //!< Input x value of minimum point
      real & min_y, //!< Input y value of minimum point
      real & min_z, //!< Input z value of minimum point
      real & max_x, //!< Input x value of maximum point
      real & max_y, //!< Input y value of maximum point
      real & max_z  //!< Input z value of maximum point
    ) const override;

  }; // class segment

  static segment const & NAN_SEGMENT   = * new segment(NAN_POINT, NAN_POINT); //!< Not-a-Number static const segment object
  static segment       & DUMMY_SEGMENT = * new segment(NAN_POINT, NAN_POINT); //!< Dummy static non-const segment object

} // namespace acme

#endif

///
/// eof: segment.hxx
///
