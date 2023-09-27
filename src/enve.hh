/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * The ENVE project                                                    *
 *                                                                     *
 * Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *
 *                                                                     *
 * The ENVE project and its components are supplied under the terms of *
 * the open source BSD 3-Clause License. The contents of the ENVE      *
 * project and its components may not be copied or disclosed except in *
 * accordance with the terms of the BSD 3-Clause License.              *
 *                                                                     *
 * URL: https://opensource.org/licenses/BSD-3-Clause                   *
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
/// file: enve.hh
///

#ifndef INCLUDE_ENVE_HH
#define INCLUDE_ENVE_HH

// Print enve errors
#ifndef ENVE_ERROR
#define ENVE_ERROR(MSG)                 \
  {                                     \
    std::ostringstream os;              \
    os << MSG;                          \
    throw std::runtime_error(os.str()); \
  }
#endif

// Check for enve errors
#ifndef ENVE_ASSERT
#define ENVE_ASSERT(COND, MSG) \
  if (!(COND))                 \
  ENVE_ERROR(MSG)
#endif

#include <fstream>

#include "acme.hh"

using acme::real;
using acme::integer;
using acme::out_stream;

using acme::QUIET_NAN;
using acme::EPSILON_SQRT;
using acme::EPSILON_CBRT;

using acme::vec3;
using acme::mat3;
using acme::mat4;

using acme::point;
using acme::line;
using acme::triangle;
using acme::disk;
using acme::plane;
using acme::affine;
using acme::aabb;
using acme::AABBtree;

using acme::NAN_VEC3;
using acme::NAN_POINT;
using acme::NAN_TRIANGLE;
using acme::NAN_DISK;
using acme::NAN_AABB;

using acme::IDENTITY_MAT4;

using acme::IsApprox;

// Static constants for convenience
static real   const EPSILON_ENVE    = EPSILON_SQRT;          //!< Standard precision epsilon static constant value for enve
static affine const IDENTITY_AFFINE = affine(IDENTITY_MAT4); //!< Identity affine constant object


#include "enve/flat.hxx"
#include "enve/mesh.hxx"
#include "enve/output.hxx"
#include "enve/rib.hxx"
#include "enve/shape.hxx"
#include "enve/shell.hxx"
#include "enve/triangleground.hxx"

#endif

///
/// eof: enve.hh
///
