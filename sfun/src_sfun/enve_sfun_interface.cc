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
#include "enve.hh"

#ifdef __cplusplus
extern "C"
{
#endif

  void *mesh_ptr;
  void *flat_ptr;
  void *shell_ptr;

  void
  enve_sfun_init(
    const EnveRealPar *size,
    const EnveRealPar *r_x,
    const EnveRealPar *m_x,
    const EnveRealPar *r_y,
    const EnveRealPar *m_y,
    const EnveRealPar *l_y,
    const EnveRealPar *flat_height,
    const EnveRealPar *flat_friction
  )
  {
    #define CMD "enve_sfun_init(...): "

    // Get environment variable
    char *mesh_path_env = getenv("ENVE_GROUND_PATH");
    if (mesh_path_env == NULL)
      {ENVE_ERROR(CMD "environment variable ENVE_GROUND_PATH does not exist.");}
    std::string mesh_path(mesh_path_env);
    std::cout << "ENVE_GROUND_PATH: " << mesh_path << std::endl;

    // Build mesh
    std::string extension = mesh_path.substr(mesh_path.size() - 4, 4);
    enve::ground::mesh *mesh = nullptr;
    if (extension == ".rdf")
      {mesh = new enve::ground::mesh(mesh_path);}
    else if (extension == ".obj")
      {mesh = new enve::ground::mesh(mesh_path, 1.0);}
    else
      {ENVE_ERROR(CMD "not a *.rdf or *.obj file.");}

    // Build flat
    enve::ground::flat *flat = new enve::ground::flat(
      *flat_friction, acme::point(0.0, 0.0, *flat_height), acme::vec3(0.0, 0.0, 1.0)
    );
    
    // Build shell
    enve::shell *shell = new enve::shell(
      *size, *r_x, *m_x, *r_y, *m_y, *l_y
    );

    // Store pointers
    mesh_ptr  = static_cast<void *>(mesh);
    flat_ptr  = static_cast<void *>(flat);
    shell_ptr = static_cast<void *>(shell);

    #undef CMD
  }

  void
  enve_sfun_out(
    const EnveInputBus  *input,
          EnveOutputBus *output,
    const EnveRealPar   *method,
    const EnveRealPar   *flat_enable
  )
  {
    #define CMD "enve_sfun_out(...): "

    enve::ground::mesh *mesh  = static_cast<enve::ground::mesh *>(mesh_ptr);
    enve::ground::flat *flat  = static_cast<enve::ground::flat *>(flat_ptr);
    enve::shell        *shell = static_cast<enve::shell *>(shell_ptr);

    // Store temporaries
    int size = shell->size();

    // Copy input shell hub reference frame
    acme::affine tmp_affine;
    for (int r = 0; r < 4; ++r)
    {
      for (int c = 0; c < 4; ++c)
      {
        (tmp_affine.matrix())(r,c) = input->hub_affine[r+4*c];
      }
    }

    // Extract enveloping method
    std::string method_in;
    if (*method == 0)
      {method_in = "geometric";}
    else if (*method == 1)
      {method_in = "sampling";}
    else
      {ENVE_ERROR(CMD "not a ''geometric'' or ''sampling'' method.")}

    // Use back-up plane for setup routine
    if (*flat_enable != 0)
    {
      shell->setup(*flat, tmp_affine, method_in);
      output->in_mesh = true;
    }
    else
    {
      // Update and check if shell is in mesh
      output->in_mesh = shell->setup(*mesh, tmp_affine, method_in);

      // If no elements are detected under the tire shadows 'in_mesh = 0'
      // and a setup with the back-up plane is called
      if (!output->in_mesh)
        {shell->setup(*flat, tmp_affine, method_in);}
    }

    // Update shell outputs
    shell->contactPointAffine(tmp_affine);
    shell->contactDepth(output->shell_rho);
    shell->contactFriction(output->shell_friction);

    for (int r = 0; r < 4; ++r)
    {
      for (int c = 0; c < 4; ++c)
      {
        output->shell_affine[r+4*c] = (tmp_affine.matrix())(r,c);
      }
    }

    // Update ribs outputs
    for (int i = 0; i < ENVE_MAX_RIBS; ++i)
    {
      if (i < size)
      {
        shell->contactPointAffine(i, tmp_affine);
        shell->contactDepth(i, output->ribs_rho[i]);
        shell->contactFriction(i, output->ribs_friction[i]);
        for (int r = 0; r < 4; ++r)
        {
          for (int c = 0; c < 4; ++c)
          {
            output->ribs_affine[r+4*c+16*i] = (tmp_affine.matrix())(r,c);
          }
        }
      }
      else
      {
        tmp_affine.matrix() = acme::NAN_MAT4;
        output->ribs_rho[i]         = acme::QUIET_NAN;
        output->ribs_friction[i]    = acme::QUIET_NAN;
        for (int r = 0; r < 4; ++r)
        {
          for (int c = 0; c < 4; ++c)
          {
            output->ribs_affine[r+4*c+16*i] = (tmp_affine.matrix())(r,c);
          }
        }
      }
    }

    #undef CMD
  }

  void
  enve_sfun_end(void)
  {
    #define CMD "enve_sfun_end(...): "

    //delete static_cast<enve::mesh::mesh *>(mesh_ptr);
    //delete static_cast<enve::mesh::flat *>(flat_ptr);
    //delete static_cast<enve::flat *>(shell_ptr);

    #undef CMD
  }

#ifdef __cplusplus
}
#endif

///
/// eof: enve_sfun_interface.cc
///
