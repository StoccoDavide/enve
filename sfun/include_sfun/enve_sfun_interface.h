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
/// file: enve_sfun_interface.h
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
  enve_sfun_init(
    const EnveRealPar *size,         // Ribs number (-)
    const EnveRealPar *r_x,          // Shell radius on x-axis (m)
    const EnveRealPar *m_x,          // Shell curve degree for x-axis (-)
    const EnveRealPar *r_y,          // Shell radius on y-axis (m)
    const EnveRealPar *m_y,          // Shell curve degree for y-axis (-)
    const EnveRealPar *l_y,          // Surface half width on y-axis (m)
    const EnveRealPar *flat_height,  // Flat ground surface height (m)
    const EnveRealPar *flat_friction // Flat ground surface friction scaling coefficient (-)
  );

  // S-function entry point for step update
  void
  enve_sfun_out(
    const EnveInputBus  *input,      // Input bus containing the shell hub affine transformation matrix
          EnveOutputBus *output,     // Output bus containing the contact data
    const EnveRealPar   *method,     // method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
    const EnveRealPar   *flat_enable // flat_enable 0: ENVE use ground::mesh, 1: ENVE use ground::flat
  );

  // S-function entry point for deletion of allocated memory
  void
  enve_sfun_end(void);

#ifdef __cplusplus
}
#endif

#endif

///
/// eof: enve_sfun_interface.h
///
