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
/// file: Utils_AABB_tree.cc
///

#include "Utils_AABB_tree.hh"
#include <algorithm>
#include <utility>

namespace Utils {

  using std::max;
  using std::min;
  using std::swap;
  using std::copy_n;

  template <typename Real>
  string
  AABBtree<Real>::info() const {
    integer nleaf = 0;
    integer nlong = 0;
    for ( integer i = 0; i < m_num_tree_nodes; ++i ) {
      if      ( m_child[i] < 0     ) ++nleaf;
      else if ( m_num_nodes[i] > 0 ) ++nlong;
    }
    string res = "-------- AABB tree info --------\n";
    res += fmt::format( "  Number of nodes     {}\n", m_num_tree_nodes );
    res += fmt::format( "  Number of leaf      {}\n", nleaf );
    res += fmt::format( "  Number of long node {}\n", nlong );
    res += fmt::format( "  Number of objects   {}\n", m_num_bb );
    res += fmt::format( "  max_object_per_node {}\n", m_max_object_per_node );
    res += fmt::format( "  long_bbox_tolerance {}\n", m_long_bbox_tolerance );
    res += fmt::format( "  volume_tolerance    {}\n", m_volume_tolerance );
    res += "--------------------------------\n";
    return res;
  }

  template <typename Real>
  void
  AABBtree<Real>::set_max_object_per_node( integer n ) {
    UTILS_ASSERT(
      n > 0 && n <= 4096,
      "AABBtree::set_max_object_per_node( nobj = {} )\n"
      "nobj must be > 0 and <= 4096\n",
      n
    );
    m_max_object_per_node = n;
  }

  template <typename Real>
  void
  AABBtree<Real>::set_long_bbox_tolerance( Real tol ) {
    UTILS_ASSERT(
      tol > 0 && tol < 1,
      "AABBtree::set_long_bbox_tolerance( tol = {} )\n"
      "tol must be > 0 and < 1\n",
      tol
    );
    m_long_bbox_tolerance = tol;
  }

  template <typename Real>
  void
  AABBtree<Real>::set_volume_tolerance( Real tol ) {
    UTILS_ASSERT(
      tol > 0 && tol < 1,
      "AABBtree::set_volume_tolerance( tol = {} )\n"
      "tol must be > 0 and < 1\n",
      tol
    );
    m_volume_tolerance = tol;
  }

