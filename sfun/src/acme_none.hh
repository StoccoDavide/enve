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
/// file: acme_none.hh
///

#pragma once

#ifndef INCLUDE_ACME_NONE
#define INCLUDE_ACME_NONE

#include "acme.hh"
#include "acme_point.hh"

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
    //! None class deconstructor
    ~none(void);

    //! None class constructor
    none(void);

    //! None copy constructor
    none(none const &) = default;

    //! None move constructor
    // none(none &&) = default;

    //! Translate entity by vector
    void
    translate(
      vec3 const &vector_in //!< Input translation vector
      ) override{};

    //! Transform entity with affine transformation matrix
    void
    transform(
      affine const &affine_in //!< 4x4 affine transformation matrix
      ) override{};

    //! Check if entity is degenerated
    bool
    isDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const override
    {
      return true;
    };

    //! Return object hierarchical level
    integer
    level(void) const override
    {
      return 1;
    }

    //! Return object type as string
    std::string
    type(void) const override
    {
      return "none";
    }

    //! Check whether the object is no entity
    bool
    isNone(void) const override
    {
      return true;
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
      return false;
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
      return false;
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

  }; // class none

  static none THROWAWAY_NONE = none(); //!< Throwaway static non-const none object

} // namespace acme

#endif

///
/// eof: acme_none.hh
///