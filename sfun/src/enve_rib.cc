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
    real         angle
  )
    : disk(radius, plane),
      m_width(width),
      m_angle(angle)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    real         radius,
    plane const &plane
  )
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
    real         angle
  )
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
    real angle
  )
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
    real normal_z
  )
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
    rib  const &rib_in,
    real        tolerance
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
    std::vector<size_t>    const &tris,
    affine                 const &affine_in,
    std::string            const  method,
    output                       &out
  ) 
    const
  {
    if (method == "geometric")
      return this->envelopGeometric(localGround, tris, affine_in, out);
    else if (method == "sampling")
      return this->envelopSampling(localGround, affine_in, out);
    else
      ENVE_ERROR("enve::rib::envelop(mesh, ...): invalid enveloping method.\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelop(
    ground::flat const &localGround,
    affine       const &affine_in,
    std::string  const  method,
    output             &out
  ) 
    const
  {
    if (method == "geometric")
      return this->envelopGeometric(localGround, affine_in, out);
    else if (method == "sampling")
      return this->envelopSampling(localGround, affine_in, out);
    else
      ENVE_ERROR("enve::rib::envelop(mesh, ...): invalid enveloping method.\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelop(
    affine const &affine_in,
    output       &out
  ) 
    const
  {
    point origin(affine_in.translation());
    mat3  rotation(affine_in.linear());

    out.point    = origin + rotation * (this->center() - point(0.0, 0.0, this->radius()));
    out.normal   = rotation * UNITZ_VEC3;
    out.friction = 0.0;
    out.depth    = 0.0;
    out.area     = 0.0;
    out.volume   = 0.0;

    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopGeometric(
    triangleground::vecptr const &localGround,
    std::vector<size_t>    const &tris,
    affine                 const &affine_in,
    output                       &out
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
    vec3    normal_tmp;
    real    FA, FC, FB, FA4CB;
    real    segmentLength_tmp;
    real    segmentArea_tmp;
    real    segmentVolume_tmp;
    real    segmentAreaTotal   = 0.0;
    real    segmentVolumeTotal = 0.0;

    point contactPoint_tmp    = point::Constant(0.0);
    vec3  contactNormal_tmp   = vec3::Constant(0.0);
    real  contactFriction_tmp = 0.0;

    point contactPoint_iter    = point::Constant(0.0);
    vec3  contactNormal_iter   = vec3::Constant(0.0);
    real  contactFriction_iter = 0.0;

    vec3  ribNormalGround(rotation * this->normal());
    point ribCenterGround(origin + rotation * center);
    disk  ribGround(radius, ribCenterGround, ribNormalGround);

    size_t i;
    for (size_t k = 0; k < tris.size(); ++k)
    {
      i = tris[k];
      if (acme::intersection(*localGround[i], ribGround, segment_tmp, 1e-5))
      {
        segmentLength_tmp = segment_tmp.length();
        if (segmentLength_tmp < EPSILON_LOW)
        {
          break;
        }

        // Simpson's rule
        FA    = std::max(0.0, radius - (segment_tmp.vertex(0)  - ribCenterGround).norm());
        FC    = std::max(0.0, radius - (segment_tmp.centroid() - ribCenterGround).norm());
        FB    = std::max(0.0, radius - (segment_tmp.vertex(1)  - ribCenterGround).norm());
        FA4CB = std::max(FA + 4.0*FC + FB, EPSILON_LOW);

        int_bool = true;

        segmentArea_tmp   = segmentLength_tmp * width;
        segmentAreaTotal += segmentArea_tmp;

        segmentVolume_tmp   = segmentLength_tmp/6.0 * FA4CB * width;
        segmentVolumeTotal += segmentVolume_tmp;

        contactPoint_iter    = (segment_tmp.vertex(0)*FA + segment_tmp.centroid()*4.0*FC + segment_tmp.vertex(1)*FB) / FA4CB;
        normal_tmp           = (ribNormalGround.cross(ribCenterGround - contactPoint_iter)).normalized();
        contactNormal_iter   = (localGround[i]->normal() - normal_tmp * localGround[i]->normal().dot(normal_tmp)).normalized();
        contactFriction_iter = localGround[i]->friction();

        contactPoint_tmp    += segmentVolume_tmp * contactPoint_iter;
        contactNormal_tmp   += segmentVolume_tmp * contactNormal_iter;
        contactFriction_tmp += segmentVolume_tmp * contactFriction_iter;
      }
    }
    if (int_bool)
    {
      segmentAreaTotal   = std::max(segmentAreaTotal,   EPSILON_HIGH);
      segmentVolumeTotal = std::max(segmentVolumeTotal, EPSILON_HIGH);

      out.point    = contactPoint_tmp    / segmentVolumeTotal;
      out.normal   = (contactNormal_tmp  / segmentVolumeTotal).normalized();
      out.friction = contactFriction_tmp / segmentVolumeTotal;
      out.depth    = radius - (out.point - ribCenterGround).norm();
      out.area     = segmentAreaTotal;
      out.volume   = segmentVolumeTotal;
      return true;
    }
    else
    {
      out.point    = origin + rotation * (center - point(0.0, 0.0, radius));
      out.normal   = rotation * UNITZ_VEC3;
      out.friction = 0.0;
      out.depth    = 0.0;
      out.area     = 0.0;
      out.volume   = 0.0;
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopGeometric(
    ground::flat const &localGround,
    affine       const &affine_in,
    output             &out
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
    vec3    normal_tmp;

    bool int_bool = acme::intersection(localGround, ribGround, segment_tmp, EPSILON_HIGH);
    if (int_bool && segment_tmp.length() > EPSILON_LOW)
    {
      out.point    = segment_tmp.centroid();
      normal_tmp   = (ribNormalGround.cross(ribCenterGround - out.point)).normalized();
      out.normal   = (localGround.normal()*(1.0 - localGround.normal().dot(normal_tmp))).normalized();
      out.friction = localGround.friction();
      out.depth    = radius - (out.point - ribCenterGround).norm();
      out.area     = 2*std::sqrt(out.depth*(2*radius-out.depth))*width;
      out.volume   = (radius*radius*std::acos((radius-out.depth)/radius) - 
                     (radius-out.depth)*std::sqrt(out.depth*(2*radius-out.depth)))*width;
      return true;
    }
    else
    {
      out.point    = origin + rotation * (center - point(0.0, 0.0, radius));
      out.normal   = rotation * UNITZ_VEC3;
      out.friction = 0.0;
      out.depth    = 0.0;
      out.area     = 0.0;
      out.volume   = 0.0;
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopSampling(
    triangleground::vecptr const &localGround,
    affine                 const &affine_in,
    output                       &out
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

    vec3  lineDirection(-UNITZ_VEC3);
    bool sampling = true;
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center + deltaX), lineDirection,
                                              point_vec[0], normal_tmp, friction_vec[0]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center - deltaX), lineDirection,
                                              point_vec[1], normal_tmp, friction_vec[1]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center + deltaY), lineDirection,
                                              point_vec[2], normal_tmp, friction_vec[2]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center - deltaY), lineDirection,
                                              point_vec[3], normal_tmp, friction_vec[3]);

    out.point  = (point_vec[0] + point_vec[1] + point_vec[2] + point_vec[3]) / 4.0;
    out.normal = ((point_vec[0] - point_vec[1]).cross(point_vec[2] - point_vec[3])).normalized();

    vec3 e_y = affine_in.linear().col(1);
    vec3 e_x = (out.normal.cross(e_y)).normalized();
    vec3 e_z = (e_y.cross(e_x)).normalized();

    out.depth = radius*std::abs(out.normal.dot(e_z)) - (out.point - ribCenterGround).norm();
    
    if ( sampling && out.depth > 0.0 )
    {
      out.friction = (friction_vec[0] + friction_vec[1] + friction_vec[2] + friction_vec[3]) / 4.0;
      out.area     = 2*std::sqrt(out.depth*(2*radius-out.depth))*width;
      out.volume   = (radius*radius*std::acos((radius-out.depth)/radius) - 
                     (radius-out.depth)*std::sqrt(out.depth*(2*radius-out.depth)))*width;
      return true;
    }
    else
    {
      out.point    = origin + rotation * (center - point(0.0, 0.0, radius));
      out.normal   = rotation * UNITZ_VEC3;
      out.friction = 0.0;
      out.depth    = 0.0;
      out.area     = 0.0;
      out.volume   = 0.0;
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopSampling(
    ground::flat const &localGround,
    affine       const &affine_in,
    output             &out
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

    vec3  lineDirection(-UNITZ_VEC3);
    bool sampling = true;
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center + deltaX), lineDirection,
                                              point_vec[0], normal_tmp, friction_vec[0]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center - deltaX), lineDirection,
                                              point_vec[1], normal_tmp, friction_vec[1]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center + deltaY), lineDirection,
                                              point_vec[2], normal_tmp, friction_vec[2]);
    sampling = sampling && this->samplingLine(localGround, origin + rotation * (center - deltaY), lineDirection,
                                              point_vec[3], normal_tmp, friction_vec[3]);

    out.point  = (point_vec[0] + point_vec[1] + point_vec[2] + point_vec[3]) / 4.0;
    out.normal = ((point_vec[0] - point_vec[1]).cross(point_vec[2] - point_vec[3])).normalized();

    vec3 e_y = affine_in.linear().col(1);
    vec3 e_x = (out.normal.cross(e_y)).normalized();
    vec3 e_z = (e_y.cross(e_x)).normalized();
    
    out.depth  = radius*std::abs(out.normal.dot(e_z)) - (out.point - ribCenterGround).norm();

    if ( sampling && out.depth > 0.0 )
    {
      out.friction = (friction_vec[0] + friction_vec[1] + friction_vec[2] + friction_vec[3]) / 4.0;
      out.area     = 2*std::sqrt(out.depth*(2*radius-out.depth))*width;
      out.volume   = (radius*radius*std::acos((radius-out.depth)/radius) - 
                     (radius-out.depth)*std::sqrt(out.depth*(2*radius-out.depth)))*width;
      return true;
    }
    else
    {
      out.point    = origin + rotation * (center - point(0.0, 0.0, radius));
      out.normal   = rotation * UNITZ_VEC3;
      out.friction = 0.0;
      out.depth    = 0.0;
      out.area     = 0.0;
      out.volume   = 0.0;
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::samplingLine(
    triangleground::vecptr const &localGround,
    point                  const &origin,
    vec3                   const &direction,
    point                        &contactPoint,
    vec3                         &contactNormal,
    real                         &contactFriction
  ) 
    const
  {
    size_t             localGroundSize = localGround.size();
    point              point_tmp;
    std::vector<point> point_vec;
    std::vector<vec3>  normal_vec;
    std::vector<real>  friction_vec;
    point_vec.reserve(localGroundSize);
    normal_vec.reserve(localGroundSize);
    friction_vec.reserve(localGroundSize);
    bool               int_bool = false;
    for (size_t i = 0; i < localGroundSize; ++i)
    {
      if (acme::intersection(line(origin, direction), *localGround[i], point_tmp, EPSILON_HIGH))
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
    else if (localGroundSize > 0 && !int_bool)
    {
      // Flying over the mesh
      return false;
    }
    else if (localGroundSize == 0)
    {
      // Out of mesh
      return false;
    }
    else
    {
      ENVE_ERROR("enve::rib::samplingLine(mesh, ...): condition not handled.\n");
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
    if (acme::intersection(line(origin, direction), localGround, contactPoint, EPSILON_HIGH))
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

  bool
  rib::intersection(
    line     const &line_in,
    triangle const &triangle_in,
    point          &point_out,
    real            tolerance
  )
    const
  {
    point vertex0(triangle_in.vertex(0));
    point vertex1(triangle_in.vertex(1));
    point vertex2(triangle_in.vertex(2));
    vec3  edge1(vertex1 - vertex0);
    vec3  edge2(vertex2 - vertex0);
    point origin(line_in.origin());
    vec3  direction(line_in.direction());

    vec3 h, s, q;
    real a, f, u, v;
    h = direction.cross(edge2);
    a = edge1.dot(h);
    if (a > -tolerance && a < tolerance)
      return false;
    real tolerance_space = 2.5e-02;
    f = 1.0 / a;
    s = origin - vertex0;
    u = f * s.dot(h);
    if (u < 0.0-tolerance_space || u > 1.0+tolerance_space)
      return false;
    q = s.cross(edge1);
    v = f * direction.dot(q);
    if (v < 0.0-tolerance_space || u + v > 1.0+tolerance_space)
      return false;
    real t    = f * edge2.dot(q);
    point_out = origin + t * direction;
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

///
/// file: enve_rib.cc
///