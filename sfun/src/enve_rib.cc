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
/// file: enve_rib.cc
///

#include "enve_rib.hh"

using namespace acme;

namespace enve
{

  /*\
   |        _ _
   |   _ __(_) |__
   |  | '__| | '_ \
   |  | |  | | |_) |
   |  |_|  |_|_.__/
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::~rib()
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib()
    : disk(NAN_DISK),
      m_width(QUIET_NAN),
      m_angle(QUIET_NAN)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real         radius,
    plane const &plane,
    real         width,
    real         angle)
    : disk(radius, plane),
      m_width(width),
      m_angle(angle)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real         radius,
    plane const &plane)
    : disk(radius, plane),
      m_width(QUIET_NAN),
      m_angle(QUIET_NAN)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real         radius,
    point const &center,
    vec3  const &normal,
    real         width,
    real         angle)
    : disk(radius, center, normal),
      m_width(width),
      m_angle(angle)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real radius,
    real center_x,
    real center_y,
    real center_z,
    real normal_x,
    real normal_y,
    real normal_z,
    real width,
    real angle)
    : disk(radius, center_x, center_y, center_z, normal_x, normal_y, normal_z),
      m_width(width),
      m_angle(angle)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real radius,
    real center_x,
    real center_y,
    real center_z,
    real normal_x,
    real normal_y,
    real normal_z)
    : disk(radius, center_x, center_y, center_z, normal_x, normal_y, normal_z),
      m_width(QUIET_NAN),
      m_angle(QUIET_NAN)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib &
  rib::operator=(
    rib const &rib_in
  )
  {
    if (this == &rib_in)
    {
      return *this;
    }
    else
    {
      this->disk::operator=(rib_in);
      this->m_width       = rib_in.m_width;
      this->m_angle       = rib_in.m_angle;
      return *this;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  rib::copy(
    rib const &rib_in
  )
  {
    this->radius()      = rib_in.radius();
    this->layingPlane() = rib_in.layingPlane();
    this->m_width       = rib_in.m_width;
    this->m_angle       = rib_in.m_angle;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  rib::width(void)
    const
  {
    return this->m_width;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real const &
  rib::angle(void)
    const
  {
    return this->m_angle;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  rib::width(void)
  {
    return this->m_width;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real &
  rib::angle(void)
  {
    return this->m_angle;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::isApprox(
    rib const &rib_in,
    real       tolerance
  )
    const
  {
    return this->disk::isApprox(rib_in) &&
           acme::isApprox(this->m_width, rib_in.m_width, tolerance) &&
           acme::isApprox(this->m_angle, rib_in.m_angle, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelop(
    triangleground::vecptr const &localGround,
    affine                 const &affine_in,
    std::string            const  method,
    point                        &contactPoint,
    vec3                         &contactNormal,
    real                         &contactFriction,
    real                         &contactDepth,
    real                         &contactArea,
    real                         &contactVolume
  ) 
    const
  {
    if (method == "geometric")
      return this->envelopGeometric(localGround, affine_in, contactPoint, contactNormal, contactFriction, contactDepth, contactArea, contactVolume);
    else if (method == "sampling")
      return this->envelopSampling(localGround, affine_in, contactPoint, contactNormal, contactFriction, contactDepth, contactArea, contactVolume);
    else
      ENVE_ERROR("enve::rib::envelop(mesh, ...): invalid enveloping method.\n");
  }

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelop(
    ground::flat const &localGround,
    affine       const &affine_in,
    std::string  const  method,
    point              &contactPoint,
    vec3               &contactNormal,
    real               &contactFriction,
    real               &contactDepth,
    real               &contactArea,
    real               &contactVolume
  ) 
    const
  {
    if (method == "geometric")
      return this->envelopGeometric(localGround, affine_in, contactPoint, contactNormal, contactFriction, contactDepth, contactArea, contactVolume);
    else if (method == "sampling")
      return this->envelopSampling(localGround, affine_in, contactPoint, contactNormal, contactFriction, contactDepth, contactArea, contactVolume);
    else
      ENVE_ERROR("enve::rib::envelop(mesh, ...): invalid enveloping method.\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopGeometric(
    triangleground::vecptr const &localGround,
    affine                 const &affine_in,
    point                        &contactPoint,
    vec3                         &contactNormal,
    real                         &contactFriction,
    real                         &contactDepth,
    real                         &contactArea,
    real                         &contactVolume
  ) 
    const
  {
    real  radius = this->radius();
    real  width  = this->width();
    point center = this->center();
    point origin(affine_in.translation());
    mat3  rotation(affine_in.linear());

    bool int_bool = false;
    
    segment segment_tmp;
    real    FA, FC, FB;
    real    segmentLength_tmp;
    real    segmentArea_tmp;
    real    segmentLengthTotal = 0.0;
    real    segmentAreaTotal   = 0.0;

    point contactPoint_tmp    = point::Constant(0.0);
    vec3  contactNormal_tmp   = vec3::Constant(0.0);
    real  contactFriction_tmp = 0.0;

    vec3  ribNormalGround(rotation * this->normal());
    point ribCenterGround(origin + rotation * center);
    disk  ribGround(radius, ribCenterGround, ribNormalGround);
    real  tolerance = 1e-4;
    for (size_t i = 0; i < localGround.size(); ++i)
    {
      if (acme::intersection(*localGround[i], ribGround, segment_tmp, EPSILON_LOW))
      { 
        int_bool = true;
        segmentLength_tmp   = segment_tmp.length();
        segmentLengthTotal += segmentLength_tmp;

        // Simpson's rule
        FA = radius - (segment_tmp.vertex(0) - ribCenterGround).norm();
        FC = radius - (segment_tmp.centroid() - ribCenterGround).norm();
        FB = radius - (segment_tmp.vertex(1) - ribCenterGround).norm();
        
        if (FA < -tolerance) {
          ENVE_ERROR("enve::rib::envelopGeometric(mesh, ...): FA less than 0.\n");
        } else if (FA < 0.0) {
          FA = 0.0;
        }
        

        if (FC < -tolerance) {
          ENVE_ERROR("enve::rib::envelopGeometric(mesh, ...): FC less than 0.\n");
        } else if (FC < 0.0) {
          FC = 0.0;
        }
        
        
        if (FB < -tolerance) {
          ENVE_ERROR("enve::rib::envelopGeometric(mesh, ...): FB less than 0.\n");
        } else if (FB < 0.0) {
          FB = 0.0;
        }
        
        segmentArea_tmp   = segmentLength_tmp/6 * (FA + 4*FC + FB);
        segmentAreaTotal += segmentArea_tmp;

        contactPoint_tmp   = segmentArea_tmp * segmentLength_tmp/6 *
                             (segment_tmp.vertex(0)*FA + 4*segment_tmp.centroid()*FC + segment_tmp.vertex(1)*FB);
        contactNormal_tmp += segmentArea_tmp * ((ribCenterGround - contactPoint_tmp).normalized() +
                             ribNormalGround*ribNormalGround.dot(localGround[i]->normal())
                             ).normalized();
        contactFriction_tmp += segmentArea_tmp * localGround[i]->friction();
      }
    }
    if (int_bool)
    {
      if (segmentAreaTotal < EPSILON_HIGH){
        segmentLengthTotal += EPSILON_HIGH;
        segmentAreaTotal   += EPSILON_HIGH;
      }

      contactPoint    = contactPoint_tmp    / segmentAreaTotal;
      contactNormal   = contactNormal_tmp   / segmentAreaTotal;
      contactFriction = contactFriction_tmp / segmentAreaTotal;
      contactDepth    = radius - (contactPoint - ribCenterGround).norm();
      contactArea     = segmentLengthTotal*width;
      contactVolume   = segmentAreaTotal*width;
      return true;
    }
    else
    {
      contactPoint    = origin + rotation * (center - point(0.0, 0.0, radius));
      contactNormal   = rotation * UNITZ_VEC3;
      contactFriction = 0.0;
      contactDepth    = 0.0;
      contactArea     = 0.0;
      contactVolume   = 0.0;
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopGeometric(
    ground::flat const &localGround,
    affine       const &affine_in,
    point              &contactPoint,
    vec3               &contactNormal,
    real               &contactFriction,
    real               &contactDepth,
    real               &contactArea,
    real               &contactVolume
  ) 
    const
  {
    real  radius = this->radius();
    real  width  = this->width();
    point center(this->center());
    point origin(affine_in.translation());
    mat3  rotation(affine_in.linear());

    vec3  ribNormalGround(rotation * this->normal());
    point ribCenterGround(origin + rotation * center);
    disk ribGround(radius, ribCenterGround, ribNormalGround);
    segment segment_tmp;
    if (acme::intersection(localGround, ribGround, segment_tmp, EPSILON_LOW))
    {
      contactPoint    = segment_tmp.centroid();
      contactNormal   = ((ribCenterGround - contactPoint).normalized() +
                        ribNormalGround*ribNormalGround.dot(localGround.normal())
                        ).normalized();
      contactFriction = localGround.friction();
      contactDepth    = radius - (contactPoint - ribCenterGround).norm();
      contactArea     = 2*std::sqrt(contactDepth*(2*radius-contactDepth))*width;
      contactVolume   = (radius*radius*std::acos((radius-contactDepth)/radius) - 
                        (radius-contactDepth)*std::sqrt(contactDepth*(2*radius-contactDepth)))*width;
      return true;
    }
    else
    {
      contactPoint    = origin + rotation * (center - point(0.0, 0.0, radius));
      contactNormal   = rotation * UNITZ_VEC3;
      contactFriction = 0.0;
      contactDepth    = 0.0;
      contactArea     = 0.0;
      contactVolume   = 0.0;
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopSampling(
    triangleground::vecptr const &localGround,
    affine                 const &affine_in,
    point                        &contactPoint,
    vec3                         &contactNormal,
    real                         &contactFriction,
    real                         &contactDepth,
    real                         &contactArea,
    real                         &contactVolume
  ) 
    const
  {
    real  radius = this->radius();
    real  width  = this->width();
    point center(this->center());
    point origin(affine_in.translation());
    mat3  rotation(affine_in.linear());

    vec3  deltaX(0.1*radius, 0.0, 0.0);
    vec3  deltaY(0.0, 0.3*width, 0.0);
    std::vector<point> point_vec(4);
    vec3               normal_tmp;
    std::vector<real>  friction_vec(4);
    vec3  ribNormalGround(rotation * this->normal());
    point ribCenterGround(origin + rotation * center);

    vec3  lineDirection(rotation * (-UNITZ_VEC3));
    int sampling = true;
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center + deltaX), lineDirection, point_vec[0], normal_tmp, friction_vec[0]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center - deltaX), lineDirection, point_vec[1], normal_tmp, friction_vec[1]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center + deltaY), lineDirection, point_vec[2], normal_tmp, friction_vec[2]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center - deltaY), lineDirection, point_vec[3], normal_tmp, friction_vec[3]);
    
    contactPoint = (point_vec[0] + point_vec[1] + point_vec[2] + point_vec[3]) / 4.0;
    
    if ( sampling && (ribCenterGround - contactPoint).norm() <= radius )
    {
      contactNormal   = ((ribCenterGround - contactPoint).normalized() +
                        ribNormalGround*ribNormalGround.dot(((point_vec[0] - point_vec[1]).cross(point_vec[2] - point_vec[3])).normalized())
                        ).normalized();
      contactFriction = (friction_vec[0] + friction_vec[1] + friction_vec[2] + friction_vec[3]) / 4.0;
      contactDepth    = radius - (contactPoint - ribCenterGround).norm();
      contactArea     = 2*std::sqrt(contactDepth*(2*radius-contactDepth))*width;
      contactVolume   = (radius*radius*std::acos((radius-contactDepth)/radius) - 
                        (radius-contactDepth)*std::sqrt(contactDepth*(2*radius-contactDepth)))*width;
      return true;
    }
    else
    {
      contactPoint    = origin + rotation * (center - point(0.0, 0.0, radius));
      contactNormal   = rotation * UNITZ_VEC3;
      contactFriction = 0.0;
      contactDepth    = 0.0;
      contactArea     = 0.0;
      contactVolume   = 0.0;
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopSampling(
    ground::flat const &localGround,
    affine       const &affine_in,
    point              &contactPoint,
    vec3               &contactNormal,
    real               &contactFriction,
    real               &contactDepth,
    real               &contactArea,
    real               &contactVolume
  ) 
    const
  {
    real  radius = this->radius();
    real  width  = this->width();
    point center(this->center());
    point origin(affine_in.translation());
    mat3  rotation(affine_in.linear());

    vec3  deltaX(0.1*radius, 0.0, 0.0);
    vec3  deltaY(0.0, 0.3*width, 0.0);
    std::vector<point> point_vec(4);
    vec3               normal_tmp;
    std::vector<real>  friction_vec(4);
    vec3  ribNormalGround(rotation * this->normal());
    point ribCenterGround(origin + rotation * center);

    vec3  lineDirection(rotation * (-UNITZ_VEC3));
    bool sampling = true;
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center + deltaX), lineDirection, point_vec[0], normal_tmp, friction_vec[0]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center - deltaX), lineDirection, point_vec[1], normal_tmp, friction_vec[1]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center + deltaY), lineDirection, point_vec[2], normal_tmp, friction_vec[2]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center - deltaY), lineDirection, point_vec[3], normal_tmp, friction_vec[3]);
    
    contactPoint = (point_vec[0] + point_vec[1] + point_vec[2] + point_vec[3]) / 4.0;
    
    if ( sampling && (ribCenterGround - contactPoint).norm() <= radius )
    {
      contactNormal   = ((ribCenterGround - contactPoint).normalized() +
                        ribNormalGround*ribNormalGround.dot(((point_vec[0] - point_vec[1]).cross(point_vec[2] - point_vec[3])).normalized())
                        ).normalized();
      contactFriction = (friction_vec[0] + friction_vec[1] + friction_vec[2] + friction_vec[3]) / 4.0;
      contactDepth    = radius - (contactPoint - ribCenterGround).norm();
      contactArea     = 2*std::sqrt(contactDepth*(radius-contactDepth))*width;
      contactVolume   = (radius*radius*std::acos((radius-contactDepth)/radius) - 
                        (radius-contactDepth)*std::sqrt(contactDepth*(2*radius-contactDepth)))*width;
      return true;
    }
    else
    {
      contactPoint    = origin + rotation * (center - point(0.0, 0.0, radius));
      contactNormal   = rotation * UNITZ_VEC3;
      contactFriction = 0.0;
      contactDepth    = 0.0;
      contactArea     = 0.0;
      contactVolume   = 0.0;
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::samplingLine(
    triangleground::vecptr const &localGround,
    point const                  &origin,
    vec3 const                   &direction,
    point                        &contactPoint,
    vec3                         &contactNormal,
    real                         &contactFriction
  ) 
    const
  {
    point              point_tmp;
    std::vector<point> point_vec;
    std::vector<vec3>  normal_vec;
    std::vector<real>  friction_vec;
    bool               int_bool = false;
    for (size_t i = 0; i < localGround.size(); ++i)
    {
      if (acme::intersection(line(origin, direction), *localGround[i], point_tmp, EPSILON_LOW))
      {
        point_vec.push_back(point_tmp);
        normal_vec.push_back(localGround[i]->normal());
        friction_vec.push_back(localGround[i]->friction());
        int_bool = true;
      }
    }
    // Select the highest intersection point
    if (point_vec.size() == 1 && int_bool)
    {
      contactPoint    = point_vec[0];
      contactNormal   = normal_vec[0];
      contactFriction = friction_vec[0];
      return true;
    }
    else if (point_vec.size() > 1 && int_bool)
    {
      contactPoint    = point_vec[0];
      contactNormal   = normal_vec[0];
      contactFriction = friction_vec[0];
      for (size_t j = 1; j < point_vec.size(); ++j)
      {
        if (point_vec[j].z() > contactPoint.z())
        {
          contactPoint    = point_vec[j];
          contactNormal   = normal_vec[j];
          contactFriction = friction_vec[j];
        }
      }
      return true;
    }
    else if (localGround.size() > 0 && !int_bool)
    {
      // Flying over the mesh
      return false;
    }
    else if (localGround.size() == 0)
    {
      // Out of mesh
      return false;
    }
    else
    {
      ENVE_ERROR("enve::rib::samplingLine(mesh, ...): not handled condition.");
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::samplingLine(
    ground::flat const &localGround,
    point        const &origin,
    vec3         const &direction,
    point              &contactPoint,
    vec3               &contactNormal,
    real               &contactFriction
  ) 
    const
  {
    if (acme::intersection(line(origin, direction), localGround, contactPoint, EPSILON_LOW))
    {
      contactNormal   = localGround.normal();
      contactFriction = localGround.friction();
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_rib.cc
///