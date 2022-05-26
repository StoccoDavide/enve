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
(*                                                                     *)
(*  Reference:                                                         *)
(*  Efficient intersection between splines of clothoids.               *)
(*  Enrico Bertolazzi, Paolo Bevilacqua, Marco Frego                   *)
(*  October 2019 - Mathematics and Computers in Simulation 176         *)
(*  DOI: 10.1016/j.matcom.2019.10.001                                  *)
(*                                                                     *)
(*  URL: https://github.com/ebertolazzi/Clothoids                      *)
(*                                                                     *)
(***********************************************************************)
*/

///
/// file: acme_aabbTree.hh
///

#pragma once

#ifndef INCLUDE_ACME_AABBTREE
#define INCLUDE_ACME_AABBTREE

#include "acme.hh"
#include "acme_aabb.hh"
#include "acme_math.hh"

namespace acme
{

  /*\
   |      _        _    ____  ____  _
   |     / \      / \  | __ )| __ )| |_ _ __ ___  ___
   |    / _ \    / _ \ |  _ \|  _ \| __| '__/ _ \/ _ \
   |   / ___ \  / ___ \| |_) | |_) | |_| | |  __/  __/
   |  /_/   \_\/_/   \_\____/|____/ \__|_|  \___|\___|
   |
  \*/

  //! Axis-aligned bouding box tree class container
  /**
   * Axis-aligned bouding box AABB tree.
   */
  class AABBtree
  {
  public:
    typedef std::shared_ptr<AABBtree> ptr;    //!< Shared ointer to AABB tree object
    typedef std::vector<ptr>          vecptr; //!< Vector of pointers to AABB tree objects

  private:
    aabb::ptr        m_ptrbox;   //!< Pointer to AABB tree
    AABBtree::vecptr m_children; //!< Pointers to children AABB tree

    //! AABBtree copy constructor
    AABBtree(AABBtree const &tree);

  public:
    //! AABB tree class destructor
    ~AABBtree(void);

    //! AABB tree class constructor
    AABBtree(void);

    //! Clear AABB tree data
    void
    clear(void);

    //! Check if AABB tree is empty
    bool
    isEmpty(void) const;

    //! Build AABB tree given a list of boxes
    void
    build(
      aabb::vecptr const &boxes //!< List of boxes
    );

    //! Print AABB tree data
    void
    print(
      out_stream &stream,   //!< Output stream
      int         level = 0 //!< Level to print
    ) const;

    //! Check if two AABB tree collide
    template <typename collisionFunction>
    bool
    collision(
      AABBtree const   &tree,             //!< AABB tree used to check collision
      collisionFunction function,         //!< Function to check if the contents of two aabb collide
      bool              swap_tree = false //!< If true exchange the tree in computation
    ) const
    {

      // check aabb with
      if (!tree.m_ptrbox->intersects(*this->m_ptrbox))
        return false;

      int icase = (this->m_children.empty() ? 0 : 1) +
                  (tree.m_children.empty() ? 0 : 2);

      switch (icase)
      {
      case 0: // both leaf, use aabb intersection algorithm
        if (swap_tree)
          return function(tree.m_ptrbox, this->m_ptrbox);
        else
          return function(this->m_ptrbox, tree.m_ptrbox);
      case 1: // first is a tree, second is a leaf
      {
        typename AABBtree::vecptr::const_iterator it;
        for (it = this->m_children.begin(); it != this->m_children.end(); ++it)
          if (tree.collision(**it, function, !swap_tree))
            return true;
      }
      break;
      case 2: // first leaf, second is a tree
      {
        typename AABBtree::vecptr::const_iterator it;
        for (it = tree.m_children.begin();
             it != tree.m_children.end();
             ++it)
          if (this->collision(**it, function, swap_tree))
            return true;
      }
      break;
      case 3: // first is a tree, second is a tree
      {
        typename AABBtree::vecptr::const_iterator it1;
        typename AABBtree::vecptr::const_iterator it2;
        for (it1 = this->m_children.begin(); it1 != this->m_children.end(); ++it1)
          for (it2 = tree.m_children.begin();
               it2 != tree.m_children.end();
               ++it2)
            if ((*it1)->collision(**it2, function, swap_tree))
              return true;
      }
      break;
      }
      return false;
    }

    //! Compute all the intersection candidates of AABB trees
    void
    intersection(
      AABBtree const   &tree,             //!< AABB tree used to check collision
      aabb::vecpairptr &intersectionList, //!< List of pair aabb that overlaps
      bool              swap_tree = false //!< If true exchange the tree in computation
    ) const;

  private:
    //! Find the candidate at minimum distance from point
    void
    selectMinimumDistance(
      point const  &query,        //!< Input point
      aabb::vecptr &candidateList //!< Output candidate list
    ) const;

    //! Compute the minimum of the maximum distance between a point
    static real
    minimumExteriorDistance(
      point const    &query,   //!< Input point
      AABBtree const &tree,    //!< Input tree
      real            distance //!< Output distance
    );

    //! Select the candidate which aabb have distance less than distance
    static void
    selectLessThanDistance(
      point const    &query,        //!< Input point
      real            distance,     //!< Input distance
      AABBtree const &tree,         //!< Input tree
      aabb::vecptr   &candidateList //!< Output candidate list
    );

  }; // class AABBtree

} // namespace acme

#endif

///
/// eof: acme_aabbTree.hh
///