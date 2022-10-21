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
/// file: enve_sfun_interface.cc
///

#include "enve_sfun_interface.h"
#include "enve_sfun_wrapper.hh"

#ifdef __cplusplus
extern "C"
{
#endif

  void *ground_ptr;
  void *shell_ptr;

  void
  sfun_init(
    const double *size,
    const double *r_x,
    const double *m_x,
    const double *r_y,
    const double *m_y,
    const double *l_y,
    const double *flat_height,
    const double *flat_friction
  )
  {
    #define CMD "enve::sfun_init(...): "

    // Load environment variable
    char *envar_ground_path = getenv("ENVE_GROUND_PATH");
    if (envar_ground_path == NULL)
      {ENVE_ERROR(CMD "environment variable ENVE_GROUND_PATH does not exist.");}
    std::string ground_path(reinterpret_cast<char const *>(envar_ground_path));
    std::cout << "ENVE_GROUND_PATH: " << ground_path << std::endl;

    // Load mesh
    std::string extension      = ground_path.substr(ground_path.size() - 4, 4);
    enve::ground::mesh *ground = nullptr;
    if (extension == ".rdf")
      {ground = new enve::ground::mesh(ground_path);}
    else if (extension == ".obj")
      {ground = new enve::ground::mesh(ground_path, 1.0);}
    else
      {ENVE_ERROR(CMD "not a *.rdf or *.obj file.");}

    // Build shell
    ShellVehicle *shell = new ShellVehicle();
    shell->init(size, r_x, m_x, r_y, m_y, l_y, flat_height, flat_friction);

    // Store pointers
    ground_ptr = static_cast<void *>(ground);
    shell_ptr  = static_cast<void *>(shell);
  }

  void
  sfun_out(
    const ShellAffine *input,
    GroundContact     *output,
    const double      *method,
    const double      *flat_enable
  )
  {
    enve::ground::mesh *ground = static_cast<enve::ground::mesh *>(ground_ptr);
    ShellVehicle       *shell  = static_cast<ShellVehicle *>(shell_ptr);
    output->in_mesh = shell->out(
      ground,
      input->hub_affine,
      method,
      output->shell_affine,
      output->shell_rho,
      output->shell_friction,
      output->ribs_affine,
      output->ribs_rho,
      output->ribs_friction,
      flat_enable
    );
  }

  void
  sfun_end(void)
  {
    delete static_cast<enve::ground::mesh *>(ground_ptr);
    delete static_cast<ShellVehicle *>(shell_ptr);
  }

#ifdef __cplusplus
}
#endif

///
/// eof: enve_sfun_interface.cc
///
