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
/// file: enve_sfun_types.h
///

#ifndef INCLUDE_ENVE_SFUN_TYPES_H
#define INCLUDE_ENVE_SFUN_TYPES_H

#ifndef ENVE_MAX_RIBS
#define ENVE_MAX_RIBS 20
#endif

// Typedefs for enve S-function double
typedef double EnveRealPar;

// Structure containing the input enve S-function bus
typedef struct
{
  EnveRealPar hub_affine[16]; // Shell hub affine transformation matrix
} EnveInputBus;

// Structure containing the output enve S-function bus
typedef struct
{
  EnveRealPar shell_affine[16];              // Shell contact point affine transformation matrix
  EnveRealPar shell_rho;                     // Shell contact depth
  EnveRealPar shell_friction;                // Shell friction coefficient scaling factor
  EnveRealPar ribs_affine[16*ENVE_MAX_RIBS]; // Ribs contact point affine transformation matrix
  EnveRealPar ribs_rho[ENVE_MAX_RIBS];       // Ribs contact depth
  EnveRealPar ribs_friction[ENVE_MAX_RIBS];  // Ribs friction coefficient scaling factor
  EnveRealPar in_mesh;                       // Flag to detect if the wheel is outside the ground mesh. (0: at least one wheel is out of ground, 1: every wheels are in the ground)
} EnveOutputBus;

#endif

///
/// eof: enve_sfun_types.h
///
