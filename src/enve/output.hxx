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

#ifndef INCLUDE_ENVE_OUTPUT
#define INCLUDE_ENVE_OUTPUT

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
    point point    = NAN_POINT; //!< Contact points vector
    vec3  normal   = NAN_VEC3;  //!< Contact normal unit vectors
    real  friction = QUIET_NAN; //!< Contact friction
    real  depth    = QUIET_NAN; //!< Contact depth 
    real  area     = QUIET_NAN; //!< Contact area
    real  volume   = QUIET_NAN; //!< Contact volume
  }; // struct output

} // namespace enve

#endif

///
/// eof: output.hxx
///
