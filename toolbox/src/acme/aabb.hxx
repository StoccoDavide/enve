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
/// file: aabb.hxx
///

#pragma once

#ifndef INCLUDE_ACME_AABB_HXX
#define INCLUDE_ACME_AABB_HXX

#include "point.hxx"

namespace acme
{

  /*\
   |               _     _
   |    __ _  __ _| |__ | |_
   |   / _` |/ _` | '_ \| '_ \
   |  | (_| | (_| | |_) | |_) |
   |   \__,_|\__,_|_.__/|_.__/
   |
  \*/

  //! Axis-aligebd bounding box class container
  /**
   * Axis-aligebd bounding box in 3D space and defined by a "maximum" and a "minimum" point.
   */
  class aabb
  {
  public:
    typedef std::shared_ptr<aabb const> ptr;        //!< Shared pointer to const aabb object used in AABBtree routines
    typedef std::pair<ptr, ptr>         pairptr;    //!< Pair of pointers to const aabb objects used in AABBtree routines
    typedef std::vector<ptr>            vecptr;     //!< Vector of pointers to const aabb objects used in AABBtree routines
    typedef std::vector<pairptr>        vecpairptr; //!< Vector of pairs of pointers to const aabb objects used in AABBtree routines

  private:
    point   m_min = NAN_POINT;  //!< Box maximum point
    point   m_max = NAN_POINT;  //!< Box minimum point
    integer m_id  = integer(0); //!< Box id (may be used in external algorithms)
    integer m_pos = integer(0); //!< Box rank (may be used in external algorithms)

  public:
    //! Box copy constructor
    aabb(const aabb &) = default;

    //! Box move constructor
    aabb(aabb &&) = default;

    //! Box assignment operator
    aabb & operator=(const aabb &) = default;

    //! Box move assignment operator
    aabb & operator=(aabb &&) = default;

    //! Box class constructor
    aabb(void);

    //! Box class constructor
    aabb(
      real    min_x,               //!< Input x value of aabb minimum point
      real    min_y,               //!< Input y value of aabb minimum point
      real    min_z,               //!< Input z value of aabb minimum point
      real    max_x,               //!< Input x value of aabb maximum point
      real    max_y,               //!< Input y value of aabb maximum point
      real    max_z,               //!< Input z value of aabb maximum point
      integer id     = integer(0), //!< Input id value
      integer ipos   = integer(0)  //!< Input rank value
    );

    //! Box class constructor
    aabb(
      point   const & min,               //!< Input aabb minimum point
      point   const & max,               //!< Input aabb maximum point
      integer         id   = integer(0), //!< Input aabb id value
      integer         ipos = integer(0)  //!< Input aabb rank value
    );

    //! Box class constructor
    aabb(
      std::vector<aabb::ptr> const & boxes,             //!< Input reference to vector of boxes
      integer                        id   = integer(0), //!< Input aabb id value
      integer                        ipos = integer(0)  //!< Input aabb rank value
    );

    //! Clear the aabb domain (set to Not-a-Number)
    void
    clear(void);

    //! Check if aabb objects are (almost) equal
    bool
    isApprox(
      aabb const & aabb_in,            //!< Input
      real         tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check aabb max and min points
    bool
    checkMaxMin(void)
    const;

    //! Update and check aabb max and min points
    bool
    updateMaxMin(void);

    //! Get minimum point const reference
    point const &
    min(void)
    const;

    //! Get minimum point reference
    point &
    min(void);

    //! Get aabb minimum i-th axis value const reference
    real const &
    min(
      integer i //!< Input i-th value
    ) const;

    //! Get aabb minimum i-th axis value reference
    real &
    min(
      integer i //!< Input i-th value
    );

    //! Set aabb minimum point
    void
    min(
      real x, //!< Input x value of aabb minimum point
      real y, //!< Input y value of aabb minimum point
      real z  //!< Input z value of aabb minimum point
    );

    //! Get aabb maximum point const reference
    point const &
    max(void)
    const;

    //! Get aabb maximum point reference
    point &
    max(void);

    //! Get aabb maximum i-th point axis value const reference
    real const &
    max(
      integer i //!< Input i-th value
    ) const;

    //! Get aabb maximum i-th point axis value
    real &
    max(
      integer i //!< Input i-th value
    );

    //! Set aabb maximum point
    void
    max(
      real x, //!< Input x value of aabb maximum point
      real y, //!< Input y value of aabb maximum point
      real z  //!< Input z value of aabb maximum point
    );

    //! Detect if boxes collide
    bool
    intersects(
      aabb const & aabb_in //!< Input
    ) const;

    //! Build aabb with a vector of pointers to boxes
    void
    merged(
      aabb::vecptr const & boxes //!< Input poiter to vector of boxes
    );

    //! Distance of a point to the aabb
    real
    centerDistance(
      point const & point_in //!< Query point
    ) const;

    //! Maximum distance of a point to the aabb
    real
    exteriorDistance(
      point const & point_in //!< Query point
    ) const;

    //! Resize the aabb as the minimum bounding aabb containing three input points
    void
    clamp(
      point const & point0_in, //!< Input point 0
      point const & point1_in, //!< Input point 1
      point const & point2_in  //!< Input point 2
    );

    //! Resize the aabb as the minimum bounding aabb containing three input points
    void
    clamp(
      point const point_in[3] //!< Input points
    );

    //!< Return aabb id const reference
    integer const &
    id(void)
    const;

    //!< Return aabb id reference
    integer &
    id(void);

    //!< Return aabb position const reference
    integer const &
    pos(void)
    const;

    //!< Return aabb position reference
    integer &
    pos(void);

    //! Translate aabb by vector
    void
    translate(
      point const & vector_in //!< Input translation vector
    );

    // Check whether the point is inside the aabb
    bool
    isInside(
      point const & point_in,           //!< Query point
      real          tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check if aabb is degenerated
    bool
    isDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const;

  }; // class aabb

  static aabb const & NAN_AABB   = * new aabb(NAN_POINT, NAN_POINT); //!< Not-a-Number static const aabb object
  static aabb       & DUMMY_AABB = * new aabb(NAN_AABB);             //!< Dummy static non-const aabb object

} // namespace acme

#endif

///
/// eof: aabb.hxx
///
