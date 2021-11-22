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
/// file: enve_shell.hh
///

#pragma once

#ifndef INCLUDE_ENVE_SHELL
#define INCLUDE_ENVE_SHELL

#include <acme.hh>
#include <acme_aabb.hh>
#include <acme_point.hh>
#include <acme_segment.hh>
#include <acme_utils.hh>

#include "enve.hh"
#include "enve_flat.hh"
#include "enve_hyperellipse.hh"
#include "enve_mesh.hh"
#include "enve_points.hh"
#include "enve_polynom.hh"
#include "enve_rib.hh"

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

  static point THROWAWAY_POINT    = point(NAN_POINT); //!< Throwaway static non-const point object
  static vec3  THROWAWAY_NORMAL   = vec3(NAN_VEC3);   //!< Throwaway static non-const vec3 object
  static real  THROWAWAY_FRICTION = real(QUIET_NAN);  //!< Throwaway static non-const real object

  //! Base class for ENVE shell models
  class shell
  {
  public:
    typedef std::shared_ptr<shell const> ptr;    //!< Pointer to shell object
    typedef std::vector<shell::ptr>      vecptr; //!< Vector of pointers to shell objects

  private:
    std::shared_ptr<shape> m_shape;  //!< Shell shape
    std::vector<rib>       m_ribs;   //!< Shell ribs vector
    affine                 m_affine; //!< Shell reference frame (ISO)
    std::shared_ptr<aabb>  m_bbox;   //!< Shell bounding aabb (must be transformed in the mesh reference frame before intersection!)

    std::vector<point> m_pointRib;  //!< Contact points vector on mesh (projected on rib plane)
    std::vector<point> m_pointMesh; //!< Contact points vector on mesh (projected on the mesh)
    std::vector<vec3>  m_normal;    //!< Contact normal vectors vector
    vecN               m_friction;  //!< Contact friction
    vecN               m_depth;     //!< Contact depth

  public:
    //! Shell class destructor
    ~shell(void);

    //! Shell copy constructor
    shell(shell const &) = delete;

    //! Shell move constructor
    shell(shell const &&) = delete;

    //! Shell class constructor
    shell(
      size_t size, //!< Input ribs number
      real   r_x,  //!< Input shell radius on x axis (m)
      real   m_x,  //!< Input shell curve degree for x axis
      real   r_y,  //!< Input shell radius on y axis (m)
      real   m_y,  //!< Input shell curve degree for y axis
      real   l_y   //!< Input surface half width on y axis (m)
    );

    //! Shell class constructor
    shell(
      size_t      size,                      //!< Input ribs number
      vecN const &dataR,                     //!< Vector of radius data (m)
      vecN const &dataY,                     //!< Vector of y data (m)
      size_t      order,                     //!< Polynom order
      real        tolerance = EPSILON_MEDIUM //!< Tolerance
    );

    //! Shell class constructor
    shell(
      size_t      size,  //!< Input ribs number
      vecN const &dataR, //!< Vector of radius data (m)
      vecN const &dataY  //!< Vector of y data (m)
    );

    //! Shell class constructor
    shell(
      size_t              size,           //!< Input ribs number
      hyperellipse const &hyperellipse_in //!< Input hyperellipse shape
    );

    //! Shell class constructor
    shell(
      size_t         size,      //!< Input ribs number
      polynom const &polynom_in //!< Input polynom shape
    );

    //! Reset shell size, position and stored contact results
    void
    reset(
      size_t size //!< Input ribs number
    );

    //! Get shell ribs number
    size_t
    size(void) const;

    /*\
     |                                   _
     |    __ _  ___  ___  _ __ ___   ___| |_ _ __ _   _
     |   / _` |/ _ \/ _ \| '_ ` _ \ / _ \ __| '__| | | |
     |  | (_| |  __/ (_) | | | | | |  __/ |_| |  | |_| |
     |   \__, |\___|\___/|_| |_| |_|\___|\__|_|   \__, |
     |   |___/                                    |___/
    \*/

    //! Get shell surface maximum radius (m)
    real
    surfaceMaxRadius(void) const;

    //! Get shell surface maximum width on y axis (m)
    real
    surfaceMaxWidth(void) const;

    //! Get shell surface minimum width (m)
    real
    surfaceWidthLowerBound(void) const;

    //! Get shell surface maximum width (m)
    real
    surfaceWidthUpperBound(void) const;

    //! Get shell surface width (m)
    real
    surfaceWidth(void) const;

    //! Get shell surface maximum width on reference (m)
    bool
    checkWidthBound(
      real y //!< Coordinate of y axis
    ) const;

    //! Get shell surface of revolution rib radius at y axis coordinate (m)
    real
    surfaceRadius(
      real y //!< Coordinate of y axis
    ) const;

    //! Get shell surface of revolution rib first derivative with respect to y coordinate
    real
    surfaceDerivative(
      real y,                         //!< Coordinate of y axis
      real tolerance = EPSILON_MEDIUM //!< Tolerance
    ) const;

    //! Get shell surface of revolution rib angle with respect to y axis (rad)
    real
    surfaceAngle(
      real y,                         //!< Coordinate of y axis
      real tolerance = EPSILON_MEDIUM //!< Tolerance
    ) const;

    //! Get i-th rib unloaded radius (m)
    real
    ribRadius(
      size_t i //!< Input index
    ) const;

    //! Get i-th rib unloaded radius (m)
    point
    ribCenter(
      size_t i //!< Input index
    ) const;

    //! Get rib width (m)
    real
    ribWidth(
      size_t i //!< Input index
    ) const;

    /*\
     |    __
     |   / _|_ __ __ _ _ __ ___   ___
     |  | |_| '__/ _` | '_ ` _ \ / _ \
     |  |  _| | | (_| | | | | | |  __/
     |  |_| |_|  \__,_|_| |_| |_|\___|
     |
    \*/

    //! Translate shell by vector
    void
    translate(
      vec3 const &vector_in //!< Translation vector
    );

    //! Returns shell translation vector
    vec3
    translation(void) const;

    //! Rotate shell by a rotation angle around an arbitrary axis
    void
    rotate(
      real        angle, //!< Input angle (rad)
      vec3 const &axis   //!< Input axis
    );

    //! Rotate shell by a rotation angle around an arbitrary axis
    void
    rotate(
      real               angle, //!< Input angle (rad)
      std::string const &axis   //!< Input axis
    );

    //! Returns shell rotation matrix
    mat3
    rotation(void) const;

    //! Returns shell linear matrix (rotation + scaling + shearing)
    mat3
    linear(void) const;

    //! Set 4x4 affine transformation matrix \n
    //! Warning: Rotation matrix must be orthonormal!
    void
    transform(
      affine const &matrix_in //!< Input 4x4 affine transformation matrix
    );

    //! Set 4x4 affine transformation matrix \n
    //! Warning: Rotation matrix must be orthonormal!
    void
    transform(
      mat4 const &matrix_in //!< Input 4x4 affine transformation matrix
    );

    //! Get 4x4 affine transformation matrix
    affine const &
    transformation(void) const;

    //! Get x vector
    vec3
    x(void) const;

    //! Get y vector
    vec3
    y(void) const;

    //! Get z vector
    vec3
    z(void) const;

    //! Get current Euler angles (rad) \n
    //! WARNING: Rotation sequence ZXY!
    void
    eulerAngles(
      vec3 &angles //!< Frame Euler angles
    ) const;

    /*\
     |   _
     |  | |__   _____  __
     |  | '_ \ / _ \ \/ /
     |  | |_) | (_) >  <
     |  |_.__/ \___/_/\_\
     |
    \*/

    //! Get shell bonding aabb as object pointer vector
    std::shared_ptr<aabb>
    bbox(void) const;

    //! Update shell bonding aabb
    void
    updateBBox(void);

    /*\
     |                   _             _
     |    ___ ___  _ __ | |_ __ _  ___| |_
     |   / __/ _ \| '_ \| __/ _` |/ __| __|
     |  | (_| (_) | | | | || (_| | (__| |_
     |   \___\___/|_| |_|\__\__,_|\___|\__|
     |
    \*/

    //! Get shell relative angles (rad) \n
    //! WARNING: Rotation sequence ZXY!
    void
    relativeAngles(
      vec3 &angles //!< Relative angles vector (rad)
    ) const;

    //! Get shell relative angles for the i-th rib (rad) \n
    //! WARNING: Rotation sequence ZXY!
    void
    relativeAngles(
      size_t i,     //!< Input i-th index
      vec3  &angles //!< Relative angles vector (rad)
    ) const;

    //! Get shell relative angles as vector (rad) \n
    //! WARNING: Rotation sequence ZXY!
    void
    relativeAngles(
      std::vector<vec3> &angles //!< Relative angles vector (rad)
    ) const;

    //! Get contact depth at center point (m) (projected on rib plane)
    void
    contactDepthRib(
      real &depth,     //!< Depth at center point [m/s]
      real &depth_dot, //!< Contact depth derivative [m/s]
      real  depth_old, //!< Previous time step Rho (m)
      real  time_step  //!< Time step [s]
    ) const;

    //! Get contact depth at center point for the i-th rib (m) (projected on rib plane)
    void
    contactDepthRib(
      size_t i,         //!< Input i-th index
      real  &depth,     //!< Depth at center point [m/s]
      real  &depth_dot, //!< Contact depth derivative [m/s]
      real   depth_old, //!< Previous time step Rho (m)
      real   time_step  //!< Time step [s]
    ) const;

    //! Get contact depth vector (m) and it time derivatives [m/s] (projected on rib plane)
    void
    contactDepthRib(
      vecN       &depth,     //!< Depth matrix [m/s]
      vecN       &depth_dot, //!< Contact depth derivative matrix [m/s]
      vecN const &depth_old, //!< Previous time step Rho matrix (m)
      real        time_step  //!< Time step [s]
    ) const;

    //! Get contact depth at center point (m) (projected on the mesh)
    void
    contactDepthMesh(
      real &depth,     //!< Depth at center point [m/s]
      real &depth_dot, //!< Contact depth derivative [m/s]
      real  depth_old, //!< Previous time step Rho (m)
      real  time_step  //!< Time step [s]
    ) const;

    //! Get contact depth at center point for the i-th rib (m) (projected on the mesh)
    void
    contactDepthMesh(
      size_t i,         //!< Input i-th index
      real  &depth,     //!< Depth at center point [m/s]
      real  &depth_dot, //!< Contact depth derivative [m/s]
      real   depth_old, //!< Previous time step Rho (m)
      real   time_step  //!< Time step [s]
    ) const;

    //! Get contact depth vector (m) and it time derivatives [m/s] (projected on the mesh)
    void
    contactDepthMesh(
      vecN       &depth,     //!< Depth matrix [m/s]
      vecN       &depth_dot, //!< Contact depth derivative matrix [m/s]
      vecN const &depth_old, //!< Previous time step Rho matrix (m)
      real        time_step  //!< Time step [s]
    ) const;

    //! Get contact normal vector
    void
    contactNormal(
      vec3 &normal //!< Contact point normal direction
    ) const;

    //! Get contact normal vector for the i-th rib
    void
    contactNormal(
      size_t i,     //!< Input i-th index
      vec3  &normal //!< Contact point normal direction
    ) const;

    //! Get contact normal vectors vector
    void
    contactNormal(
      std::vector<vec3> &normal //!< Contact point normal direction vector
    ) const;

    //! Get contact point (projected on rib plane)
    void
    contactPointRib(
      point &point //!< Contact point
    ) const;

    //! Get contact point (projected on rib plane)
    void
    contactPointRib(
      size_t i,    //!< Input i-th index
      point &point //!< Contact point
    ) const;

    //! Get contact points vector (projected on rib plane)
    void
    contactPointRib(
      std::vector<point> &point //!< Contact points vector
    ) const;

    //! Get contact point (projected on the mesh)
    void
    contactPointMesh(
      point &point //!< Contact point
    ) const;

    //! Get contact point (projected on the mesh)
    void
    contactPointMesh(
      size_t i,    //!< Input i-th index
      point &point //!< Contact point
    ) const;

    //! Get contact points vector (projected on the mesh)
    void
    contactPointMesh(
      std::vector<point> &point //!< Contact points vector
    ) const;

    //! Get contact point friction
    void
    contactFriction(
      real &friction //!< Contact friction coefficient
    ) const;

    //! Get contact point friction for the i-th rib
    void
    contactFriction(
      size_t i,       //!< Input i-th index
      real  &friction //!< Contact friction coefficient
    ) const;

    //! Get contact frictions vector
    void
    contactFriction(
      vecN &friction //! Contact friction coefficients vector
    ) const;

    //! Get contact point 4x4 affine transformation matrix (projected on rib plane)
    void
    contactPointRibAffine(
      affine &point_affine //!< Contact point affine transformation matrix
    ) const;

    //! Get contact point 4x4 affine transformation matrix for the i-th rib (projected on rib plane)
    void
    contactPointRibAffine(
      size_t  i,           //!< Input i-th index
      affine &point_affine //!< Contact point affine transformation matrix
    ) const;

    //! Get contact point 4x4 affine transformation matrices (projected on rib plane)
    void
    contactPointRibAffine(
      std::vector<affine> &point_affine //!< Contact point affine transformation matrices vector
    ) const;

    //! Get contact point 4x4 affine transformation matrix (projected on the mesh)
    void
    contactPointMeshAffine(
      affine &point_affine //!< Contact point affine transformation matrix
    ) const;

    //! Get contact point 4x4 affine transformation matrix for the i-th rib (projected on the mesh)
    void
    contactPointMeshAffine(
      size_t  i,           //!< Input i-th index
      affine &point_affine //!< Contact point affine transformation matrix
    ) const;

    //! Get contact point 4x4 affine transformation matrices (projected on the mesh)
    void
    contactPointMeshAffine(
      std::vector<affine> &point_affine //!< Contact point affine transformation matrices vector
    ) const;

    //! Update current shell position and find contact parameters (intersection with mesh)
    bool
    setup(
      ground::mesh const &ground,    //!< ENVE mesh object (ground)
      affine const       &matrix,    //!< 4x4 affine transformation matrix
      size_t              threshold, //!< Evaluations threshold number
      std::string const   method     //!< Method name (choose from: "triangle" or "line")
    );

    //! Update current shell position and find contact parameters (intersection with plane)
    bool
    setup(
      ground::flat const &ground, //!< ENVE flat object (ground)
      affine const       &matrix  //!< 4x4 affine transformation matrix
    );

    //! Print contact parameters
    void
    print(
      out_stream &os //!< Output stream type
    ) const;

  private:
    //! Perform one point sampling on a single triangle (line-triangle intersection)
    void
    oversample(
      size_t o, //!< Rib index to be filled by oversampled data
      size_t a, //!< Rib index to be used to oversample (smaller)
      size_t b  //!< Rib index to be used to oversample (bigger)
    );

    //! Perform one point sampling on a single triangle (line-triangle intersection)
    bool
    samplingSingleTriangle(
      triangleground::vecptr const &triangles_vec, //!< Triangles list (with only one element!)
      point const                  &origin,        //!< Line sampling origin  (shell local frame)
      vec3 const                   &direction,     //!< Line sampling direction (shell local frame)
      point                        &point,         //!< Intersection point
      vec3                         &normal,        //!< Intersected triangle normal
      real                         &friction       //!< Intersected triangle friction
    ) const;

    //! Perform one point sampling (line-triangle intersection)
    bool
    samplingPoint(
      triangleground::vecptr const &triangles_vec, //!< Triangles list
      point const                  &origin,        //!< Line sampling origin  (shell local frame)
      vec3 const                   &direction,     //!< Line sampling direction (shell local frame)
      point                        &point,         //!< Intersection point
      vec3                         &normal,        //!< Intersected triangle normal
      real                         &friction       //!< Intersected triangle friction
    ) const;

    //! Perform cross points sampling
    bool
    samplingCross(
      triangleground::vecptr const &triangles_vec, //!< Triangles list
      point const                  &origin,        //!< Line sampling origin  (shell local frame)
      vec3 const                   &direction,     //!< Line sampling direction (shell local frame)
      real                          delta_x,       //!< Delta y
      real                          delta_y,       //!< Delta x
      point                        &point,         //!< Local contact point
      vec3                         &normal,        //!< Local contact normal
      real                         &friction       //!< Local contact friction coefficient
    ) const;

    //! Evaluate i-th rib single triangle contact
    bool
    envelopSingleTriangle(
      triangleground::vecptr const &triangles_vec, //!< Triangles candidate list
      size_t                        i              //!< Rib index (i-th rib)
    );

    //! Evaluate i-th rib contact through lines intersection envelop model
    bool
    envelopLine(
      triangleground::vecptr const &triangles_vec, //!< Triangles candidate list
      size_t                        i              //!< Rib index (i-th rib)
    );

    //! Evaluate i-th rib contact through triangles intersection envelop model
    bool
    envelopTriangle(
      triangleground::vecptr const &triangles_vec, //!< Triangles candidate list
      size_t                        i              //!< Rib index (i-th rib)
    );

    //! Evaluate i-th rib contact through triangles intersection envelop model
    bool
    envelopPlane(
      ground::flat const &ground, //!< Local flat ground object
      size_t              i       //!< Rib index (i-th rib)
    );

  private:
    bool
    projectContactPointOnFlat(
      ground::flat const &ground,
      point const        &point_rib,
      vec3 const         &direction,
      size_t              i,
      point              &point_out)
      const;

    bool
    projectContactPointOnMesh(
      triangleground::vecptr const &triangles,
      point const                  &point_rib,
      vec3 const                   &direction,
      size_t                        i,
      point                        &point_out)
      const;

  }; // class shell

} // namespace enve

#endif

///
/// file: enve_shell.hh
///