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
/// file: enve_timing_00.cc
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
      << "TIMING 00 - ENVE TIMING 0" << std::endl
      << std::endl;

    // Instantiate a TicToc object
    Utils::TicToc tictoc;

    // Load *.rdf File
    ground::mesh road("./files_rdf/Eight.rdf");

    // Tire Parameters
    std::string method = "geometric";

    // Initialize the tire shell
    shell tire_shell(
      20,  // n_r
      0.3, // r_x
      4.0, // m_x
      0.3, // r_y
      4.0, // m_y
      0.1  // l_y
    );

    // Orient the tire in the space
    real yaw_angle    = 0.0 * PI;
    real camber_angle = 0.0 * PI;
    real pitch_angle  = 0.0 * PI;

    // Set frequency and speed
    real frequency = 1000; // Hz
    real speed     = 10;   // m/s

    // Set starting and arrival positions
    //point start(1.7, -140.0, 0.3);   // 24.13 triangles (22.0% of duty cycle - 20 ribs)
    //point arrival(0.4, +140.0, 0.3); // 24.13 triangles
    //point start(5.0, -140.0, 0.3);   // 5.52 triangles (4.8% of duty cycle - 20 ribs)
    //point arrival(5.0, +140.0, 0.3); // 5.52 triangles
    point start(2.0, -140.0, 0.26);   // 20.39 triangles (18.0% of duty cycle - 20 ribs) (4.8% of duty cycle - 5 ribs)
    point arrival(2.0, +140.0, 0.26); // 20.39 triangles

    // Compute parameters
    real  step_size = (arrival - start).norm() / speed * frequency;
    point step((arrival - start) / step_size);
    point origin(start);
    vecN  time_vec(static_cast<size_t>(step_size) + 1);


    // Create frame object
    affine pose;
    pose = translate(origin) * angleaxis(yaw_angle,    UNITZ_VEC3)
                             * angleaxis(camber_angle, UNITX_VEC3)
                             * angleaxis(pitch_angle,  UNITY_VEC3);

    // Variable initialization (for real numbers)
    point contact_point;
    vec3  contact_normal;
    real  friction;
    real  depth;
    vec3  relative_angles;

    // Perform timing
    triangleground::vecptr triangles_list;
    real triangles_list_size = 0.0;
    for (size_t i = 0; i < step_size; ++i)
    {
      // Start chronometer
      tictoc.tic();

      // Set an orientation and calculate parameters
      tire_shell.setup(road, pose, method);

      // Data extraction (for real numbers)
      tire_shell.contactPoint(contact_point);
      tire_shell.contactNormal(contact_normal);
      tire_shell.contactFriction(friction);
      tire_shell.contactDepth(depth);
      tire_shell.relativeAngles(relative_angles);

      // Stop chronometer
      tictoc.toc();

      // Update single disk timing
      time_vec[i] = tictoc.elapsed_ms();

      // Update common variables
      road.intersection(tire_shell.BBox(), triangles_list);
      triangles_list_size += triangles_list.size();
      pose.translate(step);
    }

    real mean     = time_vec.mean();
    real variance = 0.0;
    triangles_list_size /= step_size;
    for (integer i = 0; i < time_vec.size(); ++i)
      {variance += (time_vec[i] - mean) * (time_vec[i] - mean);}
    variance /= time_vec.size();
    real std_dev = std::sqrt(variance);

    // Output performance data
    std::cout
      << "ENVE PERFORMANCE REPORT" << std::endl
      << "Method         = " << method << std::endl
      << "Total time     = " << time_vec.sum() << " ms" << std::endl
      << "Avg. step time = " << mean << " ms" << std::endl
      << "Variance       = " << variance << " ms" << std::endl
      << "Std. dev.      = " << std_dev << " ms" << std::endl
      << "Samples        = " << time_vec.size() << std::endl
      << "Avg. triangles = " << triangles_list_size << std::endl;
 
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
/// eof: enve_timing_00.cc
///
