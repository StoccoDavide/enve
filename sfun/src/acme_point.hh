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
/// file: acme_point.hh
///

#pragma once

#ifndef INCLUDE_ACME_POINT
#define INCLUDE_ACME_POINT

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>

#include "acme.hh"
#include "acme_entity.hh"
#include "acme_math.hh"

namespace acme
{

  /*\
   |               _       _
   |   _ __   ___ (_)_ __ | |_
   |  | '_ \ / _ \| | '_ \| __|
   |  | |_) | (_) | | | | | |_
   |  | .__/ \___/|_|_| |_|\__|
   |  |_|
  \*/

  //! Point class container
  /**
   * Specialization of Eigen::Matrix class
   */
  class point : public vec3, public entity
  {
  public:
    using vec3::Matrix;

    //! Point class destructor
    ~point(void);

    //! Point class constructor
    point(void);

    //! This constructor allows you to construct matrix from Eigen expressions
    template <typename derived>
    point(
      Eigen::MatrixBase<derived> const &other //!< Eigen matrix object
      ) : vec3(other)
    {
    }

    //! This method allows you to assign Eigen expressions to matrix
    template <typename derived>
    point &
    operator=(
      Eigen::MatrixBase<derived> const &other //!< Eigen matrix object
    )
    {
      this->vec3::operator=(other);
      return *this;
    }

    //! Translate point by vector
    void
    translate(
      vec3 const &vector_in //!< Input translation vector
      ) override;

    //! Transform point with affine transformation matrix
    void
    transform(
      affine const &affine_in //!< 4x4 affine transformation matrix
      ) override;

    //! Check if entity is degenerated
    bool
    isDegenerated(
      acme::real tolerance = EPSILON //!< Tolerance
    ) const override;

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
      return "point";
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
      return true;
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

    //! Check whether in the point is clampable
    bool
    isClampable(void) const override
    {
      return true;
    }

    //! Check whether in the point is non-clampable
    bool
    isNonClampable(void) const override
    {
      return false;
    }

    //! Get minumum and maximum values along axes
    bool
    clamp(
      acme::vec3 &min, //!< Input minimum point
      acme::vec3 &max  //!< Input maximum point
    ) const override;

    //! Get minumum and maximum values along axes
    bool
    clamp(
      acme::real &min_x, //!< Input x value of minimum point
      acme::real &min_y, //!< Input y value of minimum point
      acme::real &min_z, //!< Input z value of minimum point
      acme::real &max_x, //!< Input x value of maximum point
      acme::real &max_y, //!< Input y value of maximum point
      acme::real &max_z  //!< Input z value of maximum point
    ) const override;

  }; // class point

  static point const NAN_POINT       = point::Constant(QUIET_NAN); //!< Not-a-Number static const point object
  static point       THROWAWAY_POINT = point(NAN_POINT);           //!< Throwaway static non-const point object

} // namespace acme

#endif

///
/// eof: acme_point.hh
///