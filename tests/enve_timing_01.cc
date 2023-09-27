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
/// file: enve_timing_01.cc
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
      << "TIMING 01 - ENVE TIMING 1" << std::endl
      << std::endl;

    // Instantiate a TicToc object
    TicToc tictoc;

    // Load *.rdf File
    ground::mesh road("./files_rdf/LakeTown.rdf");

    // Tire Parameters
    std::string method = "geometric";

    // Initialize the tire shell
    shell tire_shell(
      5,   // n_r
      0.3, // r_x
      6.0, // m_x
      0.3, // r_y
      6.0, // m_y
      0.1  // l_y
    );

    // Orient the tire in the space
    real yaw_angle    = 0.0 * PI;
    real camber_angle = 0.0 * PI;
    real pitch_angle  = 0.0 * PI;

    // Set starting and arrival positions
    // Geometric
    // 198.09 triangles (14.2% of duty cycle - 20 ribs)  (8.8% of duty cycle - 10 ribs) (5.6% of duty cycle - 5 ribs)
    // Sampling
    // 198.09 triangles (92.4% of duty cycle - 20 ribs)  (47.3% of duty cycle - 10 ribs) (24.3% of duty cycle - 5 ribs)
    point start(45.0, 175.6, 0.26);
    point arrival(46.0, 175.6, 0.26);

    // Compute parameters
    size_t steps = 1e3;
    point  step((arrival - start) / steps);
    point  origin(start);
    vecN   time_vec(static_cast<size_t>(steps) + 1);

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
    for (size_t i = 0; i < steps; ++i)
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
      road.intersection(tire_shell.bbox(), triangles_list);
      triangles_list_size += triangles_list.size();
      triangles_list.clear();
      pose.translate(step);
    }

    real mean     = time_vec.mean();
    real variance = 0.0;
    triangles_list_size /= steps;
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
      << "TIMING 01: Completed" << std::endl
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
/// eof: enve_timing_01.cc
///
