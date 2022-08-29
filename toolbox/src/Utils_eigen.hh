/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2017                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                |
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

///
/// file: Utils_eigen.hh
///
#pragma once

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef UTILS_EIGEN_dot_HH
#define UTILS_EIGEN_dot_HH

#include "Utils.hh"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-copy-with-dtor"
#endif

#define EIGEN_DONT_PARALLELIZE
#define EIGEN_NO_AUTOMATIC_RESIZING
#include <Eigen/Core>

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif

#endif


///
/// eof: Utils_eigen.hh
///
