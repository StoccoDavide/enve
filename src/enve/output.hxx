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
/// file: output.hxx
///

#ifndef INCLUDE_ENVE_OUTPUT_HXX
#define INCLUDE_ENVE_OUTPUT_HXX

namespace enve
{

  /*\
   |               _               _   
   |    ___  _   _| |_ _ __  _   _| |_ 
   |   / _ \| | | | __| '_ \| | | | __|
   |  | (_) | |_| | |_| |_) | |_| | |_ 
   |   \___/ \__,_|\__| .__/ \__,_|\__|
   |                  |_|              
  \*/

  //! Output data class
  struct output {
    acme::point point    = NAN_POINT; //!< Output contact point
    acme::vec3  normal   = NAN_VEC3;  //!< Output contact normal
    acme::real  friction = QUIET_NAN; //!< Output contact friction
    acme::real  depth    = QUIET_NAN; //!< Output contact depth 
    acme::real  area     = QUIET_NAN; //!< Output contact area
    acme::real  volume   = QUIET_NAN; //!< Output contact volume
  }; // struct output

} // namespace enve

#endif

///
/// eof: output.hxx
///
