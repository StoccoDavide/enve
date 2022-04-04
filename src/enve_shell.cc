/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *)
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
    real   l_y
  )
    : m_shape(std::make_shared<shape>(r_x, m_x, r_y, m_y, l_y)),
      m_aabb(std::make_shared<aabb>())
  {
    this->m_affine.matrix() = IDENTITY_MAT4;
    this->resize(size);
    this->updateBBox();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shell::shell(
    size_t       size,
    shape const &shape_in
  )
    : m_shape(std::make_shared<shape>(shape_in)),
      m_aabb(std::make_shared<aabb>())
  {
    this->m_affine.matrix() = IDENTITY_MAT4;
    this->resize(size);
    this->updateBBox();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::resize(
    size_t size
  )
  {
    ENVE_ASSERT(size > 0, "enve::shell::resize(): shell ribs numer must be greater than 0.\n");

    // Resize the contact point, friction and normal vectors
    this->m_ribs.clear();
    this->m_out.clear();

    this->m_ribs.resize(size);
    this->m_out.resize(size);

    // Locate the disks
    real shellWidth = this->m_shape->surfaceWidth();
    real ribW = 2*shellWidth / size;
    real ribR, ribA;
    real ribY = -shellWidth - ribW / 2.0;
    for (size_t i = 0; i < size; ++i)
    {
      ribY += ribW;
      ribR  = this->m_shape->surfaceRadius(ribY);
      ribA  = this->m_shape->surfaceAngle(ribY);
      ENVE_ASSERT(ribR > 0, "enve::shell::resize(size): Negative rib radius.\n" );
      ENVE_ASSERT(ribR == ribR, "enve::shell::resize(size): NaN rib radius.\n" );
      ENVE_ASSERT(ribA == ribA, "enve::shell::resize(size): NaN rib angle.\n" );
      this->m_ribs[i] = rib(ribR, point(0.0, ribY, 0.0), vec3(0.0, 1.0, 0.0), ribW, ribA);
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
   |       _
   |   ___| |__   __ _ _ __   ___
   |  / __| '_ \ / _` | '_ \ / _ \
   |  \__ \ | | | (_| | |_) |  __/
   |  |___/_| |_|\__,_| .__/ \___|
   |                  |_|
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
  shell::surfaceWidth(void)
    const
  {
    return this->m_shape->surfaceWidth();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::checkWidthBound(
    real y
  )
    const
  {
    return this->m_shape->checkWidthBound(y);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceRadius(
    real y
  )
    const
  {
    return this->m_shape->surfaceRadius(y);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceDerivative(
    real y,
    real tolerance
  )
    const
  {
    return this->m_shape->surfaceDerivative(y, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::surfaceAngle(
    real y,
    real tolerance
  )
    const
  {
    return this->m_shape->surfaceAngle(y, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::ribRadius(
    size_t i
  )
    const
  {
    return this->m_ribs[i].radius();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  point
  shell::ribCenter(
    size_t i
  )
    const
  {
    return this->m_ribs[i].center();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::ribWidth(
    size_t i
  )
    const
  {
    return this->m_ribs[i].width();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real
  shell::ribAngle(
    size_t i
  )
    const
  {
    return this->m_ribs[i].angle();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |         __  __ _            
   |   __ _ / _|/ _(_)_ __   ___ 
   |  / _` | |_| |_| | '_ \ / _ \
   | | (_| |  _|  _| | | | |  __/
   |  \__,_|_| |_| |_|_| |_|\___|
   |                             
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::translate(
    vec3 const &vector
  )
  {
    this->m_affine.translate(vector);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  vec3
  shell::translation(void)
    const
  {
    return this->m_affine.translation();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::rotate(
    real        angle,
    vec3 const &axis
  )
  {
    this->m_affine.rotate(angleaxis(angle, axis));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  mat3
  shell::rotation(void)
    const
  {
    return this->m_affine.rotation();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  mat3
  shell::linear(void)
    const
  {
    return this->m_affine.linear();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::transform(
    mat4 const &affine_in
  )
  {
    this->checkTransformation(affine_in);
    this->m_affine.matrix() = affine_in;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::transform(
    affine const &affine_in
  )
  {
    this->checkTransformation(affine_in);
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

  bool
  shell::checkTransformation(
    mat4 const &affine_in
  )
    const
  {
    // Check if determinant is one
    if (std::abs(affine_in.determinant() - 1.0) < EPSILON_LOW)
      return true;
    else
      return false;    
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::checkTransformation(
    affine const &affine_in
  )
    const
  {
    return this->checkTransformation(affine_in.matrix());
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
    vec3 &angles
  )
    const
  {
    angles = this->m_affine.linear().eulerAngles(2, 0, 1);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |               _     _     
   |    __ _  __ _| |__ | |__  
   |   / _` |/ _` | '_ \| '_ \ 
   |  | (_| | (_| | |_) | |_) |
   |   \__,_|\__,_|_.__/|_.__/ 
   |                           
  \*/
  
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
  std::shared_ptr<aabb>
  shell::BBox(void)
    const
  {
    return this->m_aabb;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::updateBBox(void)
  {
    real  radius = this->m_shape->surfaceMaxRadius();
    point origin(this->m_affine.translation());
    point extrema(radius, radius, radius);
    this->m_aabb->min() = origin - extrema;
    this->m_aabb->max() = origin + extrema;
    this->m_aabb->updateMaxMin();
  }
  
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |            _               
   |   ___  ___| |_ _   _ _ __  
   |  / __|/ _ \ __| | | | '_ \ 
   |  \__ \  __/ |_| |_| | |_) |
   |  |___/\___|\__|\__,_| .__/ 
   |                     |_|    
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::setup(
    ground::mesh const &ground,
    affine       const &affine_in,
    std::string  const  method
  )
  {
    // Set the new reference frame
    if (this->checkTransformation(affine_in))
    {
      this->transform(affine_in);
    }
    else
    {
      ENVE_ERROR( "enve::shell::setup(ground::mesh, ... ): Not an othonormal and right-handed affine transformation matrix.\n");
      return false;
    }
    // Shell Shadow update
    this->updateBBox();
    // Local intersected triangles vector
    triangleground::vecptr localGround;
    ground.intersection(this->m_aabb, localGround);

    // End setup if there are no intersections
    if (localGround.size() < 1)
    {
      // std::cout << "enve::setup(mesh, affine, threshold, method): WARNING No mesh detected under the shell.\n";
      for (size_t i = 0; i < this->size(); ++i)
        this->m_ribs[i].envelop(affine_in, this->m_out[i]);
      return false;
    }
    else
    {
      // Perform intersection on all ribs
      bool out = false;
      // Find if at least one rib intersect the ground surface
      for (size_t i = 0; i < this->size(); ++i)
        out = this->m_ribs[i].envelop(localGround, affine_in, method, this->m_out[i]) || out;
      return out;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::setup(
    ground::flat const &ground,
    affine       const &affine_in,
    std::string  const  method
  )
  {
    // Set the new reference frame
    if (this->checkTransformation(affine_in))
    {
      this->transform(affine_in);
    }
    else
    {
      ENVE_ERROR( "enve::shell::setup(ground::flat, ... ): Not an othonormal and right-handed affine transformation matrix.\n");
      return false;
    }
    // Shell Shadow update
    this->updateBBox();

    // Perform intersection on all ribs
    for (size_t i = 0; i < this->size(); ++i)
      this->m_ribs[i].envelop(ground, affine_in, method, this->m_out[i]);
    return true;
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
  shell::contactPoint(
    point &point
  )
    const
  {
    point           = ZEROS_VEC3;
    size_t size     = this->size(); 
    real volume_sum = 0.0;
    this->contactVolume(volume_sum);
    if (volume_sum < EPSILON_HIGH) {
      for (size_t i = 0; i < size; ++i)
        point += this->m_out[i].point;
      point /= size;
    } else {
      for (size_t i = 0; i < size; ++i)
        point += this->m_out[i].point*this->m_out[i].volume;
      point /= volume_sum;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPoint(
    size_t i,
    point &point
  )
    const
  {
    point = this->m_out[i].point;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPoint(
    std::vector<point> &point
  )
    const
  {
    size_t size = this->size(); 
    point.resize(size);
    for (size_t i = 0; i < size; ++i)
      point[i] = this->m_out[i].point;  
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactNormal(
    vec3 &normal
  )
    const
  {
    normal          = ZEROS_VEC3;
    size_t size     = this->size(); 
    real volume_sum = 0.0;
    this->contactVolume(volume_sum);
    if (volume_sum < EPSILON_HIGH) {
      for (size_t i = 0; i < size; ++i)
        normal += this->m_out[i].normal;
      normal /= size;
      normal.normalize();
    } else {
      for (size_t i = 0; i < size; ++i)
        normal += this->m_out[i].normal*this->m_out[i].volume;
      normal /= volume_sum;
      normal.normalize();
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactNormal(
    size_t i,
    vec3  &normal
  )
    const
  {
    normal = this->m_out[i].normal;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactNormal(
    std::vector<vec3> &normal
  )
    const
  {
    size_t size = this->size(); 
    normal.resize(size);
    for (size_t i = 0; i < size; ++i)
      normal[i] = this->m_out[i].normal;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactFriction(
    real &friction
  )
    const
  {
    friction        = 0.0;
    size_t size     = this->size(); 
    real volume_sum = 0.0;
    this->contactVolume(volume_sum);
    if (volume_sum < EPSILON_HIGH) {
      for (size_t i = 0; i < size; ++i)
        friction += this->m_out[i].friction;
      friction /= size;
    } else {
      for (size_t i = 0; i < size; ++i)
        friction += this->m_out[i].friction*this->m_out[i].volume;
      friction /= volume_sum;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactFriction(
    size_t i,
    real  &friction)
    const
  {
    friction = this->m_out[i].friction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactFriction(
    std::vector<real> &friction)
    const
  {
    size_t size = this->size(); 
    friction.resize(size);
    for (size_t i = 0; i < size; ++i)
      friction[i] = this->m_out[i].friction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepth(
    real &depth
  )
    const
  {
    depth           = 0.0;
    size_t size     = this->size(); 
    real volume_sum = 0.0;
    this->contactVolume(volume_sum);
    if (volume_sum < EPSILON_HIGH) {
      depth = volume_sum / size;
    } else {
      for (size_t i = 0; i < size; ++i)
        depth += this->m_out[i].depth*this->m_out[i].volume;
      depth /= volume_sum;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepth(
    size_t i,
    real  &depth
  )
    const
  {
    depth = this->m_out[i].depth;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepth(
    std::vector<real> &depth
  )
    const
  {
    size_t size = this->size(); 
    depth.resize(size);
    for (size_t i = 0; i < size; ++i)
      depth[i] = this->m_out[i].depth;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactArea(
    real &area
  )
    const
  {
    area = 0.0;
    for (size_t i = 0; i < this->size(); ++i)
        area += this->m_out[i].friction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactArea(
    size_t i,
    real  &area)
    const
  {
    area = this->m_out[i].area;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactArea(
    std::vector<real> &area)
    const
  {
    size_t size = this->size(); 
    area.resize(size);
    for (size_t i = 0; i < size; ++i)
      area[i] = this->m_out[i].area;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactVolume(
    real &volume
  )
    const
  {
    volume = 0.0;
    for (size_t i = 0; i < this->size(); ++i)
        volume += this->m_out[i].volume;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactVolume(
    size_t i,
    real  &volume)
    const
  {
    volume = this->m_out[i].volume;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactVolume(
    std::vector<real> &volume)
    const
  {
    size_t size = this->size(); 
    volume.resize(size);
    for (size_t i = 0; i < size; ++i)
      volume[i] = this->m_out[i].volume;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointAffine(
    affine &point_affine)
    const
  {
    point point;
    vec3  normal;
    this->contactPoint(point);
    this->contactNormal(normal);
    vec3 x_vec((this->y().cross(normal)).normalized());
    vec3 y_vec((normal.cross(x_vec)).normalized());
    point_affine.matrix() << x_vec, y_vec, normal, point,
      vec4(0.0, 0.0, 0.0, 1.0).transpose();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointAffine(
    size_t  i,
    affine &point_affine)
    const
  {
    vec3 x_vec((this->y().cross(this->m_out[i].normal)).normalized());
    vec3 y_vec((this->m_out[i].normal.cross(x_vec)).normalized());
    point_affine.matrix() << x_vec, y_vec, this->m_out[i].normal, this->m_out[i].point,
      vec4(0.0, 0.0, 0.0, 1.0).transpose();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointAffine(
    std::vector<affine> &point_affine)
    const
  {
    for (size_t i = 0; i < this->size(); ++i)
      this->contactPointAffine(i, point_affine[i]);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::relativeAngles(
    vec3 &angles
  )
    const
  {
    affine point_affine;
    this->contactPointAffine(point_affine);
    mat3 rotation(point_affine.linear().transpose() * this->m_affine.linear());
    angles = rotation.eulerAngles(2, 0, 1);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::relativeAngles(
    size_t i,
    vec3  &angles
  )
    const
  {
    affine point_affine;
    this->contactPointAffine(i, point_affine);
    mat3 rotation(point_affine.linear().transpose() * this->m_affine.linear());
    angles = rotation.eulerAngles(2, 0, 1);
    angles.x() -= this->m_ribs[i].angle();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::relativeAngles(
    std::vector<vec3> &angles
  )
    const
  {
    for (size_t i = 0; i < this->size(); ++i)
      this->relativeAngles(i, angles[i]);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::print(
    out_stream &os)
    const
  {
    point point;
    this->contactPoint(point);
    vec3 normal;
    this->contactNormal(normal);
    real friction = 0.0;
    this->contactFriction(friction);
    real depth = 0.0;
    this->contactDepth(depth);
    real area = 0.0;
    this->contactArea(area);
    real volume = 0.0;
    this->contactVolume(volume);
    vec3 relative_angles;
    this->relativeAngles(relative_angles);
    affine point_affine;
    this->contactPointAffine(point_affine);

    size_t size = this->size();
    std::vector<acme::point> point_vec;
    this->contactPoint(point_vec);
    std::vector<vec3> normal_vec;
    this->contactNormal(normal_vec);
    std::vector<real> friction_vec(size);
    this->contactFriction(friction_vec);
    std::vector<real> depth_vec(size);
    this->contactDepth(depth_vec);
    std::vector<real> area_vec(size);
    this->contactArea(area_vec);
    std::vector<real> volume_vec(size);
    this->contactVolume(volume_vec);
    std::vector<affine> point_affine_vec(size);
    this->contactPointAffine(point_affine_vec);
    std::vector<vec3> relative_angles_vec(size);
    this->relativeAngles(relative_angles_vec);
    vec3 euler_angles;
    this->eulerAngles(euler_angles);

    os << " ------------ SHELL PRINT ------------" << std::endl
    << std::endl;
    this->m_shape->print(os);

    os << "Ribs info:" << std::endl;
    for (size_t i = 0; i < relative_angles_vec.size(); ++i)
      os << "Rib " << i << " : C = " << this->m_ribs[i].center()
                   << "        R = " << this->m_ribs[i].radius() << " m" << std::endl
                   << "        A = " << this->m_ribs[i].angle() << " rad" << std::endl;
                   
    os << "Contact parameters:" << std::endl
       << "Shell maximum radius" << std::endl
       << "R = " << this->m_shape->surfaceMaxRadius() << " m" << std::endl
       << "Camber angle" << std::endl
       << "Γ = " << euler_angles.y() / PI << "pi rad" << std::endl
       << "Rotation angle" << std::endl
       << "ß = " << euler_angles.z() / PI << "pi rad" << std::endl
       << "Yaw angle" << std::endl
       << "α = " << euler_angles.x() / PI << "pi rad" << std::endl
       << "Contact point (absolute reference frame)" << std::endl
       << "P = " << point.transpose() << std::endl
       << "Contact point (absolute reference frame)" << std::endl;
    for (size_t i = 0; i < point_vec.size(); ++i)
      os << "Rib " << i << " - P = " << point_vec[i].transpose() << " m" << std::endl;
    os << "Contact normal (absolute reference frame)" << std::endl
       << "N = " << normal.transpose() << std::endl
       << "Contact normal vector (absolute reference frame)" << std::endl;
    for (size_t i = 0; i < normal_vec.size(); ++i)
      os << "Rib " << i << " - N = " << normal_vec[i].transpose() << std::endl;
    os << "Contact point friction" << std::endl
       << "f = " << friction << std::endl
       << "Contact point friction vector" << std::endl;
    for (size_t i = 0; i < friction_vec.size(); ++i)
      os << "Rib " << i << " - f = " << friction_vec[i] << std::endl;
    os << "Contact depth (on average point)" << std::endl
       << "d = " << depth << " m" << std::endl
       << "Contact depth vector" << std::endl;
    for (size_t i = 0; i < depth_vec.size(); ++i)
      os << "Rib " << i << " - d = " << depth_vec[i] << " m" << std::endl;
    os << "Contact area (total)" << std::endl
       << "A = " << area << " m^2" << std::endl
       << "Contact area vector" << std::endl;
    for (size_t i = 0; i < area_vec.size(); ++i)
      os << "Rib " << i << " - A = " << area_vec[i] << " m^2" << std::endl;
    os << "Contact volume (total)" << std::endl
       << "V = " << volume << " m^3" << std::endl
       << "Contact volume vector" << std::endl;
    for (size_t i = 0; i < volume_vec.size(); ++i)
      os << "Rib " << i << " - V = " << volume_vec[i] << " m^3" << std::endl;
    os << "Shell reference frame" << std::endl
       << this->m_affine.matrix() << std::endl
       << "Local contact point reference frame" << std::endl
       << point_affine.matrix() << std::endl
       << "Relative pose angles" << std::endl
       << "[Γ ß α]' = " << relative_angles.transpose() / PI << "pi rad" << std::endl
       << "Ribs relative pose angles" << std::endl;
    for (size_t i = 0; i < relative_angles_vec.size(); ++i)
      os << "Rib " << i << " - [Γ ß α]' = " << relative_angles_vec[i].transpose() / PI << "pi rad" << std::endl;
    os << std::endl;
    
    os << " ------------     END     ------------" << std::endl
       << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_shell.cc
///