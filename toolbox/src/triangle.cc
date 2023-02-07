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
/// file: triangle.cc
///

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include "acme.hh"

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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangle::triangle(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangle::triangle(
    real vertex0_x,
    real vertex0_y,
    real vertex0_z,
    real vertex1_x,
    real vertex1_y,
    real vertex1_z,
    real vertex2_x,
    real vertex2_y,
    real vertex2_z
  )
    : m_vertex{point(vertex0_x, vertex0_y, vertex0_z),
               point(vertex1_x, vertex1_y, vertex1_z),
               point(vertex2_x, vertex2_y, vertex2_z)}
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangle::triangle(
    point const & vertex0,
    point const & vertex1,
    point const & vertex2
  )
    : m_vertex{vertex0, vertex1, vertex2}
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  triangle::triangle(
    point const vertex[3]
  )
    : m_vertex{vertex[0], vertex[1], vertex[2]}
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  triangle::isApprox(
    triangle const & triangle_in,
    real             tolerance
  )
    const
  {
    return this->m_vertex[0].isApprox(triangle_in.m_vertex[0], tolerance) &&
           this->m_vertex[1].isApprox(triangle_in.m_vertex[1], tolerance) &&
           this->m_vertex[2].isApprox(triangle_in.m_vertex[2], tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  triangle::vertex(
    integer i
  )
    const
  {
    #define CMD "acme::triangle::vertex(): "

    ACME_ASSERT(i < 3,
      CMD "index out of bounds [0,2].")
    return this->m_vertex[i];

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  triangle::vertex(
    integer i
  )
  {
    #define CMD "acme::triangle::vertex(): "

    ACME_ASSERT(i < 3,
      CMD "index out of bounds [0,2].")
    return this->m_vertex[i];

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point const &
  triangle::operator[](
    integer i
  )
    const
  {
    #define CMD "acme::triangle::operator[]: "

    ACME_ASSERT(i < 3,
      CMD "index out of bounds [0,2].")
    return this->m_vertex[i];

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point &
  triangle::operator[](
    integer i
  )
  {
    #define CMD "acme::triangle::operator[]: "

    ACME_ASSERT(i < 3,
      CMD "index out of bounds [0,2].")
    return this->m_vertex[i];

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point
  triangle::centroid(void)
    const
  {
    return (this->m_vertex[0] + this->m_vertex[1] + this->m_vertex[2]) / real(3.0);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  segment
  triangle::edge(
    integer i
  )
    const
  {
    #define CMD "acme::triangle::edge(): "

    ACME_ASSERT(i < 3,
      CMD "index out of bounds [0,2].")
    if (i == 0)
      {return segment(this->m_vertex[0], this->m_vertex[1]);}
    else if (i == 1)
      {return segment(this->m_vertex[1], this->m_vertex[2]);}
    else // (i == 2)
      {return segment(this->m_vertex[2], this->m_vertex[0]);}

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  triangle::normal(void)
    const
  {
    return (this->m_vertex[1] - this->m_vertex[0]).cross(this->m_vertex[2] - this->m_vertex[0]).normalized();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  triangle::swap(
    integer i,
    integer j
  )
  {
    point tmp_vertex_i(this->m_vertex[i]);
    point tmp_vertex_j(this->m_vertex[j]);
    this->m_vertex[i] = tmp_vertex_j;
    this->m_vertex[j] = tmp_vertex_i;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  triangle::perimeter(void)
    const
  {
    return (this->m_vertex[0] - this->m_vertex[1]).norm() +
           (this->m_vertex[1] - this->m_vertex[2]).norm() +
           (this->m_vertex[2] - this->m_vertex[0]).norm();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  triangle::area(void)
    const
  {
    return ((this->m_vertex[1] - this->m_vertex[0]).cross(this->m_vertex[2] - this->m_vertex[0])).norm() / real(2.0);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  triangle::barycentric(
    point const & point_in,
    real        & u,
    real        & v,
    real        & w
  )
    const
  {
    point v0(this->m_vertex[1] - this->m_vertex[0]);
    point v1(this->m_vertex[2] - this->m_vertex[0]);
    point v2(point_in - this->m_vertex[0]);
    real  d00   = v0.dot(v0);
    real  d01   = v0.dot(v1);
    real  d11   = v1.dot(v1);
    real  d20   = v2.dot(v0);
    real  d21   = v2.dot(v1);
    real  denom = d00 * d11 - d01 * d01;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = real(1.0) - v - w;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  plane
  triangle::layingPlane(void)
    const
  {
    return plane(this->centroid(), this->normal());
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  triangle::translate(
    vec3 const & vector_in
  )
  {
    this->m_vertex[0] = vector_in + this->m_vertex[0];
    this->m_vertex[1] = vector_in + this->m_vertex[1];
    this->m_vertex[2] = vector_in + this->m_vertex[2];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  triangle::transform(
    affine const & affine_in
  )
  {
    this->m_vertex[0].transform(affine_in);
    this->m_vertex[1].transform(affine_in);
    this->m_vertex[2].transform(affine_in);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  triangle::isInside(
    point const & point_in,
    real          tolerance
  )
    const
  {
    real u, v, w;
    this->barycentric(point_in, u, v, w);
    if (u >= real(0.0) - tolerance && u <= real(1.0) + tolerance &&
        v >= real(0.0) - tolerance && v <= real(1.0) + tolerance &&
        w >= real(0.0) - tolerance && w <= real(1.0) + tolerance)
    {
      return this->layingPlane().isInside(point_in, tolerance);
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  triangle::isDegenerated(
    real tolerance
  )
    const
  {
    return IsApprox((this->m_vertex[0] - this->m_vertex[1]).norm(), real(0.0), tolerance) ||
           IsApprox((this->m_vertex[1] - this->m_vertex[2]).norm(), real(0.0), tolerance) ||
           IsApprox((this->m_vertex[2] - this->m_vertex[0]).norm(), real(0.0), tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  triangle::clamp(
    vec3 & min,
    vec3 & max
  )
    const
  {
    min(0) = std::min(this->m_vertex[0].x(), std::min(this->m_vertex[1].x(), this->m_vertex[2].x()));
    min(1) = std::min(this->m_vertex[0].y(), std::min(this->m_vertex[1].y(), this->m_vertex[2].y()));
    min(2) = std::min(this->m_vertex[0].z(), std::min(this->m_vertex[1].z(), this->m_vertex[2].z()));
    max(0) = std::max(this->m_vertex[0].x(), std::max(this->m_vertex[1].x(), this->m_vertex[2].x()));
    max(1) = std::max(this->m_vertex[0].y(), std::max(this->m_vertex[1].y(), this->m_vertex[2].y()));
    max(2) = std::max(this->m_vertex[0].z(), std::max(this->m_vertex[1].z(), this->m_vertex[2].z()));
    return this->isClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  triangle::clamp(
    real & min_x,
    real & min_y,
    real & min_z,
    real & max_x,
    real & max_y,
    real & max_z
  )
    const
  {
    min_x = std::min(this->m_vertex[0].x(), std::min(this->m_vertex[1].x(), this->m_vertex[2].x()));
    min_y = std::min(this->m_vertex[0].y(), std::min(this->m_vertex[1].y(), this->m_vertex[2].y()));
    min_z = std::min(this->m_vertex[0].z(), std::min(this->m_vertex[1].z(), this->m_vertex[2].z()));
    max_x = std::max(this->m_vertex[0].x(), std::max(this->m_vertex[1].x(), this->m_vertex[2].x()));
    max_y = std::max(this->m_vertex[0].y(), std::max(this->m_vertex[1].y(), this->m_vertex[2].y()));
    max_z = std::max(this->m_vertex[0].z(), std::max(this->m_vertex[1].z(), this->m_vertex[2].z()));
    return this->isClampable();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

#endif

///
/// eof: triangle.cc
///
