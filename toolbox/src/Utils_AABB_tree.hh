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
/// file: Utils_AABBtree.hh
///
#pragma once

#ifndef UTILS_AABB_TREE_dot_HH
#define UTILS_AABB_TREE_dot_HH

#include "Utils.hh"

#include <string>
#include <vector>
#include <set>
#include <map>

namespace Utils {

  using std::string;
  using std::vector;
  using std::set;
  using std::map;

  /*\
   |      _        _    ____  ____  _
   |     / \      / \  | __ )| __ )| |_ _ __ ___  ___
   |    / _ \    / _ \ |  _ \|  _ \| __| '__/ _ \/ _ \
   |   / ___ \  / ___ \| |_) | |_) | |_| | |  __/  __/
   |  /_/   \_\/_/   \_\____/|____/ \__|_|  \___|\___|
  \*/

  template <typename Real>
  class AABBtree {
  public:

    typedef int integer;
    typedef set<integer>     SET;
    typedef map<integer,SET> MAP;

  private:

    Malloc<Real>    m_rmem;
    Malloc<integer> m_imem;

    // AABBtree structure
    integer m_dim            = 0;
    integer m_num_bb         = 0;
    integer m_num_tree_nodes = 0;

    integer * m_father    = nullptr;
    integer * m_child     = nullptr;
    integer * m_ptr_nodes = nullptr;
    integer * m_num_nodes = nullptr;
    integer * m_id_nodes  = nullptr;
    integer * m_stack     = nullptr;
    Real    * m_bb_min    = nullptr;
    Real    * m_bb_max    = nullptr;

    // parameters
    integer m_max_object_per_node = 16;
    Real    m_long_bbox_tolerance = 0.8;
    Real    m_volume_tolerance    = 0.1;

  public:

    AABBtree() : m_rmem("AABBtree"), m_imem("AABBtree") {}

    void set_max_object_per_node( integer n );
    void set_long_bbox_tolerance( Real tol );
    void set_volume_tolerance( Real tol );

    void build( Real const * bb_min, Real const * bb_max, integer nbox, integer dim );

    void intersect( Real const * pnt, SET & bb_index ) const;
    void intersect( Real const * bb_min, Real const * bb_max, SET & bb_index ) const;
    void intersect( AABBtree<Real> const & aabb, MAP & bb_index ) const;

    void get_nodes( integer i_pos, SET & bb_index ) const;

    integer dim()            const { return m_dim; }
    integer num_bb()         const { return m_num_bb; }
    integer num_tree_nodes() const { return m_num_tree_nodes; }

    string info() const;

  };

  /*
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  */

  #ifndef UTILS_OS_WINDOWS
  extern template class AABBtree<float>;
  extern template class AABBtree<double>;
  #endif

}


#endif

///
/// eof: Utils_AABBtree.hh
///
