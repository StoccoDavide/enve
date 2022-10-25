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
/// file: flat.hxx
///

#ifndef INCLUDE_ENVE_FLAT_HXX
#define INCLUDE_ENVE_FLAT_HXX

namespace enve
{

  namespace ground
  {

    /*\
     |    __ _       _
     |   / _| | __ _| |_
     |  | |_| |/ _` | __|
     |  |  _| | (_| | |_
     |  |_| |_|\__,_|\__|
     |
    \*/

    //! Triangular flat class
    class flat : public plane
    {
    private:
      real m_friction; //!< Friction coefficient scaling factor

    public:
      //! Flat copy constructor
      flat(flat const &) = delete;

      //! Flat move constructor
      flat(flat &&) = delete;

      //! Flat assignment operator    
      flat & operator=(const flat &) = delete;

      //! Flat move assignment operator    
      flat & operator=(flat &&) = delete;
      
      //! Flat class destructor
      ~flat(void) override = default;

      //! Flat class constructor
      flat(void);

      //! Flat class constructor
      flat(
        real friction, //!< Friction coefficient scaling factor
        real origin_x, //!< Input x value of ground plane origin point
        real origin_y, //!< Input y value of ground plane origin point
        real origin_z, //!< Input z value of ground plane origin point
        real normal_x, //!< Input x value of ground plane normal vector
        real normal_y, //!< Input y value of ground plane normal vector
        real normal_z  //!< Input z value of ground plane normal vector
      );

      //! Flat class constructor
      flat(
        real          friction, //!< Friction coefficient scaling factor
        point const & origin,   //!< Input plane origin point
        vec3  const & normal    //!< Input plane normal vector
      );

      //! Flat class constructor
      flat(
        real          friction, //!< Friction coefficient scaling factor
        plane const & plane_obj //!< Input flat object
      );

      //! Copy flat object
      void
      copy(
        flat const & flat_obj //!< Flat object to be copied
      );

      //! Check if objects are (almost) equal
      bool
      isApprox(
        flat const & flat_obj,               //!< Input flat object
        real         tolerance = EPSILON_LOW //!< Tolerance
      ) const;

      //! Get friction coefficent scaling factor const reference
      real const &
      friction(void)
      const;

      //! Set friction coefficent scaling factor reference
      real &
      friction(void);

      //! Get laying plane
      plane const &
      layingPlane(void)
      const;

      //! Set laying plane
      plane &
      layingPlane(void);

      //! Print data
      void
      print(
        out_stream & os //!< Output stream
      ) const;
    };

  } // namespace ground

} // namespace enve

#endif

///
/// eof: flat.hxx
///