  template <typename Real>
  void
  AABBtree<Real>::build(
    Real const * bb_obj_min,
    Real const * bb_obj_max,
    integer      nbox,
    integer      dim
  ) {
    m_dim    = dim;
    m_num_bb = nbox;

    integer nmax = 2*m_num_bb; // estimate max memory usage

    m_rmem.allocate( size_t(2*nmax*dim) );
    m_imem.allocate( size_t(6*nmax+m_num_bb) );

    m_bb_min    = m_rmem( size_t(nmax*dim) );
    m_bb_max    = m_rmem( size_t(nmax*dim) );

    m_father    = m_imem( size_t(nmax) );
    m_child     = m_imem( size_t(nmax) );
    m_ptr_nodes = m_imem( size_t(nmax) );
    m_num_nodes = m_imem( size_t(nmax) );
    m_id_nodes  = m_imem( size_t(m_num_bb) );
    m_stack     = m_imem( size_t(2*nmax) );

    // initialize id nodes, will be reordered during the tree build
    for ( integer i = 0; i < m_num_bb; ++i ) m_id_nodes[i] = i;

    // setup root node
    m_father[0]    = -1;
    m_child[0]     = -1;
    m_ptr_nodes[0] = 0;
    m_num_nodes[0] = m_num_bb;

    // root contains all rectangles, build its bbox
    Real       * bb0min = m_bb_min;
    Real       * bb0max = m_bb_max;
    Real const * bbmin  = bb_obj_min;
    Real const * bbmax  = bb_obj_max;
    std::copy_n( bbmin, m_dim, bb0min );
    std::copy_n( bbmax, m_dim, bb0max );
    for ( integer i = 1; i < m_num_bb; ++i ) {
      bbmin += m_dim;
      bbmax += m_dim;
      for ( integer j = 0; j < m_dim; ++j ) {
        if ( bb0min[j] > bbmin[j] ) bb0min[j] = bbmin[j];
        if ( bb0max[j] < bbmax[j] ) bb0max[j] = bbmax[j];
      }
    }

    // main loop: divide nodes until all constraints satisfied
    m_stack[0] = 0;
    integer n_stack = 1;
    m_num_tree_nodes = 1;

    while ( n_stack > 0 ) {

      // pop node from stack
      integer id_father = m_stack[--n_stack];

      // set no childer for the moment
      m_child[id_father] = -1;

      // get rectangles id in parent
      integer num = m_num_nodes[id_father];

      // if few bbox stop splitting
      if ( num < m_max_object_per_node ) continue;

      integer  iptr = m_ptr_nodes[id_father];
      integer * ptr = m_id_nodes + iptr;

      // split plane on longest axis, use euristic
      Real const * father_min = m_bb_min + id_father * m_dim;
      Real const * father_max = m_bb_max + id_father * m_dim;

      integer idim = 0;
      Real    mx = father_max[0] - father_min[0];
      for ( integer i = 1; i < m_dim; ++i ) {
        Real mx1 = father_max[i] - father_min[i];
        if ( mx < mx1 ) { mx = mx1; idim = i; }
      }
      Real tol_len = m_long_bbox_tolerance * mx;
      Real sp      = 0;

      // separate short/long and accumulate short baricenter
      integer n_long  = 0;
      integer n_short = 0;
      while ( n_long + n_short < num ) {
        integer          id = ptr[n_long];
        Real const * id_min = bb_obj_min + id * m_dim;
        Real const * id_max = bb_obj_max + id * m_dim;
        Real         id_len = id_max[idim] - id_min[idim];
        if ( id_len > tol_len ) {
          // found long BBOX, increment n_long and update position
          ++n_long;
        } else {
          // found short BBOX, increment n_short and exchange with bottom
          ++n_short;
          swap( ptr[n_long], ptr[num-n_short] );
          sp += id_max[idim] + id_min[idim];
        }
      }

      // if split rectangles do not improve search, stop split at this level
      if ( n_short < 2 ) continue;

      // select the split position: take the mean of the set of
      // (non-"long") rectangle centers along axis idim
      sp /= 2*n_short;

      // partition based on centers
      integer n_left  = 0;
      integer n_right = 0;

      while ( n_long + n_left + n_right < num ) {
        integer          id = ptr[n_long+n_left];
        Real const * id_min = bb_obj_min + id * m_dim;
        Real const * id_max = bb_obj_max + id * m_dim;
        Real         id_mid = (id_max[idim] + id_min[idim])/2;
        if ( id_mid < sp ) {
          ++n_left; // in right position do nothing
        } else {
          ++n_right;
          swap( ptr[n_long+n_left], ptr[num-n_right] );
        }
      }

      // if cannot improve bbox, stop split at this level!
      if ( n_left == 0 || n_right == 0 ) continue;

      // child indexing
      integer id_left  = m_num_tree_nodes + 0;
      integer id_right = m_num_tree_nodes + 1;

      // compute bbox of left and right child
      Real * left_min = m_bb_min + id_left  * m_dim;
      Real * left_max = m_bb_max + id_left  * m_dim;
      for ( integer i = 0; i < n_left; ++i ) {
        integer          id = ptr[n_long+i];
        Real const * id_min = bb_obj_min + id * m_dim;
        Real const * id_max = bb_obj_max + id * m_dim;
        if ( i == 0 ) {
          copy_n( id_min, m_dim, left_min );
          copy_n( id_max, m_dim, left_max );
        } else {
          for ( integer j = 0; j < m_dim; ++j ) {
            if ( left_min[j] > id_min[j] ) left_min[j] = id_min[j];
            if ( left_max[j] < id_max[j] ) left_max[j] = id_max[j];
          }
        }
      }

      Real * right_min = m_bb_min + id_right * m_dim;
      Real * right_max = m_bb_max + id_right * m_dim;
      for ( integer i = 0; i < n_right; ++i ) {
        integer          id = ptr[n_long+n_left+i];
        Real const * id_min = bb_obj_min + id * m_dim;
        Real const * id_max = bb_obj_max + id * m_dim;
        if ( i == 0 ) {
          copy_n( id_min, m_dim, right_min );
          copy_n( id_max, m_dim, right_max );
        } else {
          for ( integer j = 0; j < m_dim; ++j ) {
            if ( right_min[j] > id_min[j] ) right_min[j] = id_min[j];
            if ( right_max[j] < id_max[j] ) right_max[j] = id_max[j];
          }
        }
      }

      // check again if split improve the AABBtree otherwise stop exploration
      if ( n_left < m_max_object_per_node || n_right < m_max_object_per_node ) {
        // few nodes, check if improve volume
        Real vo = 1;
        Real vL = 1;
        Real vR = 1;
        for ( integer j = 0l; j < m_dim; ++j ) {
          Real Lmin = left_min[j];
          Real Lmax = left_max[j];
          Real Rmin = right_min[j];
          Real Rmax = right_max[j];
          vo *= max(Lmax,Rmax) - min(Lmin,Rmin);
          vL *= Lmax - Lmin;
          vR *= Rmax - Rmin;
        }
        // if do not improve volume, stop split at this level!
        if ( vo > (vL+vR-vo)*m_volume_tolerance ) continue;
      }

      // push child nodes onto stack
      m_father[id_left]  = id_father;
      m_father[id_right] = id_father;
      m_child[id_father] = id_left;

      m_num_nodes[id_father] = n_long;

      m_ptr_nodes[id_left]  = iptr + n_long;
      m_num_nodes[id_left]  = n_left;

      m_ptr_nodes[id_right] = iptr + n_long + n_left;
      m_num_nodes[id_right] = n_right;

      // push on stack children
      m_stack[n_stack++] = id_left;
      m_stack[n_stack++] = id_right;
      m_num_tree_nodes += 2;
    }
  }

