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
/// file: acme_ball.hh
///

#pragma once

#ifndef INCLUDE_ACME_BALL
#define INCLUDE_ACME_BALL

#include "acme.hh"
#include "acme_aabb.hh"
#include "acme_point.hh"

namespace acme
{

  /*\
   |   _           _ _
   |  | |__   __ _| | |
   |  | '_ \ / _` | | |
   |  | |_) | (_| | | |
   |  |_.__/ \__,_|_|_|
   |
  \*/

  //! Ball class container
  /**
   * Ball in 3D space and defined by a radius and a plane (ball center + normal vector).
   */
  class ball : public entity
  {
  private:
    real  m_radius = QUIET_NAN; //!< Ball radius
    point m_center = NAN_POINT; //!< Ball center point

  public:
    //! Ball class deconstructor
    ~ball(void);

    //! Ball class constructor
    ball(void);

    //! Ball copy constructor
    ball(ball const &) = default;

    //! Ball move constructor
    ball(ball &&) = default;

    //! Ball class constructor
    ball(
      real radius,   //!< Input ball radius
      real center_x, //!< Input ball center x value
      real center_y, //!< Input ball center y value
      real center_z  //!< Input ball center z value
    );

    //! Ball class constructor
    ball(
      real         radius, //!< Input ball radius
      point const &center  //!< Input ball center
    );

    //! Equality operator
    ball &
    operator=(
      ball const &ball_in //!< Input ball object
    );

    //! Check if disks are (almost) equal
    bool
    isApprox(
      ball const &ball_in,            //!< Input ball object
      real        tolerance = EPSILON //!< Tolerance
    ) const;

    //! Get ball radius const reference
    real const &
    radius(void) const;

    //! Get ball radius reference
    real &
    radius(void);

    //! Get ball center point const reference
    point const &
    center(void) const;

    //! Get ball center point reference
    point &
    center(void);

    //! Calculate ball area
    real
    area(void) const;

    //! Calculate ball volume
    real
    volume(void) const;

    //! Translate by vector
    void
    translate(
      vec3 const &vector_in //!< Input translation vector
      ) override;

    //! Transform ball with affine transformation matrix
    void
    transform(
      affine const &affine_in //!< 4x4 affine transformation matrix
      ) override;

    // Check whether the point is inside the ball
    bool
    isInside(
      point const &point_in,           //!< Query point
      real         tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check if ball is degenerated
    bool
    isDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const override;

    //! Return object hierarchical level
    integer
    level(void) const override
    {
      return 9;
    }

    //! Return object type as string
    std::string
    type(void) const override
    {
      return "ball";
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
      return false;
    }

    //! Check whether the object is a ball
    bool
    isBall(void) const override
    {
      return true;
    }

    //! Check whether in the ball is clampable
    bool
    isClampable(void) const override
    {
      return true;
    }

    //! Check whether in the ball is non-clampable
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

  }; // class ball

  static ball const NAN_BALL       = ball(QUIET_NAN, NAN_POINT); //!< Not-a-Number static const ball object
  static ball       THROWAWAY_BALL = ball(NAN_BALL);             //!< Throwaway static non-const ball object

} // namespace acme

#endif

///
/// eof: acme_disk.hh
///