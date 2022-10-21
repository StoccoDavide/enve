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
/// file: none.hxx
///

#pragma once
#ifndef INCLUDE_ACME_NONE_HXX
#define INCLUDE_ACME_NONE_HXX

#include "point.hxx"

namespace acme
{

  /*\
   |
   |   _ __   ___  _ __   ___
   |  | '_ \ / _ \| '_ \ / _ \
   |  | | | | (_) | | | |  __/
   |  |_| |_|\___/|_| |_|\___|
   |
  \*/

  //! None class container
  /**
   * This cass represent a empty geometrical entity.
   */
  class none : public entity
  {
  public:
    //! None copy constructor
    none(none const &) = default;

    //! None move constructor
    none(none &&) = default;

    //! None assignment operator
    none & operator=(const none &) = default;

    //! None move assignment operator
    none & operator=(none &&) = default;

    //! None class destructor
    ~none(void) override = default;

    //! None class constructor
    none(void);

    //! Translate entity by vector
    void
    translate(
      vec3 const & vector_in //!< Input translation vector
    ) override;

    //! Transform entity with affine transformation matrix
    void
    transform(
      affine const & affine_in //!< 4x4 affine transformation matrix
    ) override;

    //! Check if entity is degenerated
    bool
    isDegenerated(
      real /*tolerance = EPSILON*/ //!< Tolerance
    ) const override
    {
      return true;
    };

    //! Return object hierarchical level
    inline
    integer
    level(void)
      const override
    {
      return integer(0);
    }

    //! Return object type as string
    inline
    std::string
    type(void)
      const override
    {
      return "none";
    }

    //! Check whether the object is no entity
    inline
    bool
    isNone(void)
      const override
    {
      return true;
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

    //! Check whether in the disk is clampable
    inline
    bool
    isClampable(void)
      const override
    {
      return false;
    }

    //! Check whether in the disk is non-clampable
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

  }; // class none

  static none & DUMMY_NONE = * new none(); //!< Dummy static non-const none object

} // namespace acme

#endif

///
/// eof: none.hxx
///
