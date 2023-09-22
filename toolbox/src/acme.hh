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
/// file: acme.hh
///

#pragma once
#ifndef INCLUDE_ACME_HH
#define INCLUDE_ACME_HH

// Print acme errors
#ifndef ACME_ERROR
#define ACME_ERROR(MSG)                  \
  {                                      \
    std::ostringstream ost;              \
    ost << MSG;                          \
    throw std::runtime_error(ost.str()); \
  }
#endif

// Check for acme errors
#ifndef ACME_ASSERT
#define ACME_ASSERT(COND, MSG) \
  if (!(COND))                 \
  ACME_ERROR(MSG)
#endif

// Standard libraries
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <vector>
#include <map>

// Eigen libraries
#include <Eigen/Dense>

//!  Namespace containing all acme typedefs, classes and routines
namespace acme
{

  /*\
   |   _____                     _       __
   |  |_   _|   _ _ __   ___  __| | ___ / _|___
   |    | || | | | '_ \ / _ \/ _` |/ _ \ |_/ __|
   |    | || |_| | |_) |  __/ (_| |  __/  _\__ \
   |    |_| \__, | .__/ \___|\__,_|\___|_| |___/
   |        |___/|_|
  \*/

  typedef double       real;       //!< Real number type
  typedef int          integer;    //!< Integer number type
  typedef std::ostream out_stream; //!< Output stream type

  typedef Eigen::Matrix<real, 2, 1>                           vec2; //!< 2x1 vector type (column vector)
  typedef Eigen::Matrix<real, 2, 2>                           mat2; //!< 2x2 matrix type
  typedef Eigen::Matrix<real, 3, 1>                           vec3; //!< 3x1 vector type (column vector)
  typedef Eigen::Matrix<real, 3, 3>                           mat3; //!< 3x3 matrix type
  typedef Eigen::Matrix<real, 4, 1>                           vec4; //!< 4x1 vector type (column vector)
  typedef Eigen::Matrix<real, 4, 4>                           mat4; //!< 4x4 matrix type
  typedef Eigen::Matrix<real, Eigen::Dynamic, 1>              vecN; //!< Nx1 vector of real number type (column vector)
  typedef Eigen::Matrix<real, Eigen::Dynamic, Eigen::Dynamic> matN; //!< NxN matrix of real number type

  typedef Eigen::DiagonalMatrix<real, 3>           scale;     //!< 3D scaling transformation type
  typedef Eigen::Translation<real, 3>              translate; //!< 3D translation transformation type
  typedef Eigen::AngleAxis<real>                   angleaxis; //!< 3D rotation transformation type
  typedef Eigen::Transform<real, 3, Eigen::Affine> affine;    //!< 3D affine transformation type

  /*\
   |    ____                _              _
   |   / ___|___  _ __  ___| |_ __ _ _ __ | |_ ___
   |  | |   / _ \| '_ \/ __| __/ _` | '_ \| __/ __|
   |  | |__| (_) | | | \__ \ || (_| | | | | |_\__ \
   |   \____\___/|_| |_|___/\__\__,_|_| |_|\__|___/
   |
  \*/

  static real const EPSILON_MACHINE = std::numeric_limits<real>::epsilon();      //!< Machine epsilon epsilon static constant value
  static real const EPSILON_HIGH    = real(1.0e-16);                             //!< High precision epsilon static constant value
  static real const EPSILON_MEDIUM  = real(1.0e-10);                             //!< Medium precision epsilon static constant value
  static real const EPSILON_LOW     = real(1.0e-07);                             //!< Low precision epsilon static constant value
  static real const EPSILON         = EPSILON_MEDIUM;                            //!< Standard precision epsilon static constant value
  static real const INFTY           = std::numeric_limits<real>::infinity();     //!< Infinity static constant value
  static real const QUIET_NAN       = std::numeric_limits<real>::quiet_NaN();    //!< Not-a-Number static constant value
  static real const PI              = real(3.141592653589793238462643383279500); //!< Pi static constant value
  static real const PIDIV180        = real(0.017453292519943295769236907684886); //!< Pi/180 static constant value

