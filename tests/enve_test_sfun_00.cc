/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * The ENVE project                                                    *
 *                                                                     *
 * Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *
 *                                                                     *
 * The ENVE project and its components are supplied under the terms of *
 * the open source BSD 3-Clause License. The contents of the ENVE      *
 * project and its components may not be copied or disclosed except in *
 * accordance with the terms of the BSD 3-Clause License.              *
 *                                                                     *
 * URL: https://opensource.org/licenses/BSD-3-Clause                   *
 *                                                                     *
 *    Davide Stocco                                                    *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: davide.stocco@unitn.it                                   *
 *                                                                     *
 *    Enrico Bertolazzi                                                *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: enrico.bertolazzi@unitn.it                               *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: enve_test_sfun_00.cc
///

#include "enve.hh"
#include "enve_sfun_interface.h"

using namespace acme;
using namespace enve;

// Main function
int
main(void)
{
  // Try block
  try
  {

    // Print test main information
    std::cout
      << "---------------------------" << std::endl
      << "TEST SFUN 00 - ENVE SFUN TEST 0" << std::endl
      << std::endl;

    // Set environment variable
    setenv("ENVE_GROUND_PATH", "./files_rdf/sample.rdf", 1);

    // Set data for S-function entry point for initialization
    EnveRealPar SizePar = 10;  // Ribs number (-)
    EnveRealPar Rx = 0.3; // Shell radius on x-axis (m)
    EnveRealPar Mx = 6.0; // Shell curve degree for x-axis (-)
    EnveRealPar Ry = 0.3; // Shell radius on y-axis (m)
    EnveRealPar My = 6.0; // Shell curve degree for y-axis (-)
    EnveRealPar Ly = 0.1; // Surface half width on y-axis (m)
    EnveRealPar FlatHeightPar   = 0.0; // Flat ground surface height (m)
    EnveRealPar FlatFrictionPar = 1.0; // Flat ground surface friction scaling coefficient (-)

    // S-function entry point for initialization
    enve_sfun_init(
       &SizePar,        // Ribs number (-)
       &Rx,             // Shell radius on x-axis (m)
       &Mx,             // Shell curve degree for x-axis (-)
       &Ry,             // Shell radius on y-axis (m)
       &My,             // Shell curve degree for y-axis (-)
       &Ly,             // Surface half width on y-axis (m)
       &FlatHeightPar,  // Flat ground surface height (m)
       &FlatFrictionPar // Flat ground surface friction scaling coefficient (-)
    );

    // Set data for S-function entry point for step update

    // Input bus containing the shell hub affine transformation matrix
    real yaw_angle    = 0.0 * PI;
    real camber_angle = 0.0 * PI;
    real pitch_angle  = 0.0 * PI;
    affine pose1, pose2;
    pose1 = translate(1.0, 1.0, 0.8) * angleaxis(yaw_angle,    UNITZ_VEC3)
                                     * angleaxis(camber_angle, UNITX_VEC3)
                                     * angleaxis(pitch_angle,  UNITY_VEC3);
    pose2 = translate(1.0, 1.0, 0.2) * angleaxis(yaw_angle,    UNITZ_VEC3)
                                     * angleaxis(camber_angle, UNITX_VEC3)
                                     * angleaxis(pitch_angle,  UNITY_VEC3);
    EnveInputBus input1, input2;
    for (integer i = 0; i < 16; ++i)
    {
      input1.HubAffine[i] = *(pose1.data() + i);
      input2.HubAffine[i] = *(pose2.data() + i);
    }

    // Print inputs affines
    std::cout
      << "Input affines" << std::endl
      << pose1
      << pose2 << std::endl;
    std::cout
      << "Input arrays" << std::endl
      << "Array = [ ";
    for (integer i = 0; i < 16; ++i)
      {std::cout << *(input1.HubAffine + i) << ", ";}
    std::cout
      << "\b\b ]"
      << std::endl
      << "Array = [ ";
    for (int i = 0; i < 16; ++i)
      {std::cout << *(input2.HubAffine + i) << ", ";}
    std::cout << "\b\b ]" << std::endl;

    // Output bus containing the contact data
    EnveOutputBus output1, output2;

    EnveRealPar flat_enable = 0; // method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
    EnveRealPar method      = 0; // flat_enable 0: ENVE use ground::mesh (RDF), 1: ENVE use ground::flat

    // S-function entry point for step update
    enve_sfun_out(
      &input1,     // Input bus containing the shell hub affine transformation matrix
      &output1,    // Output bus containing the contact data
      &method,     // method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
      &flat_enable // flat_enable 0: ENVE use ground::mesh, 1: ENVE use ground::flat
    );
    enve_sfun_out(
      &input2,     // Input bus containing the shell hub affine transformation matrix
      &output2,    // Output bus containing the contact data
      &method,     // method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
      &flat_enable // flat_enable 0: ENVE use ground::mesh, 1: ENVE use ground::flat
    );

    // Output performance data
    std::cout
      << std::endl
      << "Output affines" << std::endl
      << "output1.in_mesh = " << output1.InMesh << std::endl
      << "output2.in_mesh = " << output2.InMesh << std::endl
      << "Array = [ ";
    for (integer i = 0; i < 16; ++i)
      {std::cout << *(output1.ShellAffine + i) << ", ";}
    std::cout
      << "\b\b ]"
      << std::endl
      << "Array = [ ";
    for (integer i = 0; i < 16; ++i)
      {std::cout << *(output2.ShellAffine + i) << ", ";}
    std::cout << "\b\b ]" << std::endl
      << std::endl;

    affine pose3, pose4;
    for (integer i = 0; i < 16; ++i)
    {
      pose3.matrix() = Eigen::Map<mat4>(output1.ShellAffine, 4, 4);
      pose4.matrix() = Eigen::Map<mat4>(output2.ShellAffine, 4, 4);
    }
    std::cout
      << "Output affines" << std::endl
      << pose3
      << pose4 << std::endl;

    // End of test
    std::cout
      << std::endl
      << "TEST SFUN 00: Completed" << std::endl
      << "---------------------------" << std::endl;

    // Exit the program
    return 0;
  }

  // Exception catch block
  catch (std::exception const &exc)
  {
    std::cerr << exc.what() << std::endl;
  }

  // Default catch block
  catch (...)
  {
    std::cerr
      << std::endl
      << "Aborted test: unknown error" << std::endl
      << "---------------------------" << std::endl;
  }
}

///
/// eof: enve_test_sfun_00.cc
///
