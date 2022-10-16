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
/// file: shape.hxx
///

#ifndef INCLUDE_ENVE_SHAPE
#define INCLUDE_ENVE_SHAPE

namespace enve
{

  /*\
   |       _
   |   ___| |__   __ _ _ __   ___
   |  / __| '_ \ / _` | '_ \ / _ \
   |  \__ \ | | | (_| | |_) |  __/
   |  |___/_| |_|\__,_| .__/ \___|
   |                  |_|
  \*/

  //! Shell surface geometry
  class shape
  {
  public:
    typedef std::shared_ptr<shape const> ptr;    //!< Pointer to shape object
    typedef std::vector<shape::ptr>      vecptr; //!< Vector of pointers to shape objects

  private:
    real m_r_x; //!< Section radius on x axis (m)
    real m_m_x; //!< Section curve degree for x axis (-)
    real m_r_y; //!< Section radius on y axis (m)
    real m_m_y; //!< Section curve degree for y axis (-)
    real m_l_y; //!< Section surface effective half width (m)

  public:
    //! Shape copy constructor
    shape(shape const &) = default;

    //! Shape move constructor
    shape(shape &&) = default;

    //! Shape assignment operator    
    shape & operator=(const shape &) = delete;

    //! Shape move assignment operator    
    shape & operator=(shape &&) = delete;
    
    //! Shape class destructor
    ~shape(void) = default;

    //! Shape class constructor
    shape(void);

    //! Shape class constructor
    shape(
      real r_x, //!< Surface radius on x axis (m)
      real m_x, //!< Surface curve degree for x axis
      real r_y, //!< Surface radius on y axis (m)
      real m_y, //!< Surface curve degree for y axis
      real l_y  //!< Surface half width on y axis (m)
    );

    //! Copy shape object
    void
    copy(
      shape const & shape_obj //!< Shape object to be copied
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      shape const & shape_obj,               //!< Input object
      real          tolerance = EPSILON_LOW //!< Tolerance
    ) const;

    //! Get shape radius on x axis const reference (m)
    real const &
    Rx(void)
    const;

    //! Get shape curve degree for x axis const reference
    real const &
    Mx(void)
    const;

    //! Get shape radius on y axis const reference (m)
    real const &
    Ry(void)
    const;

    //! Get shape curve degree for y axis const reference
    real const &
    My(void)
    const;

    //! Get shape half width on y axis const reference (m)
    real const &
    Ly(void)
    const;

    //! Get shape radius on x axis reference (m)
    real &
    Rx(void);

    //! Get shape curve degree for x axis reference
    real &
    Mx(void);

    //! Get shape radius on y axis reference (m)
    real &
    Ry(void);

    //! Get shape curve degree for y axis reference
    real &
    My(void);

    //! Get shape surface half width on y axis reference (m)
    real &
    Ly(void);

    //! Get surface maximum radius const reference (m)
    real const &
    surfaceMaxRadius(void)
    const;

    //! Get surface maximum width const reference (m)
    real const &
    surfaceMaxWidth(void)
    const;

    //! Get surface maximum width on reference (m)
    bool
    checkWidthBound(
      real y //!< Coordinate of y axis
    ) const;

    real
    surfaceRadius(
      real y //!< Coordinate of y axis
    ) const;

    //! Get surface width (m)
    real const &
    surfaceWidth(void)
    const;

    //! Get surface of revolution rib first derivative with respect to y coordinate
    real
    surfaceDerivative(
      real y,                         //!< Coordinate of y axis
      real tolerance = EPSILON_MEDIUM //!< Tolerance
    ) const;

    //! Get surface of revolution rib angle with respect to y axis (rad)
    real
    surfaceAngle(
      real y,                         //!< Coordinate of y axis
      real tolerance = EPSILON_MEDIUM //!< Tolerance
    ) const;

    //! Print shape data
    void
    print(
      out_stream & os //!< Output stream type
    ) const;

  }; // class shape

} // namespace enve

#endif

///
/// eof: shape.hxx
///
