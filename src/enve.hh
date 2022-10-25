/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * This file is part of the ENVE project.                              *
 *                                                                     *
 * Copyright (c) 2022, Davide Stocco. All rights reserved.             *
 *                                                                     *
 * The ENVE project can not be copied and/or distributed without       *
 * the express permission of Davide Stocco.                            *
 *                                                                     *
 *    Davide Stocco                                                    *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: davide.stocco@unitn.it                                   *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: enve.hh
///

#ifndef INCLUDE_ENVE_HH
#define INCLUDE_ENVE_HH

#define ENVE_DEBUG

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

// Switch from Utils to acme AABB tree
#define ENVE_USE_UTILS_AABBTREE
#ifdef ENVE_USE_UTILS_AABBTREE
#define ENVE_AABBTREE_NODE_SIZE 1
#endif

// Define enve debug timing and messaging
//#define ENVE_DEBUG
#ifdef ENVE_DEBUG
  static int inter = 0;
  #define ENVE_DEBUG_TICTOC      Utils::TicToc tictoc
  #define ENVE_DEBUG_TIC         tictoc.tic()
  #define ENVE_DEBUG_TOC         tictoc.toc()
  #define ENVE_MESSAGE_DEBUG(...) std::cout << fmt::format(__VA_ARGS__) << std::flush
#else
  #define ENVE_DEBUG_TICTOC
  #define ENVE_DEBUG_TIC
  #define ENVE_DEBUG_TOC
  #define ENVE_MESSAGE_DEBUG(...)
#endif

#include <fstream>

#include "acme.hh"
#include "Utils_AABB_tree.hh"

using acme::real;
using acme::integer;
using acme::out_stream;

using acme::QUIET_NAN;
using acme::EPSILON_LOW;
using acme::EPSILON_MEDIUM;
using acme::EPSILON_HIGH;

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

using acme::IsApprox;

using AABB_TREE = Utils::AABBtree<real>;
using AABB_SET  = Utils::AABBtree<real>::AABB_SET;
using AABB_MAP  = Utils::AABBtree<real>::AABB_MAP;

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
