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
/// file: acme_utils.cc
///

#include "acme_utils.hh"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace acme
{
  /*\
   |         _   _ _
   |   _   _| |_(_) |___
   |  | | | | __| | / __|
   |  | |_| | |_| | \__ \
   |   \__,_|\__|_|_|___/
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  std::ostream &
  operator<<(
    std::ostream &os,
    vec3 const   &obj)
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "[ " << obj[0] << ", " << obj[1] << ", " << obj[2] << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  std::ostream &
  operator<<(
    std::ostream &os,
    point const  &obj)
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << "[ " << obj[0] << ", " << obj[1] << ", " << obj[2] << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream &os,
    line const &obj)
  {
    point obj_origin(obj.origin());
    vec3  obj_direction(obj.direction());
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << std::endl
       << "Origin = "
       << "[ " << obj_origin[0] << ", " << obj_origin[1] << ", " << obj_origin[2] << " ]'" << std::endl
       << "Direction = "
       << "[ " << obj_direction[0] << ", " << obj_direction[2] << ", " << obj_direction[2] << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream &os,
    ray const  &obj)
  {
    point obj_origin(obj.origin());
    vec3  obj_direction(obj.direction());
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << std::endl
       << "Origin = "
       << "[ " << obj_origin[0] << ", " << obj_origin[1] << ", " << obj_origin[2] << " ]'" << std::endl
       << "Direction = "
       << "[ " << obj_direction[0] << ", " << obj_direction[2] << ", " << obj_direction[2] << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream  &os,
    plane const &obj)
  {
    point obj_origin(obj.origin());
    vec3  obj_normal(obj.normal());
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << std::endl
       << "Origin = "
       << "[ " << obj_origin[0] << ", " << obj_origin[1] << ", " << obj_origin[2] << " ]'" << std::endl
       << "Normal = "
       << "[ " << obj_normal[0] << ", " << obj_normal[1] << ", " << obj_normal[2] << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream    &os,
    segment const &obj)
  {
    point obj_point_0(obj.vertex(0));
    point obj_point_1(obj.vertex(1));
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << std::endl
       << "Vertex 0 = "
       << "[ " << obj_point_0[0] << ", " << obj_point_0[1] << ", " << obj_point_0[2] << " ]'" << std::endl
       << "Vertex 1 = "
       << "[ " << obj_point_1[0] << ", " << obj_point_1[1] << ", " << obj_point_1[2] << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream &os,
    aabb const &obj)
  {
    point obj_point_min(obj.min());
    point obj_point_max(obj.max());
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << std::endl
       << "Min = "
       << "[ " << obj_point_min[0] << ", " << obj_point_min[1] << ", " << obj_point_min[2] << " ]'" << std::endl
       << "Max = "
       << "[ " << obj_point_max[0] << ", " << obj_point_max[1] << ", " << obj_point_max[2] << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream     &os,
    triangle const &obj)
  {
    point obj_vertex_0(obj.vertex(0));
    point obj_vertex_2(obj.vertex(1));
    point obj_vertex_1(obj.vertex(2));
    os << std::scientific
       << std::showpoint
       << std::setprecision(6)
       << std::endl
       << "Vertex 0 = "
       << "[ " << obj_vertex_0[0] << ", " << obj_vertex_0[1] << ", " << obj_vertex_0[2] << " ]'" << std::endl
       << "Vertex 1 = "
       << "[ " << obj_vertex_1[0] << ", " << obj_vertex_1[1] << ", " << obj_vertex_1[2] << " ]'" << std::endl
       << "Vertex 2 = "
       << "[ " << obj_vertex_2[0] << ", " << obj_vertex_2[1] << ", " << obj_vertex_2[2] << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream &os,
    disk const &obj)
  {
    point obj_center(obj.center());
    vec3  obj_normal(obj.normal());
    os << std::scientific
       << std::showpoint
       << std::setprecision(10)
       << std::endl
       << "Radius = "
       << obj.radius() << std::endl
       << "Center = "
       << "[ " << obj_center[0] << ", " << obj_center[1] << ", " << obj_center[2] << " ]'" << std::endl
       << "Normal = "
       << "[ " << obj_normal[0] << ", " << obj_normal[1] << ", " << obj_normal[2] << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream &os,
    ball const &obj)
  {
    real  obj_radius(obj.radius());
    point obj_center(obj.center());
    os << std::scientific
       << std::showpoint
       << std::setprecision(10)
       << std::endl
       << "Radius = "
       << obj_radius << std::endl
       << "Center = "
       << "[ " << obj_center[0] << ", " << obj_center[1] << ", " << obj_center[2] << " ]'" << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  out_stream &
  operator<<(
    out_stream   &os,
    affine const &obj)
  {
    os << std::scientific
       << std::showpoint
       << std::setprecision(10)
       << std::endl
       << "Affine = [ " << obj(0, 0) << ", " << obj(0, 1) << ", " << obj(0, 2) << ", " << obj(0, 3) << " ]" << std::endl
       << "         [ " << obj(1, 0) << ", " << obj(1, 1) << ", " << obj(1, 2) << ", " << obj(1, 3) << " ]" << std::endl
       << "         [ " << obj(2, 0) << ", " << obj(2, 1) << ", " << obj(2, 2) << ", " << obj(2, 3) << " ]" << std::endl
       << "         [ " << obj(3, 0) << ", " << obj(3, 1) << ", " << obj(3, 2) << ", " << obj(3, 3) << " ]" << std::endl
       << std::endl;
    return os;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

#endif

///
/// eof: acme_utils.cc
///