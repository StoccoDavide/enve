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
 *    Matteo Larcher                                                   *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: matteo.larcher@unitn.it                                  *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: c.h
///

#ifndef INCLUDE_ENVE_SFUN_INTEREFACE_H
#define INCLUDE_ENVE_SFUN_INTEREFACE_H

#include "enve_sfun_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

  // S-function entry point for initialization
  void
  sfun_init(
    const double *size,         // Ribs number (-)
    const double *r_x,          // Shell radius on x-axis (m)
    const double *m_x,          // Shell curve degree for x-axis (-)
    const double *r_y,          // Shell radius on y-axis (m)
    const double *m_y,          // Shell curve degree for y-axis (-)
    const double *l_y,          // Surface half width on y-axis (m)
    const double *flat_height,  // Flat ground surface height (m)
    const double *flat_friction // Flat ground surface friction scaling coefficient (-)
  );

  // S-function entry point for step update
  void
  sfun_out(
    const ShellAffine *input,      // Input bus containing the shell hub affine transformation matrix
    GroundContact     *output,     // Output bus containing the contact data
    const double      *method,     // method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
    const double      *flat_enable // flat_enable 0: ENVE use ground::mesh, 1: ENVE use ground::flat
  );

  // S-function entry point for deletion of allocated memory
  void
  sfun_end(void);

#ifdef __cplusplus
}
#endif

#endif

///
/// eof: enve_sfun_interface.h
///
