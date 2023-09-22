/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * The ENVE project                                                    *
 *                                                                     *
 * Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *
 *                                                                     *
 * The ENVE project and its components are supplied under the terms of *
 * the open source BSD 3-Clause License. The contents of the ENVE      *
 * project and its components may not be copied or disclosed except in *
 * accordance with the terms of the BSD 3-Clause License.              *
 *                                                                     *
 * URL: https://opensource.org/licenses/BSD-3-Clause                   *
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
/// file: rib.cc
///

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include "enve.hh"

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

  rib::rib(void)
    : disk(NAN_DISK),
      m_id(integer(0)),
      m_y(QUIET_NAN),
      m_width(QUIET_NAN),
      m_angle(QUIET_NAN)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  rib::rib(
    integer id,
    real    radius,
    real    y,
    real    width,
    real    angle
  )
    : disk(radius, point(0.0, y, 0.0), UNITY_VEC3),
      m_id(id),
      m_y(y),
      m_width(width),
      m_angle(angle)
  {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  rib::copy(
    rib const & rib_obj
  )
  {
    this->disk::operator=(rib_obj);
    this->m_id    = rib_obj.m_id;
    this->m_width = rib_obj.m_width;
    this->m_angle = rib_obj.m_angle;
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
    rib  const & rib_obj,
    real         tolerance
  )
    const
  {
    return this->disk::isApprox(rib_obj, tolerance) &&
           IsApprox(this->m_id,    rib_obj.m_id,    tolerance) &&
           IsApprox(this->m_y,     rib_obj.m_y,     tolerance) &&
           IsApprox(this->m_width, rib_obj.m_width, tolerance) &&
           IsApprox(this->m_angle, rib_obj.m_angle, tolerance);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelop(
    triangleground::vecptr const & ground,
    affine                 const & pose,
    std::string            const   method,
    output                       & out
  )
    const
  {
    #define CMD "enve::rib::envelop(...): "

    if (method == "geometric")
      {return this->envelopGeometric(ground, pose, out);}
    else if (method == "sampling")
      {return this->envelopSampling(ground, pose, out);}
    else
      {ENVE_ERROR(CMD "invalid enveloping method.");}

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelop(
    ground::flat const & ground,
    affine       const & pose,
    std::string  const   method,
    output             & out
  )
    const
  {
    #define CMD "enve::rib::envelop(...): "

    if (method == "geometric")
      {return this->envelopGeometric(ground, pose, out);}
    else if (method == "sampling")
      {return this->envelopSampling(ground, pose, out);}
    else
      {ENVE_ERROR(CMD "invalid enveloping method.");}

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelop(
    affine const & pose,
    output       & out
  )
    const
  {
    out.point    = pose.translation() + pose.linear() *
                   (this->center() - this->radius() * UNITZ_VEC3);
    out.normal   = pose.linear() * UNITZ_VEC3;
    out.friction = real(0.0);
    out.depth    = real(0.0);
    out.area     = real(0.0);
    out.volume   = real(0.0);
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopGeometric(
    triangleground::vecptr const & ground,
    affine                 const & pose,
    output                       & out
  )
    const
  {
    // Rib alias variables
    real  const & radius = this->radius();
    real  const & width  = this->m_width;
    point const & center = this->center();

    // Compute rib pose
    point origin(pose.translation());
    mat3  rotation(pose.linear());
    mat3  rotation_inv(rotation.transpose());
    vec3  normal_grd(rotation * this->normal());
    point center_grd(origin + rotation * center);

    // Store temporaries
    vec3  normal_tmp;
    point p_a, p_b;
    real  t_a, t_b, t_c, t_d, r_a, r_b, r_c, cos_t_c, sin_t_c,
          section_area, segment_length_tmp, segment_area_tmp,
          segment_area_tot, segment_volume_tmp, segment_volume_tot;
    segment_area_tot   = real(0.0);
    segment_volume_tot = real(0.0);

    point contact_point_tmp(ZEROS_VEC3);
    vec3  contact_normal_tmp(ZEROS_VEC3);
    real  contact_friction_tmp = real(0.0);

    point contact_point_tot(ZEROS_VEC3);
    vec3  contact_normal_tot(ZEROS_VEC3);
    real  contact_friction_tot = real(0.0);

    // Compute remaining contact parameters
    bool int_bool = false;
    segment segment_tmp;
    disk  rib_grd(radius, center_grd, normal_grd);
    for (size_t i = 0; i < ground.size(); ++i)
    {
      // Perform rib/triangleground intersection
      if (Intersection(*ground[i], rib_grd, segment_tmp))
      {
        // Find intersection points
        p_a = rotation_inv * (segment_tmp.vertex(0) - center_grd);
        p_b = rotation_inv * (segment_tmp.vertex(1) - center_grd);

        // Find angles
        t_a = std::atan2(p_a.z(), p_a.x());
        t_b = std::atan2(p_b.z(), p_b.x());

        // Check consistency
        if(t_b < t_a)
        {
          std::swap(t_a, t_b);
          std::swap(r_a, r_b);
        }
        t_c = (t_a + t_b) / real(2.0);
        t_d = (t_b - t_a) / real(2.0);

        // Check intersection
        segment_length_tmp = segment_tmp.length();
        if (t_b - t_a < EPSILON_LOW && segment_length_tmp < EPSILON_LOW)
          {break;}
        else
          {int_bool = true;}

        // Find radius
        r_a = std::min(radius, p_a.norm());
        r_b = std::min(radius, p_b.norm());
        r_c = std::min(radius, std::max(real(0.0),
                real(2.0) * r_a * r_b / std::max(EPSILON_MEDIUM, r_a + r_b) * std::cos(t_d)
              ));

        // Find area
        section_area = radius * radius * t_d - r_a * r_b * std::sin(t_b - t_a) / real(2.0);

        // Store temporary results
        cos_t_c = std::cos(t_c);
        sin_t_c = std::sin(t_c);
        segment_area_tmp     = segment_length_tmp * width;
        segment_volume_tmp   = section_area * width;
        contact_point_tmp    = origin + rotation * (center + r_c * point(cos_t_c, real(0.0), sin_t_c));
        normal_tmp           = rotation * vec3(-cos_t_c, real(0.0), -sin_t_c);
        contact_normal_tmp   = (normal_tmp + normal_grd * (ground[i]->normal() - normal_tmp).dot(normal_grd)).normalized();
        contact_friction_tmp = ground[i]->friction();

        // Store total results
        segment_area_tot     += segment_area_tmp;
        segment_volume_tot   += segment_volume_tmp;
        contact_point_tot    += segment_volume_tmp * contact_point_tmp;
        contact_normal_tot   += segment_volume_tmp * contact_normal_tmp;
        contact_friction_tot += segment_volume_tmp * contact_friction_tmp;
      }
    }

    // Store output
    if (int_bool && (segment_area_tot > EPSILON_MEDIUM || segment_volume_tot > EPSILON_MEDIUM))
    {
      out.point    = contact_point_tot    / segment_volume_tot;
      out.normal   = (contact_normal_tot  / segment_volume_tot).normalized();
      out.friction = contact_friction_tot / segment_volume_tot;
      out.depth    = radius - (out.point - center_grd).norm();
      out.area     = segment_area_tot;
      out.volume   = segment_volume_tot;
      return true;
    }
    else
    {
      // No contact with the ground
      this->envelop(pose, out);
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopGeometric(
    ground::flat const & ground,
    affine       const & pose,
    output             & out
  )
    const
  {
    // Rib alias variables
    real  const & radius = this->radius();
    real  const & width  = this->m_width;
    point const & center = this->center();

    // Compute rib pose
    point origin(pose.translation());
    mat3  rotation(pose.linear());
    vec3  normal_grd(rotation * this->normal());
    point center_grd(origin + rotation * center);

    // Perform rib/flat intersection
    vec3 normal_tmp;
    segment segment_tmp;
    disk rib_grd(radius, center_grd, normal_grd);
    bool int_bool = Intersection(ground, rib_grd, segment_tmp, EPSILON_HIGH);

    // Compute remaining contact parameters
    if (int_bool && segment_tmp.length() > EPSILON_LOW)
    {
      out.point    = segment_tmp.centroid();
      normal_tmp   = (normal_grd.cross(center_grd - out.point)).normalized();
      out.normal   = (ground.normal() - normal_tmp * ground.normal().dot(normal_tmp)).normalized();
      out.friction = ground.friction();
      out.depth    = radius - (out.point - center_grd).norm();
      out.area     = real(2.0) * std::sqrt(out.depth * (real(2.0) * radius - out.depth)) * width;
      out.volume   = (radius * radius * std::acos((radius - out.depth) / radius) -
                     (radius - out.depth) * std::sqrt(out.depth * (real(2.0) * radius - out.depth))) * width;
      return true;
    }
    else
    {
      // No contact with the ground
      this->envelop(pose, out);
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopSampling(
    triangleground::vecptr const & ground,
    affine                 const & pose,
    output                       & out
  )
    const
  {
    // Rib alias variables
    real  const & radius = this->radius();
    real  const & width  = this->m_width;
    point const & center = this->center();

    // Compute rib pose
    point origin(pose.translation());
    mat3  rotation(pose.linear());
    vec3  normal_grd(rotation * this->normal());
    point center_grd(origin + rotation * center);

    // Store temporaries
    real delta_x = real(0.1) * radius;
    real delta_y = real(0.3) * width;
    std::vector<line>  line_vec(4);
    std::vector<point> point_vec(4);
    std::vector<real>  friction_vec(4);

    // Build sampling lines
    line_vec[0] = line(origin + rotation * (center + delta_x * UNITX_VEC3), -UNITZ_VEC3);
    line_vec[1] = line(origin + rotation * (center - delta_x * UNITX_VEC3), -UNITZ_VEC3);
    line_vec[2] = line(origin + rotation * (center + delta_y * UNITY_VEC3), -UNITZ_VEC3);
    line_vec[3] = line(origin + rotation * (center - delta_y * UNITY_VEC3), -UNITZ_VEC3);

    // Sample flat ground
    bool sampling = true;
    sampling = sampling && this->samplingLine(ground, line_vec[0], point_vec[0], friction_vec[0]);
    sampling = sampling && this->samplingLine(ground, line_vec[1], point_vec[1], friction_vec[1]);
    sampling = sampling && this->samplingLine(ground, line_vec[2], point_vec[2], friction_vec[2]);
    sampling = sampling && this->samplingLine(ground, line_vec[3], point_vec[3], friction_vec[3]);

    // Compute output point and normal
    out.point  = (point_vec[0] + point_vec[1] + point_vec[2] + point_vec[3]) / real(4.0);
    out.normal = ((point_vec[0] - point_vec[1]).cross(point_vec[2] - point_vec[3])).normalized();

    // Compute contact pose
    vec3 e_y = rotation.col(1).normalized();
    vec3 e_x = (out.normal.cross(e_y)).normalized();
    vec3 e_z = (e_y.cross(e_x)).normalized();

    // Compute contact depth
    out.depth = radius * std::abs(out.normal.dot(e_z)) - (out.point - center_grd).norm();

    // Compute remaining contact parameters
    if (sampling && out.depth > real(0.0))
    {
      out.friction = (friction_vec[0] + friction_vec[1] + friction_vec[2] + friction_vec[3]) / real(4.0);
      out.area     = real(2.0) * std::sqrt(out.depth * (real(2.0) * radius - out.depth)) * width;
      out.volume   = (radius * radius * std::acos((radius - out.depth) / radius) -
                     (radius - out.depth) * std::sqrt(out.depth * (real(2.0) * radius - out.depth))) * width;
      return true;
    }
    else
    {
      // No contact with the ground
      this->envelop(pose, out);
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::envelopSampling(
    ground::flat const & ground,
    affine       const & pose,
    output             & out
  )
    const
  {
    // Rib alias variables
    real  const & radius = this->radius();
    real  const & width  = this->m_width;
    point const & center = this->center();

    // Compute rib pose
    point origin(pose.translation());
    mat3  rotation(pose.linear());
    vec3  normal_grd(rotation * this->normal());
    point center_grd(origin + rotation * center);

    // Store temporaries
    real delta_x = real(0.1) * radius;
    real delta_y = real(0.3) * width;
    std::vector<line>  line_vec(4);
    std::vector<point> point_vec(4);
    std::vector<real>  friction_vec(4);

    // Build sampling lines
    line_vec[0] = line(origin + rotation * (center + delta_x * UNITX_VEC3), -UNITZ_VEC3);
    line_vec[1] = line(origin + rotation * (center - delta_x * UNITX_VEC3), -UNITZ_VEC3);
    line_vec[2] = line(origin + rotation * (center + delta_y * UNITY_VEC3), -UNITZ_VEC3);
    line_vec[3] = line(origin + rotation * (center - delta_y * UNITY_VEC3), -UNITZ_VEC3);

    // Sample flat ground
    bool sampling = true;
    sampling = sampling && this->samplingLine(ground, line_vec[0], point_vec[0], friction_vec[0]);
    sampling = sampling && this->samplingLine(ground, line_vec[1], point_vec[1], friction_vec[1]);
    sampling = sampling && this->samplingLine(ground, line_vec[2], point_vec[2], friction_vec[2]);
    sampling = sampling && this->samplingLine(ground, line_vec[3], point_vec[3], friction_vec[3]);

    // Compute output point and normal
    out.point  = (point_vec[0] + point_vec[1] + point_vec[2] + point_vec[3]) / real(4.0);
    out.normal = ((point_vec[0] - point_vec[1]).cross(point_vec[2] - point_vec[3])).normalized();

    // Compute contact pose
    vec3 e_y = rotation.col(1).normalized();
    vec3 e_x = (out.normal.cross(e_y)).normalized();
    vec3 e_z = (e_y.cross(e_x)).normalized();

    // Compute contact depth
    out.depth = radius * std::abs(out.normal.dot(e_z)) - (out.point - center_grd).norm();

    // Compute remaining contact parameters
    if (sampling && out.depth > real(0.0))
    {
      out.friction = (friction_vec[0] + friction_vec[1] + friction_vec[2] + friction_vec[3]) / real(4.0);
      out.area     = real(2.0) * std::sqrt(out.depth * (real(2.0) * radius - out.depth)) * width;
      out.volume   = (radius * radius * std::acos((radius - out.depth) / radius) -
                     (radius - out.depth) * std::sqrt(out.depth * (real(2.0) * radius - out.depth))) * width;
      return true;
    }
    else
    {
      // No contact with the ground
      this->envelop(pose, out);
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::samplingLine(
    triangleground::vecptr const & ground,
    line                   const & sampling_line,
    point                        & contact_point,
    real                         & contact_friction
  )
    const
  {
    #define CMD "enve::rib::samplingLine(...): "

    size_t             ground_size = ground.size();
    point              point_tmp;
    std::vector<point> point_vec;
    std::vector<real>  friction_vec;
    point_vec.reserve(ground_size);
    friction_vec.reserve(ground_size);
    bool int_bool = false;
    for (size_t i = 0; i < ground_size; ++i)
    {
      if (Intersection(sampling_line, *ground[i], point_tmp, EPSILON_HIGH)) // FIXME! line to instatiated once
      {
        point_vec.push_back(point_tmp);
        friction_vec.push_back(ground[i]->friction());
        int_bool = true;
      }
    }
    // Select the highest intersection point
    if (point_vec.size() == 1 && int_bool)
    {
      contact_point    = point_vec[0];
      contact_friction = friction_vec[0];
      return true;
    }
    else if (point_vec.size() > 1 && int_bool)
    {
      contact_point    = point_vec[0];
      contact_friction = friction_vec[0];
      for (size_t j = 1; j < point_vec.size(); ++j)
      {
        if (point_vec[j].z() > contact_point.z())
        {
          contact_point    = point_vec[j];
          contact_friction = friction_vec[j];
        }
      }
      return true;
    }
    else if (ground_size > 0 && !int_bool)
    {
      // Flying over the mesh
      return false;
    }
    else if (ground_size == 0)
    {
      // Out of mesh
      return false;
    }
    else
    {
      ENVE_ERROR(CMD "condition not handled.");
      //return false;
    }

    #undef CMD
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  rib::samplingLine(
    ground::flat const & ground,
    line         const & sampling_line,
    point              & contact_point,
    real               & contact_friction
  )
    const
  {
    if (Intersection(sampling_line, ground, contact_point, EPSILON_HIGH))
    {
      contact_friction = ground.friction();
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace enve

#endif

///
/// eof: rib.cc
///