  static vec2 const UNITX_VEC2    = vec2::UnitX();             //!< X axis unit vec2 static constant object
  static vec2 const UNITY_VEC2    = vec2::UnitY();             //!< Y axis unit vec2 static constant object
  static vec2 const NAN_VEC2      = vec2::Constant(QUIET_NAN); //!< Not-a-Number vec2 static constant object
  static mat2 const NAN_MAT2      = mat2::Constant(QUIET_NAN); //!< Not-a-Number mat2 static constant object
  static vec2 const ZEROS_VEC2    = vec2::Constant(real(0.0));       //!< Zeros vec2 static constant object
  static mat2 const ZEROS_MAT2    = mat2::Constant(real(0.0));       //!< Zeros mat2 static constant object
  static vec2 const ONES_VEC2     = vec2::Constant(real(1.0));       //!< Ones vec2 static constant object
  static mat2 const ONES_MAT2     = mat2::Constant(real(1.0));       //!< Ones mat2 static constant object
  static mat2 const IDENTITY_MAT2 = mat2::Identity();          //!< Identity mat2 static constant object

  static vec3 const UNITX_VEC3    = vec3::UnitX();             //!< X axis unit vec3 constant object
  static vec3 const UNITY_VEC3    = vec3::UnitY();             //!< Y axis unit vec3 constant object
  static vec3 const UNITZ_VEC3    = vec3::UnitZ();             //!< Z axis unit vec3 constant object
  static vec3 const NAN_VEC3      = vec3::Constant(QUIET_NAN); //!< Not-a-Number vec3 constant object
  static mat3 const NAN_MAT3      = mat3::Constant(QUIET_NAN); //!< Not-a-Number mat3 constant object
  static vec3 const ZEROS_VEC3    = vec3::Constant(real(0.0)); //!< Zeros vec3 constant object
  static mat3 const ZEROS_MAT3    = mat3::Constant(real(0.0)); //!< Zeros mat3 constant object
  static vec3 const ONES_VEC3     = vec3::Constant(real(1.0)); //!< Ones vec3 constant object
  static mat3 const ONES_MAT3     = mat3::Constant(real(1.0)); //!< Ones mat3 constant object
  static mat3 const IDENTITY_MAT3 = mat3::Identity();          //!< Identity mat3 constant object

  static vec4 const UNITX_VEC4    = vec4::UnitX();             //!< X axis unit vec4 constant object
  static vec4 const UNITY_VEC4    = vec4::UnitY();             //!< Y axis unit vec4 constant object
  static vec4 const UNITZ_VEC4    = vec4::UnitZ();             //!< Z axis unit vec4 constant object
  static vec4 const UNITW_VEC4    = vec4::UnitW();             //!< W axis unit vec4 constant object
  static vec4 const NAN_VEC4      = vec4::Constant(QUIET_NAN); //!< Not-a-Number vec4 constant object
  static mat4 const NAN_MAT4      = mat4::Constant(QUIET_NAN); //!< Not-a-Number mat4 constant object
  static vec4 const ZEROS_VEC4    = vec4::Constant(real(0.0)); //!< Zeros vec4 constant object
  static mat4 const ZEROS_MAT4    = mat4::Constant(real(0.0)); //!< Zeros mat4 constant object
  static vec4 const ONES_VEC4     = vec4::Constant(real(1.0)); //!< Ones vec4 constant object
  static mat4 const ONES_MAT4     = mat4::Constant(real(1.0)); //!< Ones mat4 constant object
  static mat4 const IDENTITY_MAT4 = mat4::Identity();          //!< Identity mat4 constant object

  static vec2 DUMMY_VEC2(NAN_VEC2); //!< Dummy vec2 static non-const object
  static vec3 DUMMY_VEC3(NAN_VEC3); //!< Dummy vec3 static non-const object
  static vec4 DUMMY_VEC4(NAN_VEC4); //!< Dummy vec4 static non-const object
  static mat2 DUMMY_MAT2(NAN_MAT2); //!< Dummy mat2 static non-const object
  static mat3 DUMMY_MAT3(NAN_MAT3); //!< Dummy mat3 static non-const object
  static mat4 DUMMY_MAT4(NAN_MAT4); //!< Dummy mat4 static non-const object

} // namespace acme

#include "acme/aabb.hxx"
#include "acme/AABBtree.hxx"
#include "acme/ball.hxx"
#include "acme/collection.hxx"
#include "acme/collinear.hxx"
#include "acme/coplanar.hxx"
#include "acme/disk.hxx"
#include "acme/entity.hxx"
#include "acme/intersection.hxx"
#include "acme/line.hxx"
#include "acme/math.hxx"
#include "acme/none.hxx"
#include "acme/orthogonal.hxx"
#include "acme/parallel.hxx"
#include "acme/plane.hxx"
#include "acme/point.hxx"
#include "acme/ray.hxx"
#include "acme/segment.hxx"
#include "acme/triangle.hxx"
#include "acme/utilities.hxx"

#endif

///
/// eof: acme.hh
///
