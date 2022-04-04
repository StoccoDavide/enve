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
/// file: enve_shell.hh
///

#pragma once

#ifndef INCLUDE_ENVE_SHELL
#define INCLUDE_ENVE_SHELL

#include <numeric>

#include <acme.hh>
#include <acme_aabb.hh>
#include <acme_point.hh>
#include <acme_segment.hh>
#include <acme_utils.hh>

#include "enve.hh"
#include "enve_flat.hh"
#include "enve_mesh.hh"
#include "enve_rib.hh"
#include "enve_shape.hh"
#include "enve_output.hh"

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

  //! Base class for ENVE shell
  class shell
  {
  public:
    typedef std::shared_ptr<shell const> ptr;    //!< Pointer to shell object
    typedef std::vector<shell::ptr>      vecptr; //!< Vector of pointers to shell objects

  private:
    affine                 m_affine; //!< Shell reference frame (ISO)
    std::vector<rib>       m_ribs;   //!< Shell ribs vector
    std::shared_ptr<shape> m_shape;  //!< Shell shape
    std::shared_ptr<aabb>  m_aabb;   //!< Shell bounding aabb (must be transformed in the mesh reference frame before intersection!)
    std::vector<output>    m_out;    //!< Contact parameters output vector

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
      size_t       size,    //!< Input ribs number
      shape const &shape_in //!< Input shape object
    );

    //! Resize shell size, position and stored contact results
    void
    resize(
      size_t size //!< Input ribs number
    );

    //! Get shell ribs number
    size_t
    size(void) const;

    /*\
     |       _
     |   ___| |__   __ _ _ __   ___
     |  / __| '_ \ / _` | '_ \ / _ \
     |  \__ \ | | | (_| | |_) |  __/
     |  |___/_| |_|\__,_| .__/ \___|
     |                  |_|
    \*/

    //! Get shell surface maximum radius (m)
    real
    surfaceMaxRadius(void) const;

    //! Get shell surface maximum width on y axis (m)
    real
    surfaceMaxWidth(void) const;

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

    //! Get rib angle (rad)
    real
    ribAngle(
      size_t i //!< Input index
    ) const;

    /*\
     |         __  __ _            
     |   __ _ / _|/ _(_)_ __   ___ 
     |  / _` | |_| |_| | '_ \ / _ \
     | | (_| |  _|  _| | | | |  __/
     |  \__,_|_| |_| |_|_| |_|\___|
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
      affine const &affine_in //!< Input 4x4 affine transformation matrix
    );

    //! Set 4x4 affine transformation matrix \n
    //! Warning: Rotation matrix must be orthonormal!
    void
    transform(
      mat4 const &affine_in //!< Input 4x4 affine transformation matrix
    );

    //! Get 4x4 affine transformation matrix
    affine const &
    transformation(void) const;

    //! Check if 4x4 affine transformation matrix is othornormal and right-handed
    bool
    checkTransformation(
      mat4 const &affine_in //!< Input 4x4 affine transformation matrix
    ) const;

    //! Check if 4x4 affine transformation matrix is othornormal and right-handed
    bool
    checkTransformation(
      affine const &affine_in //!< Input 4x4 affine transformation matrix
    ) const;

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
     |               _     _     
     |    __ _  __ _| |__ | |__  
     |   / _` |/ _` | '_ \| '_ \ 
     |  | (_| | (_| | |_) | |_) |
     |   \__,_|\__,_|_.__/|_.__/ 
     |                           
    \*/

    //! Get shell bonding aabb as object pointer vector
    std::shared_ptr<aabb>
    BBox(void) const;

    //! Update shell bonding aabb
    void
    updateBBox(void);

    /*\
     |            _               
     |   ___  ___| |_ _   _ _ __  
     |  / __|/ _ \ __| | | | '_ \ 
     |  \__ \  __/ |_| |_| | |_) |
     |  |___/\___|\__|\__,_| .__/ 
     |                     |_|    
    \*/

    //! Update current shell position and find contact parameters (intersection with mesh)
    bool
    setup(
      ground::mesh const &ground,    //!< ENVE mesh object (ground)
      affine       const &affine_in, //!< 4x4 affine transformation matrix
      std::string  const  method     //!< Method name (choose from: "geometric" or "sampling")
    );

    //! Update current shell position and find contact parameters (intersection with plane)
    bool
    setup(
      ground::flat const &ground,    //!< ENVE flat object (ground)
      affine       const &affine_in, //!< 4x4 affine transformation
      std::string  const  method     //!< Method name (choose from: "geometric" or "sampling")
    );

    /*\
     |                   _             _   
     |    ___ ___  _ __ | |_ __ _  ___| |_ 
     |   / __/ _ \| '_ \| __/ _` |/ __| __|
     |  | (_| (_) | | | | || (_| | (__| |_ 
     |   \___\___/|_| |_|\__\__,_|\___|\__|
     |                                     
    \*/

    //! Get contact point
    void
    contactPoint(
      point &point //!< Contact point
    ) const;

    //! Get contact point
    void
    contactPoint(
      size_t i,    //!< Input i-th index
      point &point //!< Contact point
    ) const;

    //! Get contact points vector
    void
    contactPoint(
      std::vector<point> &point //!< Contact points vector
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

    //! Get contact friction coefficient
    void
    contactFriction(
      real &friction //!< Contact friction coefficient
    ) const;

    //! Get i-th rib contact friction coefficient
    void
    contactFriction(
      size_t i,       //!< Input i-th index
      real  &friction //!< Contact friction coefficient
    ) const;

    //! Get contact friction coefficient vector
    void
    contactFriction(
      std::vector<real> &friction //! Contact friction coefficient vector
    ) const;

    //! Get contact depth at center point (m) (projected on rib plane)
    void
    contactDepth(
      real &depth //!< Contact depth
    ) const;

    //! Get contact depth at center point for the i-th rib (m) (projected on rib plane)
    void
    contactDepth(
      size_t i,    //!< Input i-th index
      real  &depth //!< Contact depth
    ) const;

    //! Get contact depth vector (m) (projected on rib plane)
    void
    contactDepth(
      std::vector<real> &depth //!< Contact depth
    ) const;

    //! Get contact area (m^2)
    void
    contactArea(
      real &area //!< Contact area
    ) const;

    //! Get i-th rib contact area (m^2)
    void
    contactArea(
      size_t i,    //!< Input i-th index
      real  &area //!< Contact area
    ) const;

    //! Get contact area vector (m^2)
    void
    contactArea(
      std::vector<real> &area //! Contact area vector
    ) const;

    //! Get contact volume (m^3)
    void
    contactVolume(
      real &volume //!< Contact volume
    ) const;

    //! Get i-th rib contact volume (m^3)
    void
    contactVolume(
      size_t i,    //!< Input i-th index
      real  &volume //!< Contact volume
    ) const;

    //! Get contact volume vector (m^3)
    void
    contactVolume(
      std::vector<real> &volume //! Contact volume vector
    ) const;

    //! Get contact point 4x4 affine transformation matrix
    void
    contactPointAffine(
      affine &point_affine //!< Contact point affine transformation matrix
    ) const;

    //! Get contact point 4x4 affine transformation matrix for the i-th rib
    void
    contactPointAffine(
      size_t  i,           //!< Input i-th index
      affine &point_affine //!< Contact point affine transformation matrix
    ) const;

    //! Get contact point 4x4 affine transformation matrices
    void
    contactPointAffine(
      std::vector<affine> &point_affine //!< Contact point affine transformation matrices vector
    ) const;

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

    //! Print contact parameters
    void
    print(
      out_stream &os //!< Output stream type
    ) const;

  }; // class shell

} // namespace enve

#endif

///
/// file: enve_shell.hh
///