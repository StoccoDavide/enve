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

// Structure containing the shape enve S-function bus
typedef struct
{
  EnveRealPar Rx; // Shell radius on x-axis (m)
  EnveRealPar Mx; // Shell curve degree for x-axis (-)
  EnveRealPar Ry; // Shell radius on y-axis (m)
  EnveRealPar My; // Shell curve degree for y-axis (-)
  EnveRealPar Ly; // Surface half width on y-axis (m)
} EnveShapeBus;

// Structure containing the input enve S-function bus
typedef struct
{
  EnveRealPar HubAffine[16]; // Shell hub affine transformation matrix
} EnveInputBus;

// Structure containing the output enve S-function bus
typedef struct
{
  EnveRealPar ShellAffine[16];              // Shell contact point affine transformation matrix
  EnveRealPar ShellRho;                     // Shell contact depth
  EnveRealPar ShellFriction;                // Shell friction coefficient scaling factor
  EnveRealPar RibsAffine[16*ENVE_MAX_RIBS]; // Ribs contact point affine transformation matrix
  EnveRealPar RibsRho[ENVE_MAX_RIBS];       // Ribs contact depth
  EnveRealPar RibsFriction[ENVE_MAX_RIBS];  // Ribs friction coefficient scaling factor
  EnveRealPar InMesh;                       // Flag to detect if the wheel is outside the ground mesh. (0: at least one wheel is out of ground, 1: every wheels are in the ground)
} EnveOutputBus;

#endif

///
/// eof: enve_sfun_types.h
///
