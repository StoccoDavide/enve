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
/// file: acme_AABBtree.cc
///

#include "acme_AABBtree.hh"

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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  AABBtree::~AABBtree(void)
  {
    this->m_ptrbox.reset();
    this->m_children.clear();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  AABBtree::AABBtree(void)
  {
    this->m_ptrbox.reset();
    this->m_children.clear();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AABBtree::clear(void)
  {
    this->m_ptrbox.reset();
    this->m_children.clear();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  AABBtree::isEmpty(void)
    const
  {
    return this->m_children.empty() && !this->m_ptrbox;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AABBtree::build(
    aabb::vecptr const &boxes)
  {
    clear();

    if (boxes.empty())
      return;

    integer size = boxes.size();

    if (size == 1)
    {
      this->m_ptrbox = boxes.front();
      return;
    }

    this->m_ptrbox = std::make_shared<aabb const>(boxes, 0, 0);

    real xmin = this->m_ptrbox->min(0);
    real ymin = this->m_ptrbox->min(1);
    real zmin = this->m_ptrbox->min(2);
    real xmax = this->m_ptrbox->max(0);
    real ymax = this->m_ptrbox->max(1);
    real zmax = this->m_ptrbox->max(2);

    aabb::vecptr pos_boxes;
    aabb::vecptr neg_boxes;

    if ((xmax - xmin) > (ymax - ymin) && (xmax - xmin) > (zmax - zmin))
    {
      real                         cut_pos = (xmax + xmin) / 2;
      aabb::vecptr::const_iterator it;
      for (it = boxes.begin(); it != boxes.end(); ++it)
      {
        real xmid = ((*it)->min(0) + (*it)->max(0)) / 2;
        if (xmid > cut_pos)
          pos_boxes.push_back(*it);
        else
          neg_boxes.push_back(*it);
      }
    }
    else if ((ymax - ymin) > (xmax - xmin) && (ymax - ymin) > (zmax - zmin))
    {
      real                         cut_pos = (ymax + ymin) / 2;
      aabb::vecptr::const_iterator it;
      for (it = boxes.begin(); it != boxes.end(); ++it)
      {
        real ymid = ((*it)->min(1) + (*it)->max(1)) / 2;
        if (ymid > cut_pos)
          pos_boxes.push_back(*it);
        else
          neg_boxes.push_back(*it);
      }
    }
    else
    {
      real                         cut_pos = (zmax + zmin) / 2;
      aabb::vecptr::const_iterator it;
      for (it = boxes.begin(); it != boxes.end(); ++it)
      {
        real zmid = ((*it)->min(1) + (*it)->max(1)) / 2;
        if (zmid > cut_pos)
          pos_boxes.push_back(*it);
        else
          neg_boxes.push_back(*it);
      }
    }

    if (neg_boxes.empty())
    {
      aabb::vecptr::iterator mid_idx;
      mid_idx = pos_boxes.begin() + pos_boxes.size() / 2;
      neg_boxes.insert(neg_boxes.end(), mid_idx, pos_boxes.end());
      pos_boxes.erase(mid_idx, pos_boxes.end());
    }
    else if (pos_boxes.empty())
    {
      aabb::vecptr::iterator mid_idx;
      mid_idx = neg_boxes.begin() + neg_boxes.size() / 2;
      pos_boxes.insert(pos_boxes.end(), mid_idx, neg_boxes.end());
      neg_boxes.erase(mid_idx, neg_boxes.end());
    }

    AABBtree::ptr neg = std::make_shared<AABBtree>();
    AABBtree::ptr pos = std::make_shared<AABBtree>();

    neg->build(neg_boxes);
    if (!neg->isEmpty())
      this->m_children.push_back(neg);

    pos->build(pos_boxes);
    if (!pos->isEmpty())
      this->m_children.push_back(pos);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AABBtree::print(
    out_stream &os,
    integer     level)
    const
  {
    if (this->isEmpty())
    {
      os << "[EMPTY AABB tree]" << std::endl;
    }
    else
    {
      os << std::scientific
         << std::showpoint
         << std::setprecision(10)
         << "Box =" << std::endl
         << "Minimum = [ " << this->m_ptrbox->min(0) << ", " << this->m_ptrbox->min(1) << ", " << this->m_ptrbox->min(2) << " ]'" << std::endl
         << "Maximum = [ " << this->m_ptrbox->max(0) << ", " << this->m_ptrbox->max(1) << ", " << this->m_ptrbox->max(2) << " ]'" << std::endl
         << std::endl;
      AABBtree::vecptr::const_iterator it;
      for (it = this->m_children.begin(); it != this->m_children.end(); ++it)
        (*it)->print(os, level + 1);
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AABBtree::intersection(
    AABBtree const   &tree,
    aabb::vecpairptr &intersection_list,
    bool              swap_tree)
    const
  {
    // Check aabb with
    if (!tree.m_ptrbox->intersects(*this->m_ptrbox))
      return;
    integer icase = (this->m_children.empty() ? 0 : 1) +
                    (tree.m_children.empty() ? 0 : 2);
    switch (icase)
    {
    case 0: // Both are leafs
      if (swap_tree)
        intersection_list.push_back(aabb::pairptr(tree.m_ptrbox, this->m_ptrbox));
      else
        intersection_list.push_back(aabb::pairptr(this->m_ptrbox, tree.m_ptrbox));
      break;
    case 1: // First is a tree, second is a leaf
    {
      AABBtree::vecptr::const_iterator it;
      for (it = this->m_children.begin(); it != this->m_children.end(); ++it)
        tree.intersection(**it, intersection_list, !swap_tree);
    }
    break;
    case 2: // First leaf, second is a tree
    {
      AABBtree::vecptr::const_iterator it;
      for (it = tree.m_children.begin(); it != tree.m_children.end(); ++it)
        this->intersection(**it, intersection_list, swap_tree);
    }
    break;
    case 3: // First is a tree, second is a tree
    {
      AABBtree::vecptr::const_iterator c1;
      AABBtree::vecptr::const_iterator c2;
      for (c1 = this->m_children.begin(); c1 != this->m_children.end(); ++c1)
        for (c2 = tree.m_children.begin(); c2 != tree.m_children.end(); ++c2)
          (*c1)->intersection(**c2, intersection_list, swap_tree);
    }
    break;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  AABBtree::minimumExteriorDistance(
    point const    &query,
    AABBtree const &tree,
    real            distance)
  {
    AABBtree::vecptr const &tree_children = tree.m_children;
    if (tree_children.empty())
    {
      real dst = tree.m_ptrbox->exteriorDistance(query);
      return std::min(dst, distance);
    }
    real dmin = tree.m_ptrbox->centerDistance(query);
    if (dmin > distance)
      return distance;
    // check aabb with
    AABBtree::vecptr::const_iterator it;
    for (it = tree_children.begin(); it != tree_children.end(); ++it)
      distance = minimumExteriorDistance(query, **it, distance);
    return distance;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AABBtree::selectLessThanDistance(
    point const    &query,
    real            distance,
    AABBtree const &tree,
    aabb::vecptr   &candidate_list)
  {
    AABBtree::vecptr const &tree_children = tree.m_children;
    real                    dst           = tree.m_ptrbox->centerDistance(query);
    if (dst <= distance)
    {
      if (tree_children.empty())
      {
        candidate_list.push_back(tree.m_ptrbox);
      }
      else
      {
        // Check aabb with
        AABBtree::vecptr::const_iterator it;
        for (it = tree_children.begin(); it != tree_children.end(); ++it)
          selectLessThanDistance(query, distance, **it, candidate_list);
      }
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AABBtree::selectMinimumDistance(
    point const  &query,
    aabb::vecptr &candidate_list)
    const
  {
    real distance = this->minimumExteriorDistance(query, *this, INFTY);
    this->selectLessThanDistance(query, distance, *this, candidate_list);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

///
/// eof: acme_AABBtree.cc
///
