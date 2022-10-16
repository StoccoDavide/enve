/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * This file is part of the ENVE project.                              *
 *                                                                     *
 * Copyright (c) 2022, Davide Stocco. All rights reserved.             *
 *                                                                     *
 * The ENVE project can not be copied and/or distributed without       *
 * the express permission of Davide Stocco.                            *
 *                                                                     *
 *    Davide Stocco                                                    *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: davide.stocco@unitn.it                                   *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: shell.cc
///

#include "enve.hh"

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

  shell::shell(
    size_t size,
    real   Rx,
    real   Mx,
    real   Ry,
    real   My,
    real   Ly
  )
    : m_shape(std::make_shared<shape>(Rx, Mx, Ry, My, Ly)),
      m_aabb(std::make_shared<aabb>())
  {
    this->m_affine.matrix() = IDENTITY_MAT4;
    this->resize(size);
    this->updateBBox();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  shell::shell(
    size_t         size,
    shape  const & shape_obj
  )
    : m_shape(std::make_shared<shape>(shape_obj)),
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
    #define CMD "enve::shell::resize(...): "

    ENVE_ASSERT(size > size_t(0),
      CMD "negative ribs number detected.");

    // Resize the contact point, friction and normal vectors
    this->m_ribs.clear(); this->m_ribs.reserve(20);
    this->m_out.clear();  this->m_out.resize(size);

    if (!this->m_candidates.empty())
    {
      for (size_t i = 0; i < size; ++i)
      {
        if (!this->m_candidates[i].empty())
          {this->m_candidates[i].clear();}
      }
      this->m_candidates.clear();
    }

    this->m_candidates.resize(size);
    for (size_t i = 0; i < size; ++i)
      {this->m_candidates[i].reserve(200);}

    // Locate the disks
    real shellWidth = this->m_shape->surfaceWidth();
    real ribW = real(2.0) * shellWidth / size;
    real ribR, ribA;
    real ribY = -shellWidth - ribW / real(2.0);
    for (size_t i = 0; i < size; ++i)
    {
      ribY += ribW;
      ribR  = this->m_shape->surfaceRadius(ribY);
      ribA  = this->m_shape->surfaceAngle(ribY);
      ENVE_ASSERT(ribR > size_t(0),
        CMD "negative rib radius detected.");
      ENVE_ASSERT(ribR == ribR,
        CMD "NaN rib radius detected.");
      ENVE_ASSERT(ribA == ribA,
        CMD "NaN rib angle detected.");
      this->m_ribs.push_back(rib(i, ribR, ribY, ribW, ribA));
    }
    // Update bounding aabb
    this->updateBBox();
  
    #undef CMD
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
    vec3 const & vector
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
    real         angle,
    vec3 const & axis
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
    affine const & pose
  )
  {
    this->checkTransformation(pose);
    this->m_affine = pose;
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
    mat4 const & pose,
    real         tolerance
  )
    const
  {
    if (std::abs(pose.determinant() - real(1.0)) < tolerance)
      {return true;}
    else
      {return false;}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::checkTransformation(
    affine const & pose,
    real           /*tolerance*/
  )
    const
  {
    return this->checkTransformation(pose.matrix());
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
    vec3 & angles
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
    ground::mesh const & ground,
    affine       const & pose,
    std::string  const   method
  )
  {
    #define CMD "enve::shell::setup(...): "

    // Set the new reference frame
    this->transform(pose);
    this->updateBBox();

    // Local intersected triangles vector
    triangleground::vecptr local_ground;
    local_ground.reserve(200);
    ground.intersection(this->m_aabb, local_ground);

    // End setup if there are no intersections
    if (local_ground.size() < size_t(1))
    {
      for (size_t i = 0; i < this->size(); ++i)
        {this->m_ribs[i].envelop(pose, this->m_out[i]);}
      return false;
    }
    else
    {
      // Calculate ribs candidates to speed up calculations
      if (method == "geometric")
        {this->updateRibsCandidates(local_ground);}

      // Perform intersection on all ribs
      bool out = false;
      for (size_t i = 0; i < this->size(); ++i)
        {out = this->m_ribs[i].envelop(this->m_candidates[i], pose, method, this->m_out[i]) || out;}
      return out;
    }

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  shell::setup(
    ground::flat const & ground,
    affine       const & pose,
    std::string  const   method
  )
  {
    #define CMD "enve::shell::setup(...): "

    // Set the new reference frame
    this->transform(pose);
    this->updateBBox();

    // Perform intersection on all ribs
    bool out = false;
    for (size_t i = 0; i < this->size(); ++i)
      {out = this->m_ribs[i].envelop(ground, pose, method, this->m_out[i]);}
    return out;

    #undef CMD
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
    point & point
  )
    const
  {
    point           = (ZEROS_VEC3);
    size_t size     = this->size(); 
    real volume_sum = 0.0;
    this->contactVolume(volume_sum);
    if (volume_sum < EPSILON_HIGH)
    {
      for (size_t i = 0; i < size; ++i)
        {point += this->m_out[i].point;}
      point /= size;
    }
    else
    {
      for (size_t i = 0; i < size; ++i)
        {point += this->m_out[i].point*this->m_out[i].volume;}
      point /= volume_sum;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPoint(
    size_t   i,
    point  & point
  )
    const
  {
    point = this->m_out[i].point;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPoint(
    std::vector<point> & point
  )
    const
  {
    size_t size = this->size(); 
    point.resize(size);
    for (size_t i = 0; i < size; ++i)
      {point[i] = this->m_out[i].point;  }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactNormal(
    vec3 & normal
  )
    const
  {
    normal = ZEROS_VEC3;
    size_t size = this->size(); 
    real volume;
    this->contactVolume(volume);
    if (volume < EPSILON_HIGH)
    {
      for (size_t i = 0; i < size; ++i)
        {normal += this->m_out[i].normal;}
      normal /= size;
      normal.normalize();
    }
    else
    {
      for (size_t i = 0; i < size; ++i)
        {normal += this->m_out[i].normal*this->m_out[i].volume;}
      normal /= volume;
      normal.normalize();
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactNormal(
    size_t   i,
    vec3   & normal
  )
    const
  {
    normal = this->m_out[i].normal;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactNormal(
    std::vector<vec3> & normal
  )
    const
  {
    size_t size = this->size(); 
    normal.resize(size);
    for (size_t i = 0; i < size; ++i)
      {normal[i] = this->m_out[i].normal;}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactFriction(
    real & friction
  )
    const
  {
    friction        = 0.0;
    size_t size     = this->size(); 
    real volume_sum = 0.0;
    this->contactVolume(volume_sum);
    if (volume_sum < EPSILON_HIGH)
    {
      for (size_t i = 0; i < size; ++i)
        {friction += this->m_out[i].friction;}
      friction /= size;
    }
    else
    {
      for (size_t i = 0; i < size; ++i)
        {friction += this->m_out[i].friction*this->m_out[i].volume;}
      friction /= volume_sum;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactFriction(
    size_t   i,
    real   & friction
  )
    const
  {
    friction = this->m_out[i].friction;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactFriction(
    std::vector<real> & friction
  )
    const
  {
    size_t size = this->size(); 
    friction.resize(size);
    for (size_t i = 0; i < size; ++i)
      {friction[i] = this->m_out[i].friction;}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepth(
    real & depth
  )
    const
  {
    depth           = 0.0;
    size_t size     = this->size(); 
    real volume_sum = 0.0;
    this->contactVolume(volume_sum);
    if (volume_sum < EPSILON_HIGH)
    {
      depth = volume_sum / size;
    }
    else
    {
      for (size_t i = 0; i < size; ++i)
        {depth += this->m_out[i].depth*this->m_out[i].volume;}
      depth /= volume_sum;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepth(
    size_t   i,
    real   & depth
  )
    const
  {
    depth = this->m_out[i].depth;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactDepth(
    std::vector<real> & depth
  )
    const
  {
    size_t size = this->size(); 
    depth.resize(size);
    for (size_t i = 0; i < size; ++i)
      {depth[i] = this->m_out[i].depth;}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactArea(
    real & area
  )
    const
  {
    area = 0.0;
    for (size_t i = 0; i < this->size(); ++i)
      {area += this->m_out[i].friction;}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactArea(
    size_t   i,
    real   & area
  )
    const
  {
    area = this->m_out[i].area;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactArea(
    std::vector<real> & area
  )
    const
  {
    size_t size = this->size(); 
    area.resize(size);
    for (size_t i = 0; i < size; ++i)
      {area[i] = this->m_out[i].area;}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactVolume(
    real & volume
  )
    const
  {
    volume = 0.0;
    for (size_t i = 0; i < this->size(); ++i)
      {volume += this->m_out[i].volume;}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactVolume(
    size_t   i,
    real   & volume
  )
    const
  {
    volume = this->m_out[i].volume;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactVolume(
    std::vector<real> & volume
  )
    const
  {
    size_t size = this->size(); 
    volume.resize(size);
    for (size_t i = 0; i < size; ++i)
      {volume[i] = this->m_out[i].volume;}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointAffine(
    affine & pose
  )
    const
  {
    point point;
    vec3  normal;
    this->contactPoint(point);
    this->contactNormal(normal);
    vec3 x_vec((this->y().cross(normal)).normalized());
    vec3 y_vec((normal.cross(x_vec)).normalized());
    pose.matrix()
      << x_vec, y_vec, normal, point,
         vec4(0.0, 0.0, 0.0, 1.0).transpose();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointAffine(
    size_t   i,
    affine & pose
  )
    const
  {
    vec3 x_vec((this->y().cross(this->m_out[i].normal)).normalized());
    vec3 y_vec((this->m_out[i].normal.cross(x_vec)).normalized());
    pose.matrix()
      << x_vec, y_vec, this->m_out[i].normal, this->m_out[i].point,
         vec4(0.0, 0.0, 0.0, 1.0).transpose();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::contactPointAffine(
    std::vector<affine> & pose
  )
    const
  {
    for (size_t i = 0; i < this->size(); ++i)
      {this->contactPointAffine(i, pose[i]);}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::relativeAngles(
    vec3 & angles
  )
    const
  {
    affine pose;
    this->contactPointAffine(pose);
    mat3 rotation(pose.linear().transpose() * this->m_affine.linear());
    angles = rotation.eulerAngles(2, 0, 1);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::relativeAngles(
    size_t   i,
    vec3   & angles
  )
    const
  {
    affine pose;
    this->contactPointAffine(i, pose);
    mat3 rotation(pose.linear().transpose() * this->m_affine.linear());
    angles = rotation.eulerAngles(2, 0, 1);
    angles.x() -= this->m_ribs[i].angle();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::relativeAngles(
    std::vector<vec3> & angles
  )
    const
  {
    for (size_t i = 0; i < this->size(); ++i)
      {this->relativeAngles(i, angles[i]);}
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::print(
    out_stream & os
  )
    const
  {
    point cpoint;
    this->contactPoint(cpoint);
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
    affine pose;
    this->contactPointAffine(pose);

    size_t size = this->size();
    std::vector<point> point_vec;
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
    std::vector<affine> pose_vec(size);
    this->contactPointAffine(pose_vec);
    std::vector<vec3> relative_angles_vec(size);
    this->relativeAngles(relative_angles_vec);
    vec3 euler_angles;
    this->eulerAngles(euler_angles);

    os << " ------------ SHELL PRINT ------------" << std::endl
    << std::endl;
    this->m_shape->print(os);

    os << "Ribs info:" << std::endl;
    for (size_t i = 0; i < relative_angles_vec.size(); ++i)
    {
      os << "Rib " << i << " : C = " << this->m_ribs[i].center()
                   << "        R = " << this->m_ribs[i].radius() << " m" << std::endl
                   << "        W = " << this->m_ribs[i].width()  << " m" << std::endl
                   << "        A = " << this->m_ribs[i].angle()  << " rad" << std::endl;
    }
                   
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
       << "P = " << cpoint.transpose() << std::endl
       << "Contact point (absolute reference frame)" << std::endl;
    for (size_t i = 0; i < point_vec.size(); ++i)
      {os << "Rib " << i << " - P = " << point_vec[i].transpose() << " m" << std::endl;}
    os << "Contact normal (absolute reference frame)" << std::endl
       << "N = " << normal.transpose() << std::endl
       << "Contact normal vector (absolute reference frame)" << std::endl;
    for (size_t i = 0; i < normal_vec.size(); ++i)
      {os << "Rib " << i << " - N = " << normal_vec[i].transpose() << std::endl;}
    os << "Contact point friction" << std::endl
       << "f = " << friction << std::endl
       << "Contact point friction vector" << std::endl;
    for (size_t i = 0; i < friction_vec.size(); ++i)
      {os << "Rib " << i << " - f = " << friction_vec[i] << std::endl;}
    os << "Contact depth (on average point)" << std::endl
       << "d = " << depth << " m" << std::endl
       << "Contact depth vector" << std::endl;
    for (size_t i = 0; i < depth_vec.size(); ++i)
      {os << "Rib " << i << " - d = " << depth_vec[i] << " m" << std::endl;}
    os << "Contact area (total)" << std::endl
       << "A = " << area << " m^2" << std::endl
       << "Contact area vector" << std::endl;
    for (size_t i = 0; i < area_vec.size(); ++i)
      {os << "Rib " << i << " - A = " << area_vec[i] << " m^2" << std::endl;}
    os << "Contact volume (total)" << std::endl
       << "V = " << volume << " m^3" << std::endl
       << "Contact volume vector" << std::endl;
    for (size_t i = 0; i < volume_vec.size(); ++i)
      {os << "Rib " << i << " - V = " << volume_vec[i] << " m^3" << std::endl;}
    os << "Shell reference frame" << std::endl
       << this->m_affine.matrix() << std::endl
       << "Local contact point reference frame" << std::endl
       << pose.matrix() << std::endl
       << "Relative pose angles" << std::endl
       << "[Γ ß α]' = " << relative_angles.transpose() / PI << "pi rad" << std::endl
       << "Ribs relative pose angles" << std::endl;
    for (size_t i = 0; i < relative_angles_vec.size(); ++i)
      {os << "Rib " << i << " - [Γ ß α]' = " << relative_angles_vec[i].transpose() / PI << "pi rad" << std::endl;}
    os << std::endl;
    
    os << " ------------     END     ------------" << std::endl
       << std::endl;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  shell::updateRibsCandidates(
    triangleground::vecptr const & local_ground
  )
  {
    real d0, d1, d2;
    int  sum;
    size_t size = this->size();

    std::vector<real> y(size);
    for (size_t i = 0; i < size; ++i)
    {
      y[i] = this->m_ribs[i].center().y();
      if (!this->m_candidates[i].empty())
        {this->m_candidates[i].clear();}
    }

    // Create shell middle plane
    plane mid_plane(this->translation(), this->y());
    mid_plane.normalize();

    // Iterate on triangles
    for (size_t i = 0; i < local_ground.size(); ++i)
    {
      // Calculate distance of i-th triangle
      d0 = mid_plane.signedDistance(local_ground[i]->vertex(0));
      d1 = mid_plane.signedDistance(local_ground[i]->vertex(1));
      d2 = mid_plane.signedDistance(local_ground[i]->vertex(2));

      // Iterate on ribs
      for (size_t j = 0; j < size; ++j)
      {
        // Calculate sign of j-th rib distance
        sum = integer((real(0.0) < (d0-y[j])) - ((d0-y[j]) < real(0.0))) +
              integer((real(0.0) < (d1-y[j])) - ((d1-y[j]) < real(0.0))) +
              integer((real(0.0) < (d2-y[j])) - ((d2-y[j]) < real(0.0)));

        // Fill candidates list
        if (integer(-3) < sum && sum < integer(3))
          {this->m_candidates[j].push_back(local_ground[i]);}
      }
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// eof: shell.cc
///
