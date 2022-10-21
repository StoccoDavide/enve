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
/// file: line.hxx
///

#pragma once
#ifndef INCLUDE_ACME_LINE_HXX
#define INCLUDE_ACME_LINE_HXX

#include "point.hxx"

namespace acme
{

  /*\
   |   _ _
   |  | (_)_ __   ___
   |  | | | '_ \ / _ \
   |  | | | | | |  __/
   |  |_|_|_| |_|\___|
   |
  \*/

  //! Line class container
  /**
   * Infinite line in 3D space and defined by any point lying on the line and a direction
   * vector.
   */
  class line : public entity
  {
  private:
    point m_origin    = NAN_POINT; //!< Origin point
    vec3  m_direction = NAN_VEC3;  //!< Direction vector

  public:
    //! Line copy constructor
    line(line const &) = default;

    //! Line move constructor
    line(line &&) = default;

    //! Line assignment operator
    line & operator=(const line &) = default;

    //! Line move assignment operator
    line & operator=(line &&) = default;

    //! Line class destructor
    ~line(void) override = default;

    //! Line class constructor
    line(void);

    //! Line class constructor
    line(
      real ox, //!< Input x value of line origin point
      real oy, //!< Input y value of line origin point
      real oz, //!< Input z value of line origin point
      real dx, //!< Input x value of line direction vector
      real dy, //!< Input y value of line direction vector
      real dz  //!< Input z value of line direction vector
    );

    //! Line class constructor
    line(
      point const & origin,   //!< Input line origin point
      vec3  const & direction //!< Input line direction vector
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      line const & line_in,            //!< Input line object
      real         tolerance = EPSILON //!< Tolerance
    ) const;

    //! Return line origin point const reference
    point const &
    origin(void)
    const;

    //! Return line origin point reference
    point &
    origin(void);

    //! Return line direction vector const reference
    vec3 const &
    direction(void)
    const;

    //! Return line direction vector reference
    vec3 &
    direction(void);

    //! Normalize line direction vector
    void
    normalize(void);

    //! Convert line to vector
    vec3
    toVector(void)
    const;

    //! Convert line to normalized vector
    vec3
    toUnitVector(void)
    const;

    //! Reverse line direction
    void
    reverse(void);

    //! Translate line by vector
    void
    translate(
      vec3 const & vector_in //!< Input translation vector
    ) override;

    //! Transform line with affine transformation matrix
    void
    transform(
      affine const & affine_in //!< 4x4 affine transformation matrix
    ) override;

    // Check whether the point is inside the line
    bool
    isInside(
      point const & point_in,           //!< Query point
      real          tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check if line is degenerated (direction vector has zero norm)
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
      return integer(3);
    }

    //! Return object type as string
    inline
    std::string
    type(void)
      const override
    {
      return "line";
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
      return true;
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
      return false;
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

    //! Check whether in the line is clampable
    inline
    bool
    isClampable(void)
      const override
    {
      return false;
    }

    //! Check whether in the line is non-clampable
    inline
    bool
    isNonClampable(void)
      const override
    {
      return true;
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

  }; // class line

  static line const & NAN_LINE   = * new line(NAN_POINT, NAN_VEC3); //!< Not-a-Number static const line object
  static line       & DUMMY_LINE = * new line(NAN_POINT, NAN_VEC3); //!< Dummy static non-const line object

} // namespace acme

#endif

///
/// eof: line.hxx
///
