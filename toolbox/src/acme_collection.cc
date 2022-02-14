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
/// file: acme_collection.cc
///

#include "acme_collection.hh"

namespace acme
{

  /*\
   |             _ _           _   _
   |    ___ ___ | | | ___  ___| |_(_) ___  _ __
   |   / __/ _ \| | |/ _ \/ __| __| |/ _ \| '_ \
   |  | (_| (_) | | |  __/ (__| |_| | (_) | | | |
   |   \___\___/|_|_|\___|\___|\__|_|\___/|_| |_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  collection::~collection(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  collection::collection(void)
    : m_AABBtree(std::make_shared<AABBtree>())
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  collection::collection(
    entity::vecptr &entities)
    : collection()
  {
    this->m_entities = entities;
  };

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::clear(void)
  {
    this->m_entities.clear();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::resize(
    size_t size)
  {
    this->m_entities.resize(size);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::push_back(
    entity::ptr entity_in)
  {
    this->m_entities.push_back(entity_in);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  entity::ptr &
  collection::operator[](
    size_t i)
  {
    return this->m_entities[i];
  };

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  entity::ptr const &
  collection::operator[](
    size_t i)
    const
  {
    return this->m_entities[i];
  };

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::translate(
    vec3 const &input)
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
      this->m_entities[i]->translate(input);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::rotate(
    real        angle,
    vec3 const &axis)
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
      this->m_entities[i]->rotate(angle, axis);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::transform(
    affine const &matrix)
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
      this->m_entities[i]->transform(matrix);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containNone(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isNone())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::areNone(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isNone())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isNone(
    size_t i)
    const
  {
    return this->m_entities[i]->isNone();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removeNone(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isNone(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countNone(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isNone())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containPoint(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isPoint())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::arePoint(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isPoint())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isPoint(
    size_t i)
    const
  {
    return this->m_entities[i]->isPoint();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removePoint(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isPoint(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countPoint(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isPoint())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containLine(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isLine())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::areLine(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isLine())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isLine(
    size_t i)
    const
  {
    return this->m_entities[i]->isLine();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removeLine(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isLine(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countLine(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isLine())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containRay(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isRay())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::areRay(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isRay())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isRay(
    size_t i)
    const
  {
    return this->m_entities[i]->isRay();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removeRay(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isRay(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countRay(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isRay())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containPlane(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isPlane())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::arePlane(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isPlane())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isPlane(
    size_t i)
    const
  {
    return this->m_entities[i]->isPlane();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removePlane(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isPlane(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countPlane(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isPlane())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containSegment(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isSegment())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::areSegment(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isBall())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isSegment(
    size_t i)
    const
  {
    return this->m_entities[i]->isSegment();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removeSegment(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isSegment(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countSegment(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isSegment())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containTriangle(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isTriangle())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::areTriangle(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isTriangle())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isTriangle(
    size_t i)
    const
  {
    return this->m_entities[i]->isTriangle();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removeTriangle(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isTriangle(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countTriangle(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isTriangle())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containDisk(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isDisk())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::areDisk(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isDisk())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isDisk(
    size_t i)
    const
  {
    return this->m_entities[i]->isDisk();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removeDisk(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isDisk(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countDisk(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isDisk())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containBall(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isBall())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::areBall(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isBall())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isBall(
    size_t i)
    const
  {
    return this->m_entities[i]->isBall();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removeBall(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isBall(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countBall(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isBall())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containDegenerated(
    real tolerance)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isDegenerated(tolerance))
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::areDegenerated(
    real tolerance)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isDegenerated(tolerance))
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isDegenerated(
    size_t i,
    real   tolerance)
    const
  {
    return this->m_entities[i]->isDegenerated(tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removeDegenerated(
    real tolerance)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [tolerance](entity::ptr &entity)
      { return entity->isDegenerated(tolerance); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countDegenerated(
    real tolerance)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isDegenerated(tolerance))
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containClampable(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isClampable())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::areClampable(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isClampable())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isClampable(
    size_t i)
    const
  {
    return this->m_entities[i]->isClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removeClampable(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isClampable(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countClampable(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isClampable())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::containNonClampable(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->isNonClampable())
        return true;
    }
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::areNonClampable(void)
    const
  {
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isNonClampable())
        return false;
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::isNonClampable(
    size_t i)
    const
  {
    return this->m_entities[i]->isNonClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::removeNonClampable(void)
  {
    remove_if(
      this->m_entities.begin(),
      this->m_entities.end(),
      [](entity::ptr &entity)
      { return entity->isNonClampable(); });
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::countNonClampable(void)
    const
  {
    integer count = 0;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (!this->m_entities[i]->isNonClampable())
        ++count;
    }
    return count;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  collection::size(void)
    const
  {
    return integer(this->m_entities.size());
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  std::map<std::string, integer>
  collection::count(
    real tolerance)
    const
  {
    return {{"none", this->countNone()}, {"point", this->countPoint()}, {"line", this->countLine()}, {"ray", this->countRay()}, {"plane", this->countPlane()}, {"segment", this->countSegment()}, {"triangle", this->countTriangle()}, {"disk", this->countDisk()}, {"ball", this->countBall()}, {"degenerated", this->countDegenerated(tolerance)}, {"clampable", this->countClampable()}, {"non-clampable", this->countNonClampable()}};
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::clamp(aabb::vecptr &boxes) const
  {
    boxes.clear();
    vec3 min;
    vec3 max;
    for (size_t i = 0; i < this->m_entities.size(); ++i)
    {
      if (this->m_entities[i]->clamp(min, max))
        boxes.push_back(std::make_shared<aabb>(min, max, i, 0));
      else
        ACME_ERROR("acme::collection::clamp(): non-clampable object detected.");
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::buildAABBtree(void)
  {
    aabb::vecptr ptrVecbox;
    this->clamp(ptrVecbox);
    this->m_AABBtree->build(ptrVecbox);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  AABBtree::ptr const &
  collection::ptrAABBtree(void)
  {
    return this->m_AABBtree;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::intersection(
    collection &entities,
    collection &candidates)
    const
  {
    candidates.clear();
    aabb::vecpairptr intersection_list;
    this->m_AABBtree->intersection(*entities.ptrAABBtree(), intersection_list);
    for (size_t i = 0; i < intersection_list.size(); ++i)
    {
      candidates.push_back(this->m_entities[(intersection_list[i].first)->id()]);
      candidates.push_back(entities[(intersection_list[i].second)->id()]);
    }
    return candidates.size() > 0;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::intersection(
    AABBtree::ptr const &ptrAABBtree,
    collection          &candidates)
    const
  {
    candidates.clear();
    aabb::vecpairptr intersection_list;
    this->m_AABBtree->intersection(*ptrAABBtree, intersection_list);
    for (size_t i = 0; i < intersection_list.size(); ++i)
      candidates.push_back(this->m_entities[(intersection_list[i].first)->id()]);
    return candidates.size() > 0;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::intersection(
    aabb::vecptr const &ptrVecbox,
    collection         &candidates)
    const
  {
    AABBtree::ptr ptrAABBtree(std::make_shared<AABBtree>());
    ptrAABBtree->build(ptrVecbox);
    return this->intersection(ptrAABBtree, candidates);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  collection::intersection(
    aabb::ptr const ptrbox,
    collection     &candidates)
    const
  {
    aabb::vecptr ptrVecbox;
    ptrVecbox.push_back(ptrbox);
    return this->intersection(ptrVecbox, candidates);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  collection::intersection(
    collection &entities,
    real        tolerance)
    const
  {
    size_t size = this->m_entities.size();
    entities.clear();
    for (size_t i = 0; i < size; ++i)
      for (size_t j = i; j < size; ++j)
        entities.push_back(entity::ptr(acme::intersection(this->m_entities[i].get(), this->m_entities[j].get(), tolerance)));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

///
/// eof: acme_collection.cc
///