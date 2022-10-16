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
/// file: triangle.hxx
///

#ifndef INCLUDE_ACME_TRIANGLE
#define INCLUDE_ACME_TRIANGLE

#include "aabb.hxx"
#include "point.hxx"
#include "plane.hxx"
#include "segment.hxx"

namespace acme
{

  /*\
   |   _        _                   _
   |  | |_ _ __(_) __ _ _ __   __ _| | ___
   |  | __| '__| |/ _` | '_ \ / _` | |/ _ \
   |  | |_| |  | | (_| | | | | (_| | |  __/
   |   \__|_|  |_|\__,_|_| |_|\__, |_|\___|
   |                          |___/
  \*/

  //! Triangle class container
  /**
   * Triangle in 3D space. The triangle is defined by three arbitrary points.
   */
  class triangle : public entity
  {
  private:
    point m_vertex[3] = {NAN_POINT, NAN_POINT, NAN_POINT}; //!< Triangle vertices

  public:
    //! Triangle copy constructor
    triangle(triangle const &) = default;

    //! Triangle move constructor
    triangle(triangle &&) = default;

    //! Triangle assignment operator    
    triangle & operator=(const triangle &) = default;

    //! Triangle move assignment operator    
    triangle & operator=(triangle &&) = default;
    
    //! Triangle class destructor
    ~triangle(void) override = default;

    //! Triangle class constructor
    triangle(void);

    //! Triangle class constructor
    triangle(
      real vertex0_x, //!< Input x value of first triangle vertex
      real vertex0_y, //!< Input y value of first triangle vertex
      real vertex0_z, //!< Input z value of first triangle vertex
      real vertex1_x, //!< Input x value of second triangle vertex
      real vertex1_y, //!< Input y value of second triangle vertex
      real vertex1_z, //!< Input z value of second triangle vertex
      real vertex2_x, //!< Input x value of third triangle vertex
      real vertex2_y, //!< Input y value of third triangle vertex
      real vertex2_z  //!< Input z value of third triangle vertex
    );

    //! Triangle class constructor
    triangle(
      point const & vertex0, //!< Input first triangle vertex point
      point const & vertex1, //!< Input second triangle vertex point
      point const & vertex2  //!< Input third triangle vertex point
    );

    //! Triangle class constructor
    triangle(
      point const vertex[3] //!< Input triangle verices
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      triangle const & triangle_in,        //!< Input triangle object
      real             tolerance = EPSILON //!< Tolerance
    ) const;

    //! Get i-th triangle vertex const reference
    point const &
    vertex(
      integer i //!< New triangle vertex
    ) const;

    //! Get i-th triangle vertex reference
    point &
    vertex(
      integer i //!< New triangle vertex
    );

    //! Get i-th triangle vertex const reference
    point const &
    operator[](
      integer i //!< New triangle vertex
    ) const;

    //! Get i-th triangle vertex reference
    point &
    operator[](
      integer i //!< New triangle vertex
    );

    //! Get triangle centroid
    point
    centroid(void)
    const;

    //! Get triangle edge created by i-th and j-th vertices
    segment
    edge(
      integer i //!< Triangle i-th vertex index
    ) const;

    //! Get triangle face normal (normalized vector)
    vec3
    normal(void)
    const;

    //! Swap triangle vertices
    void
    swap(
      integer i, //!< Triangle i-th vertex index
      integer j  //!< Triangle j-th vertex index
    );

    //! Calculate triangle perimeter length
    real
    perimeter(void)
    const;

    //! Calculate triangle area
    real
    area(void)
    const;

    //! Compute barycentric coordinates (u,v,w) for point
    void
    barycentric(
      point const & point_in, //!< Input point
      real        & u,        //!< Output barycentric coordinate u
      real        & v,        //!< Output barycentric coordinate v
      real        & w         //!< Output barycentric coordinate w
    ) const;

    //! Get triangle laying plane
    plane
    layingPlane(void)
    const;

    //! Translate triangle by vector
    void
    translate(
      vec3 const & vector_in //!< Input translation vector
    ) override;

    //! Transform triangle with affine transformation matrix
    void
    transform(
      affine const & affine_in //!< 4x4 affine transformation matrix
    ) override;

    //! Check if a point lays inside the triangle
    bool
    isInside(
      point const & point_in,           //!< Query point
      real          tolerance = EPSILON //!< Tolerance
    ) const;

    //! Check if triangle is degenerated to point or segment
    bool
    isDegenerated(
      real tolerance = EPSILON //!< Tolerance
    ) const override;

    //! Return object hierarchical level
    inline
    integer
    level(void)
      const override
    {
      return integer(7);
    }

    //! Return object type as string
    inline
    std::string
    type(void)
      const override
    {
      return "triangle";
    }

    //! Check whether the object is no entity
    inline
    bool
    isNone(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a point
    inline
    bool
    isPoint(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a line
    inline
    bool
    isLine(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a ray
    inline
    bool
    isRay(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a plane
    inline
    bool
    isPlane(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a segment
    inline
    bool
    isSegment(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a triangle
    inline
    bool
    isTriangle(void)
      const override
    {
      return true;
    }

    //! Check whether the object is a disk
    inline
    bool
    isDisk(void)
      const override
    {
      return false;
    }

    //! Check whether the object is a ball
    inline
    bool
    isBall(void)
      const override
    {
      return false;
    }

    //! Check whether in the triangle is clampable
    inline
    bool
    isClampable(void)
      const override
    {
      return true;
    }

    //! Check whether in the triangle is non-clampable
    inline
    bool
    isNonClampable(void)
      const override
    {
      return false;
    }

    //! Get minumum and maximum values along axes
    bool
    clamp(
      vec3 & min, //!< Input minimum point
      vec3 & max  //!< Input maximum point
    ) const override;

    //! Get minumum and maximum values along axes
    bool
    clamp(
      real & min_x, //!< Input x value of minimum point
      real & min_y, //!< Input y value of minimum point
      real & min_z, //!< Input z value of minimum point
      real & max_x, //!< Input x value of maximum point
      real & max_y, //!< Input y value of maximum point
      real & max_z  //!< Input z value of maximum point
    ) const override;

  }; // class triangle

  static triangle const & NAN_TRIANGLE   = * new triangle(NAN_POINT, NAN_POINT, NAN_POINT); //!< Not-a-Number static const triangle object
  static triangle       & DUMMY_TRIANGLE = * new triangle(NAN_POINT, NAN_POINT, NAN_POINT); //!< Dummy static non-const triangle object

} // namespace acme

#endif

///
/// eof: triangle.hxx
///
