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
/// file: enve_test_02.cc
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
      << "TEST 02 - ENVE MESH INTERSECTION" << std::endl
      << std::endl;


    // Instantiate a TicToc object
    TicToc tictoc;

    // Initialize a quite big triangle
    point vertex[3];
    vertex[0] = point(0.0,    100.0, 0.0);
    vertex[1] = point(100.0,    0.0, 0.0);
    vertex[2] = point(0.0,   -100.0, 0.0);
    triangleground::vecptr triangle_prtVec;
    triangle_prtVec.push_back(
      triangleground::ptr(new triangleground(0, 1.0, vertex))
    );

    vertex[0] = point(0.0,    100.0, 0.0);
    vertex[1] = point(-100.0,   0.0, 0.0);
    vertex[2] = point(0.0,    -100.0, 0.0);
    triangle_prtVec.push_back(
      triangleground::ptr(new triangleground(0, 0.5, vertex))
    );

    // Build the mesh
    ground::mesh road(triangle_prtVec);

    // Initialize the tire shell
    shell tire_shell(
      5,      // n_r
      0.3130, // r_x
      9.0,    // m_x
      0.12,   // r_y
      6.0,    // m_y
      0.1     // l_y
    );

    // Orient the tire in the space
    real yaw_angle    = 0.0 * PI;
    real camber_angle = 0.0 * PI;
    real pitch_angle  = 0.0 * PI;

    // Create frame object
    affine pose;
    pose = translate(0.0, 0.0, 0.3) * angleaxis(yaw_angle,    UNITZ_VEC3)
                                    * angleaxis(camber_angle, UNITX_VEC3)
                                    * angleaxis(pitch_angle,  UNITY_VEC3);

    // Start chronometer
    tictoc.tic();

    // Set an orientation and calculate parameters
    tire_shell.setup(road, pose, "sampling");

    // Stop chronometer
    tictoc.toc();

    // Display current tire data on command line
    tire_shell.print(std::cout);

    affine cp_rib;
    for (size_t i = 0; i < tire_shell.size(); ++i)
    {
      tire_shell.contactPointAffine(i, cp_rib);
      std::cout
        << "Rib " << i << ":" << std::endl
        << cp_rib
        << std::endl;
    }

    // Output performance data
    std::cout
      << "Execution time = " << tictoc.elapsed_ms() * 1000 << " us" << std::endl
      << std::endl
      << "Check the results..." << std::endl;

    // End of test
    std::cout
      << std::endl
      << "TEST 02: Completed" << std::endl
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
/// eof: enve_test_02.cc
///
