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
/// file: sfun_types.h
///

#ifndef INCLUDE_SFUN_TYPES
#define INCLUDE_SFUN_TYPES

#include "sfun_settings.h"

// Structure containing the input of ENVE
typedef struct
{
  double hub_affine[16]; // Shell hub affine transformation matrix
} ShellAffine;

// Structure containing the output of ENVE
typedef struct
{
  double shell_affine[16];         // Shell contact point affine transformation matrix
  double shell_rho;                // Shell contact depth
  double shell_friction;           // Shell friction coefficient scaling factor
  double ribs_affine[16*MAX_RIBS]; // Ribs contact point affine transformation matrix
  double ribs_rho[MAX_RIBS];       // Ribs contact depth
  double ribs_friction[MAX_RIBS];  // Ribs friction coefficient scaling factor
  double in_mesh;                  // Flag to detect if the wheel is outside the ground mesh. (0: at least one wheel is out of ground, 1: every wheels are in the ground)
} GroundContact;

#endif

///
/// eof: sfun_types.h
///
