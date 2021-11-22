/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Enrico Bertolazzi.       *)
(*                                                                     *)
(* The ENVE project and its components are supplied under the terms of *)
(* the open source BSD 2-Clause License. The contents of the ENVE      *)
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
/// file: enve_shell.cc
///

#include "enve_shell.hh"

using namespace acme;

namespace enve
{

  /*\
   |       _          _ _
   |   ___| |__   ___| | |
   |  / __| '_ \ / _ \ | |
   |  \__ \ | | |  __/ | |
   |  |___/_| |_|\___|_|_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shell::~shell(void)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shell::shell(
    size_t size,
    real   r_x,
    real   m_x,
    real   r_y,
    real   m_y,
    real   l_y)
    : m_shape(std::make_shared<hyperellipse>(r_x, m_x, r_y, m_y, l_y)),
      m_bbox(std::make_shared<aabb>())
  {
    this->m_affine.matrix() = IDENTITY_MAT4;
    this->reset(size);
    this->updateBBox();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shell::shell(
    size_t size,
    vecN   dataR,
    vecN   dataY,
    size_t order,
    real   tolerance)
    : m_shape(std::make_shared<polynom>(dataR, dataY, order, tolerance)),
      m_bbox(std::make_shared<aabb>())
  {
    this->m_affine.matrix() = IDENTITY_MAT4;
    this->reset(size);
    this->updateBBox();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shell::shell(
    size_t size,
    vecN   dataR,
    vecN   dataY)
    : m_shape(std::make_shared<points>(dataR, dataY)),
      m_bbox(std::make_shared<aabb>())
  {
    this->m_affine.matrix() = IDENTITY_MAT4;
    this->reset(size);
    this->updateBBox();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shell::shell(
    size_t              size,
    hyperellipse const &hyperellipse_in)
    : m_shape(std::make_shared<hyperellipse>(hyperellipse_in)),
      m_bbox(std::make_shared<aabb>())
  {
    this->m_affine.matrix() = IDENTITY_MAT4;
    this->reset(size);
    this->updateBBox();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shell::shell(
    size_t         size,
    polynom const &polynom_in)
    : m_shape(std::make_shared<polynom>(polynom_in)),
      m_bbox(std::make_shared<aabb>())
  {
    this->m_affine.matrix() = IDENTITY_MAT4;
    this->reset(size);
    this->updateBBox();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::reset(
    size_t size)
  {
    ENVE_ASSERT(size > 0, "enve::shell::reset(): shell ribs numer must be greater than 0.\n");

    // Resize the contact point, friction and normal vectors
    this->m_ribs.clear();
    this->m_ribs.resize(size);
    this->m_normal.resize(size);
    this->m_pointRib.resize(size);
    this->m_pointMesh.resize(size);
    this->m_friction.resize(size);

    // Locate the disks
    real ribY;
    real shellWidth = this->m_shape->surfaceWidth();
    real shellLower = this->m_shape->surfaceWidthLowerBound();
    real ribWidth   = shellWidth / size;
    for (size_t i = 0; i < size; ++i)
    {
      ribY            = shellLower + ribWidth / 2.0 + i * ribWidth;
      this->m_ribs[i] = rib(
        this->m_shape->surfaceRadius(ribY),
        point(0.0, ribY, 0.0),
        vec3(0.0, 1.0, 0.0),
        ribWidth,
        this->m_shape->surfaceAngle(ribY));
    }
    // Update bounding aabb
    this->updateBBox();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  size_t
  shell::size(void)
    const
  {
    return this->m_ribs.size();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |                                   _
   |    __ _  ___  ___  _ __ ___   ___| |_ _ __ _   _
   |   / _` |/ _ \/ _ \| '_ ` _ \ / _ \ __| '__| | | |
   |  | (_| |  __/ (_) | | | | | |  __/ |_| |  | |_| |
   |   \__, |\___|\___/|_| |_| |_|\___|\__|_|   \__, |
   |   |___/                                    |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceMaxRadius(void)
    const
  {
    return this->m_shape->surfaceMaxRadius();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceMaxWidth(void)
    const
  {
    return this->m_shape->surfaceMaxWidth();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceWidthLowerBound(void)
    const
  {
    return this->m_shape->surfaceWidthLowerBound();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceWidthUpperBound(void)
    const
  {
    return this->m_shape->surfaceWidthUpperBound();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceWidth(void)
    const
  {
    return this->m_shape->surfaceWidth();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::checkWidthBound(
    real y)
    const
  {
    return this->m_shape->checkWidthBound(y);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceRadius(
    real y)
    const
  {
    return this->m_shape->surfaceRadius(y);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceDerivative(
    real y,
    real tolerance)
    const
  {
    return this->m_shape->surfaceDerivative(y, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceAngle(
    real y,
    real tolerance)
    const
  {
    return this->m_shape->surfaceAngle(y, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::ribRadius(
    size_t i)
    const
  {
    return this->m_ribs[i].radius();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point
  shell::ribCenter(
    size_t i)
    const
  {
    return this->m_ribs[i].center();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::ribWidth(
    size_t i)
    const
  {
    return this->m_ribs[i].width();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |    __
   |   / _|_ __ __ _ _ __ ___   ___
   |  | |_| '__/ _` | '_ ` _ \ / _ \
   |  |  _| | | (_| | | | | | |  __/
   |  |_| |_|  \__,_|_| |_| |_|\___|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::translate(
    vec3 const &vector)
  {
    this->m_affine.translate(vector);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  shell::translation(
    void)
    const
  {
    return this->m_affine.translation();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::rotate(
    real        angle,
    vec3 const &axis)
  {
    this->m_affine.rotate(angleaxis(angle, axis));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  mat3
  shell::rotation(
    void)
    const
  {
    return this->m_affine.rotation();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  mat3
  shell::linear(
    void)
    const
  {
    return this->m_affine.linear();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::transform(
    mat4 const &matrix)
  {
    this->m_affine.matrix() = matrix;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::transform(
    affine const &affine_in)
  {
    this->m_affine = affine_in;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  affine const &
  shell::transformation(void)
    const
  {
    return this->m_affine;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  shell::x(void)
    const
  {
    return this->m_affine.linear().col(0);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  shell::y(void)
    const
  {
    return this->m_affine.linear().col(1);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  shell::z(void)
    const
  {
    return this->m_affine.linear().col(2);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::eulerAngles(
    vec3 &angles)
    const
  {
    angles = this->m_affine.linear().eulerAngles(2, 0, 1);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |   _
   |  | |__   _____  __
   |  | '_ \ / _ \ \/ /
   |  | |_) | (_) >  <
   |  |_.__/ \___/_/\_\
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  std::shared_ptr<aabb>
  shell::bbox(void)
    const
  {
    return this->m_bbox;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::updateBBox(void)
  {
    real  radius = this->m_shape->surfaceMaxRadius();
    point origin(this->m_affine.translation());
    point extrema(radius, radius, radius);
    this->m_bbox->min() = origin - extrema;
    this->m_bbox->max() = origin + extrema;
    this->m_bbox->updateMaxMin();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |                   _             _
   |    ___ ___  _ __ | |_ __ _  ___| |_
   |   / __/ _ \| '_ \| __/ _` |/ __| __|
   |  | (_| (_) | | | | || (_| | (__| |_
   |   \___\___/|_| |_|\__\__,_|\___|\__|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::relativeAngles(
    vec3 &angles)
    const
  {
    affine point_affine;
    this->contactPointRibAffine(point_affine);
    mat3 rotation(point_affine.linear().transpose() * this->m_affine.linear());
    angles = rotation.eulerAngles(2, 0, 1);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::relativeAngles(
    size_t i,
    vec3  &angles)
    const
  {
    affine point_affine;
    this->contactPointRibAffine(i, point_affine);
    mat3 rotation(point_affine.linear().transpose() * this->m_affine.linear());
    angles = rotation.eulerAngles(2, 0, 1);
    angles.x() -= this->m_ribs[i].angle();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::relativeAngles(
    std::vector<vec3> &angles)
    const
  {
    for (size_t i = 0; i < this->size(); ++i)
      this->relativeAngles(i, angles[i]);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepthRib(
    real &depth,
    real &depth_dot,
    real  depth_old,
    real  time_step)
    const
  {
    point contact_point;
    this->contactPointRib(contact_point);
    depth = this->m_shape->surfaceMaxRadius() - (this->m_affine.translation() - contact_point).norm();
    if (depth > 0.0)
    {
      depth_dot = (depth - depth_old) / time_step;
    }
    else
    {
      depth     = 0.0;
      depth_dot = 0.0;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepthRib(
    size_t i,
    real  &depth,
    real  &depth_dot,
    real   depth_old,
    real   time_step)
    const
  {
    depth = this->m_ribs[i].radius() - (this->m_affine.translation() + this->m_affine.linear() * this->m_ribs[i].center() - this->m_pointRib[i]).norm();
    if (depth > 0.0)
    {
      depth_dot = (depth - depth_old) / time_step;
    }
    else
    {
      depth     = 0.0;
      depth_dot = 0.0;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepthRib(
    vecN       &depth,
    vecN       &depth_dot,
    vecN const &depth_old,
    real        time_step)
    const
  {
    for (size_t i = 0; i < this->size(); ++i)
    {
      this->contactDepthRib(i, depth[i], depth_dot[i], depth_old[i], time_step);
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepthMesh(
    real &depth,
    real &depth_dot,
    real  depth_old,
    real  time_step)
    const
  {
    point contact_point;
    this->contactPointMesh(contact_point);
    depth = this->m_shape->surfaceMaxRadius() - (this->m_affine.translation() - contact_point).norm();
    if (depth > 0.0)
    {
      depth_dot = (depth - depth_old) / time_step;
    }
    else
    {
      depth     = 0.0;
      depth_dot = 0.0;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepthMesh(
    size_t i,
    real  &depth,
    real  &depth_dot,
    real   depth_old,
    real   time_step)
    const
  {
    depth = this->m_ribs[i].radius() - (this->m_affine.translation() + this->m_affine.linear() * this->m_ribs[i].center() - this->m_pointMesh[i]).norm();
    if (depth > 0.0)
    {
      depth_dot = (depth - depth_old) / time_step;
    }
    else
    {
      depth     = 0.0;
      depth_dot = 0.0;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepthMesh(
    vecN       &depth,
    vecN       &depth_dot,
    vecN const &depth_old,
    real        time_step)
    const
  {
    for (size_t i = 0; i < this->size(); ++i)
    {
      this->contactDepthMesh(i, depth[i], depth_dot[i], depth_old[i], time_step);
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactNormal(
    vec3 &normal)
    const
  {
    normal      = ZEROS_VEC3;
    size_t size = this->size();
    for (size_t i = 0; i < size; ++i)
      normal += this->m_normal[i];
    normal /= size;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactNormal(
    size_t i,
    vec3  &normal)
    const
  {
    normal = this->m_normal[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactNormal(
    std::vector<vec3> &normal)
    const
  {
    normal = this->m_normal;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointRib(
    point &point)
    const
  {
    point       = ZEROS_VEC3;
    size_t size = this->size();
    for (size_t i = 0; i < size; ++i)
      point += this->m_pointRib[i];
    point /= size;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointRib(
    size_t i,
    point &point)
    const
  {
    point = this->m_pointRib[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointRib(
    std::vector<point> &point)
    const
  {
    point = this->m_pointRib;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointMesh(
    point &point)
    const
  {
    point       = ZEROS_VEC3;
    size_t size = this->size();
    for (size_t i = 0; i < size; ++i)
      point += this->m_pointMesh[i];
    point /= size;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointMesh(
    size_t i,
    point &point)
    const
  {
    point = this->m_pointMesh[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointMesh(
    std::vector<point> &point)
    const
  {
    point = this->m_pointMesh;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactFriction(
    real &friction)
    const
  {
    friction = this->m_friction.mean();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactFriction(
    size_t i,
    real  &friction)
    const
  {
    friction = this->m_friction[i];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactFriction(
    vecN &friction)
    const
  {
    friction = this->m_friction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointRibAffine(
    affine &point_affine)
    const
  {
    point point;
    vec3  normal;
    this->contactPointRib(point);
    this->contactNormal(normal);
    vec3 x_vec((this->y().cross(normal)).normalized());
    vec3 y_vec((normal.cross(x_vec)).normalized());
    point_affine.matrix() << x_vec, y_vec, normal, point,
      vec4(0.0, 0.0, 0.0, 1.0).transpose();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointRibAffine(
    size_t  i,
    affine &point_affine)
    const
  {
    vec3 x_vec((this->y().cross(this->m_normal[i])).normalized());
    vec3 y_vec((this->m_normal[i].cross(x_vec)).normalized());
    point_affine.matrix() << x_vec, y_vec, this->m_normal[i], this->m_pointRib[i],
      vec4(0.0, 0.0, 0.0, 1.0).transpose();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointRibAffine(
    std::vector<affine> &point_affine)
    const
  {
    for (size_t i = 0; i < this->size(); ++i)
      this->contactPointRibAffine(i, point_affine[i]);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointMeshAffine(
    affine &point_affine)
    const
  {
    point point;
    vec3  normal;
    this->contactPointMesh(point);
    this->contactNormal(normal);
    vec3 x_vec((this->y().cross(normal)).normalized());
    vec3 y_vec((normal.cross(x_vec)).normalized());
    point_affine.matrix() << x_vec, y_vec, normal, point,
      vec4(0.0, 0.0, 0.0, 1.0).transpose();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointMeshAffine(
    size_t  i,
    affine &point_affine)
    const
  {
    vec3 x_vec((this->y().cross(this->m_normal[i])).normalized());
    vec3 y_vec((this->m_normal[i].cross(x_vec)).normalized());
    point_affine.matrix() << x_vec, y_vec, this->m_normal[i], this->m_pointMesh[i],
      vec4(0.0, 0.0, 0.0, 1.0).transpose();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointMeshAffine(
    std::vector<affine> &point_affine)
    const
  {
    for (size_t i = 0; i < this->size(); ++i)
      this->contactPointMeshAffine(i, point_affine[i]);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::setup(
    ground::mesh const &ground,
    affine const       &affine_in,
    size_t              threshold,
    std::string const   method)
  {
    if (method != "line" && method != "triangle")
    {
      ENVE_ERROR("enve::setup(mesh, affine, threshold, method): invalid enveloping method.\n");
      return false;
    }
    // Set the new reference frame
    this->m_affine = affine_in;
    // Shell Shadow update
    this->updateBBox();
    // Local intersected triangles vector
    triangleground::vecptr triangles;
    ground.intersection(this->m_bbox, triangles);
    // Store triangle vec and shell sizes
    size_t triangles_size = triangles.size();
    size_t ribs_size      = this->size();

    // End setup if there are no intersections
    if (triangles_size < 1)
    {
      std::cout << "enve::setup(mesh, affine, threshold, method): WARNING No mesh detected under the shell.\n";
      return false;
    }
    else if (triangles_size == 1)
    {
      // Perform single triangle intersection all ribs
      for (size_t i = 0; i < ribs_size; ++i)
        this->envelopSingleTriangle(triangles, i);
      return true;
    }
    else
    {
      // Update the intersection
      // Calculate how many ribs to eliminate
      if (triangles_size * ribs_size < threshold)
      {
        // Perform intersection on all ribs
        for (size_t i = 0; i < ribs_size; ++i)
        {
          if (method == "line")
            this->envelopLine(triangles, i);
          else if (method == "triangle")
            this->envelopTriangle(triangles, i);
        }
      }
      else if (triangles_size * ribs_size / 2.0 < threshold && ribs_size % 2 != 0 && ribs_size > 1)
      {
        // Perform intersection on half ribs if odd
        for (size_t i = 0; i < ribs_size; ++i)
        {
          if (method == "line")
            this->envelopLine(triangles, i);
          else if (method == "triangle")
            this->envelopTriangle(triangles, i);
        }
        // Calculate missing information through oversampling
        for (size_t i = 1; i < ribs_size; i += 2)
          this->oversample(i, i - 1, i + 1);
      }
      else if (triangles_size * 3.0 < threshold && ribs_size % 2 != 0 && ribs_size > 3)
      {
        // Perform intersection on central and lateral ribs if odd
        if (method == "line")
        {
          this->envelopLine(triangles, 0);
          this->envelopLine(triangles, (ribs_size - 1) / 2);
          this->envelopLine(triangles, ribs_size - 1);
        }
        else if (method == "triangle")
        {
          this->envelopTriangle(triangles, 0);
          this->envelopTriangle(triangles, (ribs_size - 1) / 2);
          this->envelopTriangle(triangles, ribs_size - 1);
        }
        // Calculate missing information through oversampling
        for (size_t i = 1; i < (ribs_size - 1) / 2; ++i)
          this->oversample(i, 0, (ribs_size - 1) / 2);
        for (size_t i = (ribs_size - 1) / 2 + 1; i < ribs_size - 1; ++i)
          this->oversample(i, (ribs_size - 1) / 2, ribs_size - 1);
      }
      else if (triangles_size * 2.0 < threshold && ribs_size > 1)
      {
        // Perform intersection only on lateral ribs
        if (method == "line")
        {
          this->envelopLine(triangles, 0);
          this->envelopLine(triangles, ribs_size - 1);
        }
        else if (method == "triangle")
        {
          this->envelopTriangle(triangles, 0);
          this->envelopTriangle(triangles, ribs_size - 1);
        }
        // Calculate missing information through oversampling
        for (size_t i = 1; i < ribs_size - 1; ++i)
          this->oversample(i, 0, ribs_size - 1);
      }
      else
      {
        // EMERGENCY METHOD: Perform intersection only on lateral ribs
        this->envelopLine(triangles, 0);
        this->envelopLine(triangles, (ribs_size - 1));
        // Calculate missing information through oversampling
        for (size_t i = 1; i < ribs_size - 1; ++i)
          this->oversample(i, 0, (ribs_size - 1));
      }
      return true;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::setup(
    ground::flat const &ground,
    affine const       &affine_in)
  {
    // Set the new reference frame
    this->m_affine = affine_in;
    // Shell Shadow update
    this->updateBBox();
    // Intersect ribs with local plane
    for (size_t i = 0; i < this->size(); ++i)
      this->envelopPlane(ground, i);
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::print(
    out_stream &os)
    const
  {
    real time_step = 0.001;
    real radius    = this->m_shape->surfaceMaxRadius();

    point pointRib;
    this->contactPointRib(pointRib);
    point pointMesh;
    this->contactPointMesh(pointMesh);
    vec3 normal;
    this->contactNormal(normal);
    real depthRib         = 0.0;
    real depthRib_dot     = 0.0;
    real depthRib_old_dot = 0.0;
    this->contactDepthRib(depthRib, depthRib_dot, depthRib_old_dot, time_step);
    real depthMesh         = 0.0;
    real depthMesh_dot     = 0.0;
    real depthMesh_old_dot = 0.0;
    this->contactDepthMesh(depthMesh, depthMesh_dot, depthMesh_old_dot, time_step);
    real friction = 0.0;
    this->contactFriction(friction);
    vec3 relative_angles;
    this->relativeAngles(relative_angles);
    affine pointRib_affine;
    this->contactPointRibAffine(pointRib_affine);
    affine pointMesh_affine;
    this->contactPointMeshAffine(pointMesh_affine);

    size_t                   size = this->size();
    std::vector<acme::point> pointRib_vec;
    this->contactPointRib(pointRib_vec);
    std::vector<acme::point> pointMesh_vec;
    this->contactPointMesh(pointMesh_vec);
    std::vector<vec3> normal_vec;
    this->contactNormal(normal_vec);
    vecN depthRib_vec(size);
    vecN depthRib_dot_vec(size);
    vecN depthRib_old_vec(size);
    this->contactDepthRib(depthRib_vec, depthRib_dot_vec, depthRib_old_vec, time_step);
    vecN depthMesh_vec(size);
    vecN depthMesh_dot_vec(size);
    vecN depthMesh_old_vec(size);
    this->contactDepthMesh(depthMesh_vec, depthMesh_dot_vec, depthMesh_old_vec, time_step);
    vecN friction_vec(size);
    this->contactFriction(friction_vec);
    std::vector<vec3> relative_angles_vec(size);
    this->relativeAngles(relative_angles_vec);
    std::vector<affine> pointRib_affine_vec(size);
    this->contactPointRibAffine(pointRib_affine_vec);
    std::vector<affine> pointMesh_affine_vec(size);
    this->contactPointMeshAffine(pointMesh_affine_vec);
    vec3 euler_angles;
    this->eulerAngles(euler_angles);

    os << "Rib info" << std::endl;
    for (size_t i = 0; i < relative_angles_vec.size(); ++i)
      os << "Rib " << i << ":" << std::endl
         << "radius = " << this->m_ribs[i].radius() << "m" << std::endl
         << "center = " << this->m_ribs[i].center() << "m" << std::endl;

    os << "CONTACT PARAMETERS" << std::endl
       << "Shell radius" << std::endl
       << "R = " << radius << " m" << std::endl
       << "Camber angle" << std::endl
       << "Γ = " << euler_angles.y() / PI << "pi rad" << std::endl
       << "Rotation angle" << std::endl
       << "ß = " << euler_angles.z() / PI << "pi rad" << std::endl
       << "Yaw angle" << std::endl
       << "α = " << euler_angles.x() / PI << "pi rad" << std::endl
       << "Normal contact point vector of the local track plane (absolute reference frame)" << std::endl
       << "N = " << normal.transpose() << std::endl
       << "Local contact point on mesh (absolute reference frame) (on rib plane)" << std::endl
       << "P = " << pointRib.transpose() << std::endl
       << "Local contact point on mesh (absolute reference frame) (on mesh surface)" << std::endl
       << "P = " << pointMesh.transpose() << std::endl
       << "Shell reference frame" << std::endl
       << this->m_affine.matrix() << std::endl
       << "Local contact point reference frame (on rib plane)" << std::endl
       << pointRib_affine.matrix() << std::endl
       << "Local contact point reference frame (on mesh surface)" << std::endl
       << pointMesh_affine.matrix() << std::endl
       << "Relative camber angle" << std::endl
       << "[Γ ß α]' = " << relative_angles.transpose() / PI << "pi rad" << std::endl
       << "Relative camber angle vector" << std::endl;
    for (size_t i = 0; i < relative_angles_vec.size(); ++i)
      os << "rib " << i << ": [Γ ß α]' = " << relative_angles_vec[i].transpose() / PI << "pi rad" << std::endl;
    os << "Local contact point friction" << std::endl
       << "f = " << friction << std::endl
       << "Local contact point friction vector" << std::endl
       << "f = " << friction_vec.transpose() << std::endl
       << "Local contact depth (on average point) (on rib plane)" << std::endl
       << "d = " << depthRib << " m" << std::endl
       << "Local contact depth time derivative on average point (on rib plane)" << std::endl
       << "d = " << depthRib_dot << " m/s" << std::endl
       << "Local contact depth vector (on rib plane)" << std::endl
       << "d = " << depthRib_vec.transpose() << " m" << std::endl
       << "Local contact depth time derivative vector (on rib plane)" << std::endl
       << "d = " << depthRib_dot_vec.transpose() << " m/s" << std::endl
       << "Local contact depth (on average point) (on mesh surface)" << std::endl
       << "d = " << depthMesh << " m" << std::endl
       << "Local contact depth time derivative on average point (on mesh surface)" << std::endl
       << "d = " << depthMesh_dot << " m/s" << std::endl
       << "Local contact depth vector (on mesh surface)" << std::endl
       << "d = " << depthMesh_vec.transpose() << " m" << std::endl
       << "Local contact depth time derivative vector (on mesh surface)" << std::endl
       << "d = " << depthMesh_dot_vec.transpose() << " m/s" << std::endl
       << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::oversample(
    size_t o,
    size_t a,
    size_t b)
  {
    real y_o  = this->m_ribs[o].center().y();
    real y_a  = this->m_ribs[a].center().y();
    real y_b  = this->m_ribs[b].center().y();
    real y_oa = y_o - y_a;
    real y_ba = y_b - y_a;
    // Oversample contact points on ribs plane
    this->m_pointRib[o] = this->m_pointRib[a] + y_oa * (this->m_pointRib[b] - this->m_pointRib[a]) / y_ba;
    // Oversample contact points on mesh surface
    this->m_pointMesh[o] = this->m_pointMesh[a] + y_oa * (this->m_pointMesh[b] - this->m_pointMesh[a]) / y_ba;
    // Oversample contact normal
    this->m_normal[o] = this->m_normal[a] + y_oa * (this->m_normal[b] - this->m_normal[a]) / y_ba;
    // Oversample contact friction coefficient
    this->m_friction[o] = this->m_friction[a] + y_oa * (this->m_friction[b] - this->m_friction[a]) / y_ba;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::samplingSingleTriangle(
    triangleground::vecptr const &triangles,
    point const                  &origin,
    vec3 const                   &direction,
    point                        &point_out,
    vec3                         &normal,
    real                         &friction)
    const
  {
    ENVE_ASSERT(triangles.size() == 1, "enve::sampling_single_triangle(): triangles vector size is not equal to 1.");
    // Create the sampling line
    if (intersection(line(origin, direction), *triangles[0], point_out, EPSILON_LOW))
    {
      normal   = triangles[0]->normal();
      friction = triangles[0]->friction();
      return true;
    }
    else
    {
      // Flying over the mesh
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::samplingPoint(
    triangleground::vecptr const &triangles,
    point const                  &origin,
    vec3 const                   &direction,
    point                        &point_out,
    vec3                         &normal_out,
    real                         &friction_out)
    const
  {
    point              point_tmp;
    std::vector<point> point_vec;
    std::vector<vec3>  normal_vec;
    std::vector<real>  friction_vec;
    bool               int_bool = false;
    line               line_tmp(origin, direction);
    for (size_t i = 0; i < triangles.size(); ++i)
    {
      if (intersection(line_tmp, *triangles[i], point_tmp, EPSILON_LOW))
      {
        point_vec.push_back(point_tmp);
        normal_vec.push_back(triangles[i]->normal());
        friction_vec.push_back(triangles[i]->friction());
        int_bool = true;
      }
    }
    // Select the highest intersection point
    if (point_vec.size() == 1 && int_bool)
    {
      point_out    = point_vec[0];
      normal_out   = normal_vec[0];
      friction_out = friction_vec[0];
      return true;
    }
    else if (point_vec.size() > 1 && int_bool)
    {
      point_out    = point_vec[0];
      normal_out   = normal_vec[0];
      friction_out = friction_vec[0];
      for (size_t j = 1; j < point_vec.size(); ++j)
      {
        if (point_vec[j].z() > point_out.z())
        {
          point_out    = point_vec[j];
          normal_out   = normal_vec[j];
          friction_out = friction_vec[j];
        }
      }
      return true;
    }
    else if (triangles.size() > 0 && !int_bool)
    {
      // Flying over the mesh
      return false;
    }
    else if (triangles.size() == 0)
    {
      // Out of mesh
      return false;
    }
    else
    {
      ENVE_ERROR("enve::shell::samplingPoint(): not handled condition.");
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::samplingCross(
    triangleground::vecptr const &triangles,
    point const                  &line_origin,
    vec3 const                   &line_direction,
    real                          delta_x,
    real                          delta_y,
    point                        &point_out,
    vec3                         &normal_out,
    real                         &friction_out)
    const
  {
    // Store shell pose and z axis direction
    point frame_origin(this->m_affine.translation());
    mat3  frame_rotation(this->m_affine.linear());
    vec3  delta_x_vec(delta_x, 0.0, 0.0);
    vec3  delta_y_vec(0.0, delta_y, 0.0);
    // Find intersection in the four positions
    std::vector<point> point_vec(4);
    vec3               normal_tmp;
    std::vector<real>  friction_vec(4);
    if (this->samplingPoint(triangles, frame_origin + frame_rotation * (line_origin + delta_x_vec), line_direction, point_vec[0], normal_tmp, friction_vec[0]) && this->samplingPoint(triangles, frame_origin + frame_rotation * (line_origin - delta_x_vec), line_direction, point_vec[1], normal_tmp, friction_vec[1]) && this->samplingPoint(triangles, frame_origin + frame_rotation * (line_origin + delta_y_vec), line_direction, point_vec[2], normal_tmp, friction_vec[2]) && this->samplingPoint(triangles, frame_origin + frame_rotation * (line_origin - delta_y_vec), line_direction, point_vec[3], normal_tmp, friction_vec[3]))
    {
      // Calculate local contact point on the rib
      point_out = (point_vec[0] + point_vec[1] + point_vec[2] + point_vec[3]) / 4.0;
      // Calculate normal of the local track plane
      normal_out = ((point_vec[0] - point_vec[1]).cross(point_vec[2] - point_vec[3])).normalized();
      // Calculate the contact point friction as average of points
      friction_out = (friction_vec[0] + friction_vec[1] + friction_vec[2] + friction_vec[3]) / 4.0;
      return true;
    }
    else
    {
      point_out    = frame_origin + frame_rotation * vec3(0.0, 0.0, -this->m_shape->surfaceMaxRadius());
      normal_out   = frame_origin + frame_rotation * vec3(0.0, 0.0, 1.0);
      friction_out = real(0.0);
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::envelopSingleTriangle(
    triangleground::vecptr const &triangles,
    size_t                        i)
  {
    bool bool1 = this->samplingSingleTriangle(triangles,
                                              this->m_ribs[i].center(), // Line origin
                                              -this->z(),               // Line direction
                                              this->m_pointRib[i],
                                              this->m_normal[i],
                                              this->m_friction[i]);

    bool bool2 = this->projectContactPointOnMesh(triangles, this->m_pointRib[i], this->m_normal[i], i, this->m_pointMesh[i]);

    return bool1 && bool2;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::envelopLine(
    triangleground::vecptr const &triangles,
    size_t                        i)
  {
    bool bool1 = this->samplingCross(triangles,
                                     this->m_ribs[i].center(),       // Line origin
                                     -this->z(),                     // Line direction
                                     0.3 * this->m_ribs[i].radius(), // Delta x
                                     this->m_ribs[i].width() / 2.0,  // Delta y
                                     this->m_pointRib[i],
                                     this->m_normal[i],
                                     this->m_friction[i]);

    bool bool2 = this->projectContactPointOnMesh(triangles, this->m_pointRib[i], this->m_normal[i], i, this->m_pointMesh[i]);

    return bool1 && bool2;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::envelopTriangle(
    triangleground::vecptr const &triangles,
    size_t                        i)
  {
    point origin(this->m_affine.translation());
    mat3  rotation(this->m_affine.linear());
    // Find intersections
    segment segment_tmp;
    real    segment_tmp_length;
    point   pointRib_tmp         = point::Constant(0.0);
    point   pointMesh_tmp        = point::Constant(0.0);
    vec3    normal_tmp           = ZEROS_VEC3;
    real    friction_tmp         = 0.0;
    real    segment_length_total = 0.0;
    bool    int_bool             = false;
    rib     rib_ground(this->m_ribs[i].radius(), origin + rotation * this->m_ribs[i].center(), rotation * this->m_ribs[i].normal());
    for (size_t i = 0; i < triangles.size(); ++i)
    {
      if (intersection(*triangles[i], rib_ground, segment_tmp, EPSILON_LOW))
      {
        segment_tmp_length = segment_tmp.length();
        segment_length_total += segment_tmp_length;
        pointRib_tmp += segment_tmp_length * segment_tmp.centroid();
        normal_tmp += segment_tmp_length * triangles[i]->normal();
        friction_tmp += segment_tmp_length * triangles[i]->friction();
        int_bool = true;
      }
    }
    if (int_bool)
    {
      this->m_pointRib[i] = pointRib_tmp / segment_length_total;
      this->m_normal[i]   = normal_tmp / segment_length_total;
      this->m_friction[i] = friction_tmp / segment_length_total;
      this->projectContactPointOnMesh(triangles, this->m_pointRib[i], this->m_normal[i], i, this->m_pointMesh[i]);
      return true;
    }
    else
    {
      this->m_pointRib[i]  = origin + rotation * (this->m_ribs[i].center() - point(0.0, 0.0, this->m_ribs[i].radius()));
      this->m_normal[i]    = rotation * UNITZ_VEC3;
      this->m_friction[i]  = 0.0;
      this->m_pointMesh[i] = this->m_pointRib[i];
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::envelopPlane(
    ground::flat const &ground,
    size_t              i)
  {
    point origin(this->m_affine.translation());
    mat3  rotation(this->m_affine.linear());
    // Find intersections
    segment segment_tmp;
    disk    rib_ground(this->m_ribs[i].radius(), origin + rotation * this->m_ribs[i].center(), rotation * this->m_ribs[i].normal());
    if (intersection(ground, rib_ground, segment_tmp, EPSILON_LOW))
    {
      this->m_pointRib[i] = segment_tmp.centroid();
      this->m_normal[i]   = ground.normal();
      this->m_friction[i] = ground.friction();
      this->projectContactPointOnFlat(ground, this->m_pointRib[i], this->m_normal[i], i, this->m_pointMesh[i]);
      return true;
    }
    else
    {
      this->m_pointRib[i]  = origin + rotation * (this->m_ribs[i].center() - point(0.0, 0.0, this->m_ribs[i].radius()));
      this->m_normal[i]    = rotation * UNITZ_VEC3;
      this->m_friction[i]  = real(0.0);
      this->m_pointMesh[i] = this->m_pointRib[i];
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::projectContactPointOnFlat(
    ground::flat const &ground,
    point const        &point_rib,
    vec3 const         &direction,
    size_t              i,
    point              &point_out)
    const
  {
    point shell_origin = this->m_affine.translation();
    point line_origin  = shell_origin - (shell_origin - point_rib).normalized() * this->m_ribs[i].radius();
    return intersection(line(line_origin, direction), ground, point_out, EPSILON_LOW);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::projectContactPointOnMesh(
    triangleground::vecptr const &triangles,
    point const                  &point_rib,
    vec3 const                   &direction,
    size_t                        i,
    point                        &point_out)
    const
  {
    point shell_origin = this->m_affine.translation();
    point line_origin  = shell_origin - (shell_origin - point_rib).normalized() * this->m_ribs[i].radius();
    return this->samplingPoint(triangles, line_origin, direction, point_out, THROWAWAY_NORMAL, THROWAWAY_FRICTION);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_shell.cc
///