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
/// file: collection.hxx
///

#ifndef INCLUDE_ACME_COLLECTION
#define INCLUDE_ACME_COLLECTION

#include "AABBtree.hxx"
#include "entity.hxx"
#include "intersection.hxx"

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

  //! Collection class container
  /**
   * Collection of entity objects in 3D space.
   */
  class collection
  {
  private:
    entity::vecptr m_entities; //!< Vector of shared pointers to entity objects
    AABBtree::ptr  m_AABBtree; //!< Collection AABB tree pointer

  public:
    //! Collection copy constructor
    collection(collection const &) = default;

    //! Collection move constructor
    collection(collection &&) = default;

    //! Collection class constructor
    collection(void);

    //! Collection class constructor
    collection(
      entity::vecptr & entities //!< Vector of shared pointers to entity objects
    );

    //! Clear all collection object data
    void
    clear(void);

    //! Resize collection shared pointer vector
    void
    resize(
      integer size //!< Input size
    );

    //! Adds a new element at the end of the collection shared pointer vector
    void
    push_back(
      entity::ptr entity //!< Input shared pointer to entity
    );

    //! Get i-th entity object shared pointer reference
    entity::ptr &
    operator[](
      integer i //!< Input i-th value
    );

    //! Get i-th entity object shared pointer const reference
    entity::ptr const &
    operator[](
      integer i //!< Input i-th value
    ) const;

    //! Translate collection by vector
    void
    translate(
      vec3 const & input //!< Input translation vector
    );

    //! Rotate collection by a rotation angle around an arbitrary axis
    void
    rotate(
      real         angle, //!< Input angle [rad]
      vec3 const & axis   //!< Input axis
    );

    //! Rotate tire by a rotation angle around an arbitrary axis
    void
    rotate(
      real                angle, //!< Input angle [rad]
      std::string const & axis   //!< Input axis
    );

    //! Transform collection with affine transformation matrix
    void
    transform(
      affine const & matrix //!< 4x4 affine transformation matrix
    );

    //! Check whether in the collection there are any none entity objects
    bool
    containNone(void)
    const;

    //! Check whether the collection is composed only by none entity objects
    bool
    areNone(void)
    const;

    //! Check whether in the collection the i-th element is a none entity object
    bool
    isNone(
      integer i //!< Input i-th value
    ) const;

    //! Remove all none entity objects from collection
    void
    removeNone(void);

    //! Count all none entity objects in collection
    integer
    countNone(void)
    const;

    //! Check whether in the collection there are any point entity objects
    bool
    containPoint(void)
    const;

    //! Check whether the collection is composed only by point entity objects
    bool
    arePoint(void)
    const;

    //! Check whether in the collection the i-th element is a point entity object
    bool
    isPoint(
      integer i //!< Input i-th value
    ) const;

    //! Remove all point entity objects from collection
    void
    removePoint(void);

    //! Count all point entity objects in collection
    integer
    countPoint(void)
    const;

    //! Check whether in the collection there are any line entity objects
    bool
    containLine(void)
    const;

    //! Check whether the collection is composed only by line entity objects
    bool
    areLine(void)
    const;

    //! Check whether in the collection the i-th element is a line entity object
    bool
    isLine(
      integer i //!< Input i-th value
    ) const;

    //! Remove all line entity objects from collection
    void
    removeLine(void);

    //! Count all line entity objects in collection
    integer
    countLine(void)
    const;

    //! Check whether in the collection there are any ray entity objects
    bool
    containRay(void)
    const;

    //! Check whether the collection is composed only by ray entity objects
    bool
    areRay(void)
    const;

    //! Check whether in the collection the i-th element is a ray entity object
    bool
    isRay(
      integer i //!< Input i-th value
    ) const;

    //! Remove all ray entity objects from collection
    void
    removeRay(void);

    //! Count all ray entity objects in collection
    integer
    countRay(void)
    const;

    //! Check whether in the collection there are any plane entity objects
    bool
    containPlane(void)
    const;

    //! Check whether the collection is composed only by plane entity objects
    bool
    arePlane(void)
    const;

    //! Check whether in the collection the i-th element is a plane entity object
    bool
    isPlane(
      integer i //!< Input i-th value
    ) const;

    //! Remove all plane entity objects from collection
    void
    removePlane(void);

    //! Count all plane entity objects in collection
    integer
    countPlane(void)
    const;

    //! Check whether in the collection there are any segment entity objects
    bool
    containSegment(void)
    const;

    //! Check whether the collection is composed only by segment entity objects
    bool
    areSegment(void)
    const;

    //! Check whether in the collection the i-th element is a segment entity object
    bool
    isSegment(
      integer i //!< Input i-th value
    ) const;

    //! Remove all segment entity objects from collection
    void
    removeSegment(void);

    //! Count all segment entity objects in collection
    integer
    countSegment(void)
    const;

    //! Check whether in the collection there are any triangle entity objects
    bool
    containTriangle(void)
    const;

    //! Check whether the collection is composed only by triangle entity objects
    bool
    areTriangle(void)
    const;

    //! Check whether in the collection the i-th element is a triangle entity object
    bool
    isTriangle(
      integer i //!< Input i-th value
    ) const;

    //! Remove all triangle entity objects from collection
    void
    removeTriangle(void);

    //! Count all triangle entity objects in collection
    integer
    countTriangle(void)
    const;

    //! Check whether in the collection there are any disk entity objects
    bool
    containDisk(void)
    const;

    //! Check whether the collection is composed only by disk entity objects
    bool
    areDisk(void)
    const;

    //! Check whether in the collection the i-th element is a disk entity object
    bool
    isDisk(
      integer i //!< Input i-th value
    ) const;

    //! Remove all disk entity objects from collection
    void
    removeDisk(void);

    //! Count all disk entity objects in collection
    integer
    countDisk(void)
    const;

    //! Check whether in the collection there are any ball entity objects
    bool
    containBall(void)
    const;

    //! Check whether the collection is composed only by ball entity objects
    bool
    areBall(void)
    const;

    //! Check whether in the collection the i-th element is a ball entity object
    bool
    isBall(
      integer i //!< Input i-th value
    ) const;

    //! Remove all ball entity objects from collection
    void
    removeBall(void);

    //! Count all ball entity objects in collection
    integer
    countBall(void)
    const;

    //! Check if one of the objects in the collection is degenerated
    bool
    containDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check whether the collection is composed only by degenerated entity objects
    bool
    areDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check whether in the collection the i-th element is a degenerated entity object
    bool
    isDegenerated(
      integer i,                  //!< Input i-th value
      real    tolerance = EPSILON //!< Tolerance
    ) const;

    //! Remove all degenerated entity objects from collection
    void
    removeDegenerated(
      real tolerance = EPSILON //!< Tolerance
    );

    //! Count all degenerated entity objects in collection
    integer
    countDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check whether in the collection there are any clampable entity objects
    bool
    containClampable(void)
    const;

    //! Check whether the collection is composed only by clampable entity objects
    bool
    areClampable(void)
    const;

    //! Check whether in the collection the i-th element is a clampable entity object
    bool
    isClampable(
      integer i //!< Input i-th value
    ) const;

    //! Remove all clampable entity objects from collection
    void
    removeClampable(void);

    //! Count all clampable entity objects in collection
    integer
    countClampable(void)
    const;

    //! Check whether in the collection there are any non clampable entity objects
    bool
    containNonClampable(void)
    const;

    //! Check whether the collection is composed only by non clampable entity objects
    bool
    areNonClampable(void)
    const;

    //! Check whether in the collection the i-th element is a non clampable entity object
    bool
    isNonClampable(
      integer i //!< Input i-th value
    ) const;

    //! Remove all non clampable entity objects from collection
    void
    removeNonClampable(void);

    //! Count all non clampable entity objects in collection
    integer
    countNonClampable(void)
    const;

    //! Get collection size (number of entities)
    integer
    size(void)
    const;

    //! Count all entity types objects in collection
    std::map<std::string, integer>
    count(
      real tolerance = EPSILON //!< Tolerance
    ) const;

    //! Get vector of shered pointer to collection objects aabbs
    void
    clamp(
      aabb::vecptr & boxes //!< Vector of shered pointer to collection objects aabbs
    ) const;

    //! Build collection AABB tree
    void
    buildAABBtree(void);

    //! Return collection AABB tree shared pointer
    AABBtree::ptr const &
    ptrAABBtree(void);

    //! Intersect the collection with an external collection
    bool
    intersection(
      collection & entities,  //!< External entities collection
      collection & candidates //!< Intersection candidates
    ) const;

    //! Intersect the collection AABB tree with an external AABB tree
    bool
    intersection(
      AABBtree::ptr const & AABBtree, //!< External AABBtree object pointer
      collection          & entities  //!< Intersected entities vector list
    ) const;

    //! Update the collection AABBtree with an external aabb object pointer vector
    bool
    intersection(
      aabb::vecptr const & boxes,   //!< External aabb object pointer vector
      collection         & entities //!< Intersected entities vector list
    ) const;

    //! Update the collection AABBtree with an external aabb object pointer
    bool
    intersection(
      aabb::ptr  const   box,     //!< External aabb object pointer
      collection       & entities //!< Intersected entities vector list
    ) const;

    //! Intersect all entities of the two collections
    void
    intersection(
      collection & entities,           //!< Intersection candidates
      real         tolerance = EPSILON //!< Tolerance
    ) const;

  }; // class collection

} // namespace acme

#endif

///
/// eof: collection.hxx
///
