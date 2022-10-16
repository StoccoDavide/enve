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
/// file: triangleground.hxx
///

#ifndef INCLUDE_ENVE_TRIANGLEGROUND
#define INCLUDE_ENVE_TRIANGLEGROUND

namespace enve
{

  /*\
   |   _        _                   _                          _
   |  | |_ _ __(_) __ _ _ __   __ _| | ___ _ __ ___   __ _  __| |
   |  | __| '__| |/ _` | '_ \ / _` | |/ _ \ '__/ _ \ / _` |/ _` |
   |  | |_| |  | | (_| | | | | (_| | |  __/ | | (_) | (_| | (_| |
   |   \__|_|  |_|\__,_|_| |_|\__, |_|\___|_|  \___/ \__,_|\__,_|
   |                          |___/
  \*/

  //! Class container for the triangles for ground representation
  class triangleground : public triangle
  {
  public:
    typedef std::shared_ptr<triangleground const> ptr;    //!< Pointer to object
    typedef std::vector<triangleground::ptr>      vecptr; //!< Vector of pointers to objects

  private:
    integer m_id;       //!< ID (-)
    real    m_friction; //!< Friction coefficient scaling factor (-)
    vec3    m_normal;   //!< Unit normal (-)
    aabb    m_bbox;     //!< Axis-aligned bounding box (m)

  public:
    //! Triangleground copy constructor
    triangleground(triangleground const &) = delete;

    //! Triangleground move constructor
    triangleground(triangleground &&) = delete;

    //! Triangleground assignment operator    
    triangleground & operator=(const triangleground &) = delete;

    //! Triangleground move assignment operator    
    triangleground & operator=(triangleground &&) = delete;
    
    //! Triangleground class destructor
    ~triangleground(void) override = default;

    //! Triangleground class constructor
    triangleground(void);

    //! Triangleground class constructor
    triangleground(
      integer id,         //!< ID (-)
      real    friction,   //!< Friction coefficient scaling factor (-)
      real    vertex_0_x, //!< First vertex x-axis component (m)
      real    vertex_0_y, //!< First vertex y-axis component (m)
      real    vertex_0_z, //!< First vertex z-axis component (m)
      real    vertex_1_x, //!< Second vertex x-axis component (m)
      real    vertex_1_y, //!< Second vertex y-axis component (m)
      real    vertex_1_z, //!< Second vertex z-axis component (m)
      real    vertex_2_x, //!< Third vertex x-axis component (m)
      real    vertex_2_y, //!< Third vertex y-axis component (m)
      real    vertex_2_z  //!< Third vertex z-axis component (m)
    );

    //! Triangleground class constructor
    triangleground(
      integer         id,       //!< ID (-)
      real            friction, //!< Friction coefficient scaling factor (-)
      point   const & point_0,  //!< First vertex point (m)
      point   const & point_1,  //!< Second vertex point (m)
      point   const & point_2   //!< Third vertex point (m)
    );

    //! Triangleground class constructor
    triangleground(
      integer       id,       //!< ID (-)
      real          friction, //!< Friction coefficient scaling factor (-)
      point   const vertex[3] //!< Vertices points (m)
    );

    //! Copy triangleground object
    void
    copy(
      triangleground const & triangleground_obj //!< Input object
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      triangleground const & triangleground_obj,     //!< Input object
      real                   tolerance = EPSILON_LOW //!< Tolerance
    ) const;

    //! Get ID const reference (-)
    integer const &
    id(void)
    const;

    //! Get friction coefficent scaling factor const reference (-)
    real const &
    friction(void)
    const;

    //! Get axis-aligned bounding box const reference (m)
    aabb const &
    bbox(void)
    const;

    //! Get unit normal const reference (-)
    vec3 const &
    normal(void)
    const;

    //! Get i-th vertex const reference (m)
    point const &
    operator[](
      size_t i //!< Index
    ) const;

    //! Get i-th vertex const reference (m)
    point const &
    vertex(
      size_t i //!< Index
    ) const;

    //! Print data
    void
    print(
      out_stream & os //!< Output stream
    ) const;

  private:
    //! Update unit normal vector with positive z-axis component
    void
    updateNormal(void);

    //! Update axis-aligned bounding box
    void
    updateBbox(void);

    //! Get i-th vertex reference (m)
    point &
    operator[](
      size_t i //!< Index
    );

    //! Get i-th vertex reference (m)
    point &
    vertex(
      size_t i //!< Index
    );

  }; // class triangleground

} // namespace enve

#endif

///
/// eof: triangleground.hxx
///
