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
      << "TEST 00 - ENVE SFUN TEST 0" << std::endl
      << std::endl;

    // Set environment variable
    setenv("ENVE_GROUND_PATH", "./files_rdf/sample.rdf", 1);

    // Set data for S-function entry point for initialization
    double size          = 10;  // Ribs number (-)
    double r_x           = 0.3; // Shell radius on x-axis (m)
    double m_x           = 4.0; // Shell curve degree for x-axis (-)
    double r_y           = 0.3; // Shell radius on y-axis (m)
    double m_y           = 4.0; // Shell curve degree for y-axis (-)
    double l_y           = 0.1; // Surface half width on y-axis (m)
    double flat_height   = 0.0; // Flat ground surface height (m)
    double flat_friction = 1.0; // Flat ground surface friction scaling coefficient (-)

    // S-function entry point for initialization
    sfun_init(
       &size,         // Ribs number (-)
       &r_x,          // Shell radius on x-axis (m)
       &m_x,          // Shell curve degree for x-axis (-)
       &r_y,          // Shell radius on y-axis (m)
       &m_y,          // Shell curve degree for y-axis (-)
       &l_y,          // Surface half width on y-axis (m)
       &flat_height,  // Flat ground surface height (m)
       &flat_friction // Flat ground surface friction scaling coefficient (-)
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
    pose2 = translate(1.0, 1.0, 0.5) * angleaxis(yaw_angle,    UNITZ_VEC3)
                                    * angleaxis(camber_angle, UNITX_VEC3)
                                    * angleaxis(pitch_angle,  UNITY_VEC3);
    ShellAffine input1, input2;
    for (int i = 0; i < 16; ++i)
    {
      input1.hub_affine[i] = *(pose1.data() + i);
      input2.hub_affine[i] = *(pose2.data() + i);
    }

    // Print inputs affines
    std::cout
      << "Input affines" << std::endl
      << pose1
      << pose2 << std::endl;
    std::cout
      << "Input arrays" << std::endl;
    for (int i = 0; i < 16; ++i)
      {std::cout << *(input1.hub_affine + i) << "  ";}
    std::cout << std::endl;
    for (int i = 0; i < 16; ++i)
      {std::cout << *(input2.hub_affine + i) << "  ";}

    // Output bus containing the contact data
    GroundContact output1, output2;

    double flat_enable = 0; // method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
    double method      = 0; // flat_enable 0: ENVE use ground::mesh (RDF), 1: ENVE use ground::flat

    // S-function entry point for step update
    sfun_out(
      &input1,      // Input bus containing the shell hub affine transformation matrix
      &output1,     // Output bus containing the contact data
      &method,     // method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
      &flat_enable // flat_enable 0: ENVE use ground::mesh, 1: ENVE use ground::flat
    );
    sfun_out(
      &input2,      // Input bus containing the shell hub affine transformation matrix
      &output2,     // Output bus containing the contact data
      &method,     // method 0: ENVE use geometric enveloping, 1: ENVE use sampling enveloping
      &flat_enable // flat_enable 0: ENVE use ground::mesh, 1: ENVE use ground::flat
    );

    // Output performance data
    std::cout
      << "ENVE S-FUN REPORT" << std::endl
      << output1.shell_affine
      << output2.shell_affine << std::endl;
  
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
/// eof: enve_test_sfun_00.cc
///
