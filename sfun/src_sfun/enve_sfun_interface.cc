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

  void *MeshPtr;
  void *FlatPtr;
  void *ShellPtr;

  void
  enve_sfun_init(
    const EnveRealPar *SizePar,
    const EnveRealPar *RxPar,
    const EnveRealPar *MxPar,
    const EnveRealPar *RyPar,
    const EnveRealPar *MyPar,
    const EnveRealPar *LyPar,
    const EnveRealPar *FlatHeightPar,
    const EnveRealPar *FlatFrictionPar 
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
      *FlatFrictionPar, acme::point(0.0, 0.0, *FlatHeightPar), acme::vec3(0.0, 0.0, 1.0)
    );
    
    // Build shell
    enve::shell *shell = new enve::shell(
      *SizePar, *RxPar, *MxPar, *RyPar, *MyPar, *LyPar
    );

    // Store pointers
    MeshPtr  = static_cast<void *>(mesh);
    FlatPtr  = static_cast<void *>(flat);
    ShellPtr = static_cast<void *>(shell);

    #undef CMD
  }

  void
  enve_sfun_out(
    const EnveInputBus  *InputBus,
          EnveOutputBus *OutputBus,
    const EnveRealPar   *method,
    const EnveRealPar   *FlatEnablePar
  )
  {
    #define CMD "enve_sfun_out(...): "

    enve::ground::mesh *mesh  = static_cast<enve::ground::mesh *>(MeshPtr);
    enve::ground::flat *flat  = static_cast<enve::ground::flat *>(FlatPtr);
    enve::shell        *shell = static_cast<enve::shell *>(ShellPtr);

    // Store temporaries
    int size = shell->size();

    // Copy InputBus shell hub reference frame
    acme::affine tmp_affine;
    for (int r = 0; r < 4; ++r)
    {
      for (int c = 0; c < 4; ++c)
      {
        (tmp_affine.matrix())(r,c) = InputBus->HubAffine[r+4*c];
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
    if (*FlatEnablePar != 0)
    {
      shell->setup(*flat, tmp_affine, method_in);
      OutputBus->InMesh = true;
    }
    else
    {
      // Update and check if shell is in mesh
      OutputBus->InMesh = shell->setup(*mesh, tmp_affine, method_in);

      // If no elements are detected under the tire shadows 'in_mesh = 0'
      // and a setup with the back-up plane is called
      if (!OutputBus->InMesh)
        {shell->setup(*flat, tmp_affine, method_in);}
    }

    // Update shell OutputBuss
    shell->contactPointAffine(tmp_affine);
    shell->contactDepth(OutputBus->ShellRho);
    shell->contactFriction(OutputBus->ShellFriction);

    for (int r = 0; r < 4; ++r)
    {
      for (int c = 0; c < 4; ++c)
      {
        OutputBus->ShellAffine[r+4*c] = (tmp_affine.matrix())(r,c);
      }
    }

    // Update ribs OutputBuss
    for (int i = 0; i < ENVE_MAX_RIBS; ++i)
    {
      if (i < size)
      {
        shell->contactPointAffine(i, tmp_affine);
        shell->contactDepth(i, OutputBus->RibsRho[i]);
        shell->contactFriction(i, OutputBus->RibsFriction[i]);
        for (int r = 0; r < 4; ++r)
        {
          for (int c = 0; c < 4; ++c)
          {
            OutputBus->RibsAffine[r+4*c+16*i] = (tmp_affine.matrix())(r,c);
          }
        }
      }
      else
      {
        tmp_affine.matrix() = acme::NAN_MAT4;
        OutputBus->RibsRho[i]         = acme::QUIET_NAN;
        OutputBus->RibsFriction[i]    = acme::QUIET_NAN;
        for (int r = 0; r < 4; ++r)
        {
          for (int c = 0; c < 4; ++c)
          {
            OutputBus->RibsAffine[r+4*c+16*i] = (tmp_affine.matrix())(r,c);
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

    //delete static_cast<enve::ground::mesh *>(MeshPtr);
    //delete static_cast<enve::ground::flat *>(FlatPtr);
    //delete static_cast<enve::flat *>(ShellPtr);

    #undef CMD
  }

#ifdef __cplusplus
}
#endif

///
/// eof: enve_sfun_interface.cc
///