  template <typename Real>
  void
  AABBtree<Real>::intersect( Real const * pnt, SET & bb_index ) const {
    int n_check = 0;

    // quick return on empty inputs
    if ( m_num_tree_nodes == 0 ) return;

    // descend tree from root
    m_stack[0] = 0;
    integer n_stack = 1;
    while ( n_stack > 0 ) {
      // pop node from stack
      integer id_father = m_stack[--n_stack];

      // get BBOX
      Real const * father_min = m_bb_min + id_father * m_dim;
      Real const * father_max = m_bb_max + id_father * m_dim;

      ++n_check;
      bool overlap = true;
      for ( integer i = 0; overlap && i < m_dim; ++i ) {
        overlap = father_min[i] <= pnt[i] && pnt[i] <= father_max[i];
      }
      // if do not overlap skip
      if ( !overlap ) continue;

      // get rectangles id in parent
      this->get_nodes( id_father, bb_index );

      integer nn = m_child[id_father];
      if ( nn >= 0 ) {
        // push on stack children
        m_stack[n_stack++] = nn;
        m_stack[n_stack++] = nn+1;
      }
    }
    fmt::print( "n_check = {}\n", n_check );
  }

  template <typename Real>
  void
  AABBtree<Real>::intersect(
    Real const * bb_min,
    Real const * bb_max,
    SET        & bb_index
  ) const {
    int n_check = 0;

    // quick return on empty inputs
    if ( m_num_tree_nodes == 0 ) return;

    // descend tree from root
    m_stack[0] = 0;
    integer n_stack = 1;
    while ( n_stack > 0 ) {
      // pop node from stack
      integer id_father = m_stack[--n_stack];

      // get BBOX
      Real const * father_min = m_bb_min + id_father * m_dim;
      Real const * father_max = m_bb_max + id_father * m_dim;

      ++n_check;
      bool overlap = true;
      for ( integer i = 0; overlap && i < m_dim; ++i ) {
        overlap = father_min[i] <= bb_min[i] && bb_max[i] <= father_max[i];
      }
      // if do not overlap skip
      if ( !overlap ) continue;

      // get rectangles id in parent
      this->get_nodes( id_father, bb_index );

      integer nn = m_child[id_father];
      if ( nn >= 0 ) {
        // push on stack children
        m_stack[n_stack++] = nn;
        m_stack[n_stack++] = nn+1;
      }
    }
    fmt::print( "n_check = {}\n", n_check );
  }

  template <typename Real>
  void
  AABBtree<Real>::intersect(
    AABBtree<Real> const & aabb,
    MAP                  & bb_index
  ) const {

    int n_check = 0;

    // quick return on empty inputs
    if ( this->m_num_tree_nodes == 0 || aabb.m_num_tree_nodes == 0 ) return;

    // descend tree from root
    m_stack[0] = 0;
    m_stack[1] = 0;
    integer n_stack = 2;
    while ( n_stack > 1 ) {
      // pop node from stack
      integer root2 = m_stack[--n_stack];
      integer root1 = m_stack[--n_stack];

      // check for intersection
      Real const * root1_min = this->m_bb_min + root1 * m_dim;
      Real const * root1_max = this->m_bb_max + root1 * m_dim;
      Real const * root2_min = aabb.m_bb_min  + root2 * m_dim;
      Real const * root2_max = aabb.m_bb_max  + root2 * m_dim;

      ++n_check;

      bool overlap = true;
      for ( integer i = 0; overlap && i < m_dim; ++i ) {
        overlap = ! ( root1_min[i] > root2_max[i] || root1_max[i] < root2_min[i] );
      }
      // if do not overlap skip
      if ( !overlap ) continue;

      // check if there are elements to check
      integer nn1 = this->m_num_nodes[root1];
      integer nn2 = aabb.m_num_nodes[root2];
      if ( nn1 > 0 && nn2 > 0 ) aabb.get_nodes( root2, bb_index[root1] );

      integer id_lr1 = m_child[root1];
      integer id_lr2 = aabb.m_child[root2];

      if ( id_lr1 >= 0 ) {
        m_stack[n_stack++] = id_lr1;   m_stack[n_stack++] = root2;
        m_stack[n_stack++] = id_lr1+1; m_stack[n_stack++] = root2;
      } else if ( id_lr2 >= 0 ) {
        m_stack[n_stack++] = root1; m_stack[n_stack++] = id_lr2;
        m_stack[n_stack++] = root1; m_stack[n_stack++] = id_lr2+1;
      }
    }
    fmt::print( "n_check = {}\n", n_check );
  }

  template <typename Real>
  void
  AABBtree<Real>::get_nodes( integer i_pos, SET & bb_index ) const {
    integer num = m_num_nodes[i_pos];
    integer ptr = m_ptr_nodes[i_pos];
    while ( num-- > 0 ) bb_index.insert( m_id_nodes[ptr++] );
  }

  template class AABBtree<float>;
  template class AABBtree<double>;

}

///
/// eof: Utils_AABB_tree.cc
///
