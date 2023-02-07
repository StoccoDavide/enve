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
/// file: enve_timing_00.cc
///

#include "enve.hh"
#include "TicToc.hh"

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
      << "TEST 00 - ENVE MESH INTERSECTION" << std::endl
      << std::endl;

    // Instantiate a TicToc object
    TicToc tictoc;

    // Load .rdf File
    ground::mesh road("./files_rdf/sample.rdf");

    // Print OutMesh.txt file
    //road.print("bin/OutMesh.txt");

    // Initialize the tire shell
    shell tire_shell(
      10,    // ribs number
      0.327, // r_x
      4.000, // m_x
      0.195, // r_y
      4.000, // m_y
      0.188  // l_y
    );

    // Orient the tire in the space
    real yaw_angle    = 0.0 * PI;
    real camber_angle = 0.0 * PI;
    real pitch_angle  = 0.0 * PI;

    // Create frame object
    affine pose;
    pose = translate(2.0, 5.0, 0.25) * angleaxis(yaw_angle,     UNITZ_VEC3)
                                     * (angleaxis(camber_angle, UNITX_VEC3)
                                     * angleaxis(pitch_angle,   UNITY_VEC3));

    // Resize the tire shell
    tire_shell.resize(20);

    // Start chronometer
    tictoc.tic();

    // Set an orientation and calculate parameters
    bool out = tire_shell.setup(road, pose, "geometric");

    // Stop chronometer
    tictoc.toc();

    // Display current tire data on command line
    //if (out)
    //  tire_shell.print(std::cout);

    // Output performance data
    std::cout
      << "Execution time = " << tictoc.elapsed_ms() * 1000 << " us" << std::endl
      << std::endl
      << "Check the results..." << std::endl;

    // End of test
    std::cout
      << std::endl
      << "That's all Folks!" << std::endl
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
/// eof: enve_test_00.cc
///
