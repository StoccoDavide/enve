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
/// file: sfun_shell_vehicle.hh
///

#ifndef INCLUDE_SFUN_SHELL_VEHICLE
#define INCLUDE_SFUN_SHELL_VEHICLE

#include "enve.hh"
#include "sfun_settings.h"

class ShellVehicle
{
private:
  enve::shell        * m_shell; // Shell object pointer
  enve::ground::flat   m_flat;  // Flat object

public:
  // Default class constructor
  ShellVehicle(void);

  // Function initializes shell and back-up virtual plane
  void
  init(
    const double *size,         // Ribs number
    const double *r_x,          // Shell radius on x-axis (m)
    const double *m_x,          // Shell curve degree for x axis
    const double *r_y,          // Shell radius on y-axis (m)
    const double *m_y,          // Shell curve degree for y-axis
    const double *l_y,          // Surface half width on y-axis (m)
    const double *flat_height,  // Back-up flat ground height (m)
    const double *flat_friction // Back-up flat ground friction scaling coefficient (-)
  );

  // Function outputs the computation of enve::shell routines, including logic for out-mesh conditions
  bool
  out(
    enve::ground::mesh *ground,                    // Ground object
    const double      (&hub_affine)[16],           // Shell hub reference frame
    const double       *method,                    // Enveloping method = 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
    double            (&shell_affine)[16],         // Shell contact point reference frame
    double             &shell_rho,                 // Shell contacth depth (m)
    double             &shell_friction,            // Shell scaling friction coefficient (-)
    double            (&ribs_affine)[16*MAX_RIBS], // Ribs contact point reference frames
    double            (&ribs_rho)[MAX_RIBS],       // Ribs contact depths (m)
    double            (&ribs_friction)[MAX_RIBS],  // Ribs scaling friction coefficient (-)
    const double       *flat_enable                // Back-up plane enable = 0: use enve::ground::mesh (RDF), 1: use enve::ground::flat
  );

};

#endif

///
/// eof: sfun_shell_vehicle.hh
///
