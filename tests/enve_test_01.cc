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
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: enve_test_01.cc
///

#include "enve.hh"

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
      << "TEST 03 - ENVE MESH INTERSECTION" << std::endl
      << std::endl;


    // Instantiate a TicToc object
    Utils::TicToc tictoc;

    // Load .rdf File
    ground::mesh road("./files_rdf/LakeTown.rdf");

    // Print OutMesh.txt file
    //road.print("bin/OutMesh.txt");

    // Initialize the tire shell
    shell tire_shell(
      10,    // n_r
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
    pose = translate(45.0, 175.6, 0.26) * angleaxis(yaw_angle,    UNITZ_VEC3)
                                        * angleaxis(camber_angle, UNITX_VEC3)
                                        * angleaxis(pitch_angle,  UNITY_VEC3);
    // Start chronometer
    tictoc.tic();

    // Set an orientation and calculate parameters
    bool out = tire_shell.setup(road, pose, "geometric");

    // Stop chronometer
    tictoc.toc();

    // Display current tire data on command line
    if (out)
      tire_shell.print(std::cout);

    //affine cp_rib;
    //for (size_t i = 0; i < tire_shell.size(); ++i)
    //{
    //  tire_shell.contactPointAffine(i, cp_rib);
    //  std::cout
    //    << "Rib " << i << ":" << std::endl
    //    << cp_rib
    //    << std::endl;
    //}

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
/// eof: enve_test_01.cc
///
