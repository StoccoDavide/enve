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
/// file: enve_rtf_00.cc
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
      << "RTF 00 - ENVE REAL-TIME FACTOR 0" << std::endl
      << std::endl;

    // Instantiate a TicToc object
    TicToc tictoc;

    // Load *.rdf File
    std::vector<ground::mesh> road(10);
    road[0].load("../files_obj_rtf/test_rtf_1.obj", 1.0);
    road[1].load("../files_obj_rtf/test_rtf_2.obj", 1.0);
    road[2].load("../files_obj_rtf/test_rtf_3.obj", 1.0);
    road[3].load("../files_obj_rtf/test_rtf_4.obj", 1.0);
    road[4].load("../files_obj_rtf/test_rtf_5.obj", 1.0);
    road[5].load("../files_obj_rtf/test_rtf_6.obj", 1.0);
    road[6].load("../files_obj_rtf/test_rtf_7.obj", 1.0);
    road[7].load("../files_obj_rtf/test_rtf_8.obj", 1.0);
    road[8].load("../files_obj_rtf/test_rtf_9.obj", 1.0);
    road[9].load("../files_obj_rtf/test_rtf_10.obj", 1.0);

    ground::mesh road_obj("../files_obj_rtf/test_rtf_5.obj", 1.0);

    // Tire Parameters
    std::string method = "sampling";

    shell tire(
      1,       // n_r
      0.3,       // r_x
      6.0,       // m_x
      0.3,       // r_y
      9.0,       // m_y
      0.205/2.0  // l_y
    );
    size_t tire_max_ribs = 10;

    // Set starting and arrival positions
    matN   time_mat(static_cast<size_t>(tire_max_ribs), static_cast<size_t>(road.size()));
    matN   var_mat(static_cast<size_t>(tire_max_ribs), static_cast<size_t>(road.size()));
    matN   std_mat(static_cast<size_t>(tire_max_ribs), static_cast<size_t>(road.size()));
    affine pose;
    pose = translate(0.0, 0.0 ,0.25);

    // Variable initialization (for real numbers)
    point contact_point;
    vec3  contact_normal;
    real  friction;
    real  depth;
    vec3  relative_angles;

    // Perform timing
    triangleground::vecptr triangles_list;
    real triangles_list_size = 0.0;
    real variance = 0.0;
    size_t times = 1000;
    vecN   times_tmp(times);
    for (size_t ii = 0; ii < tire_max_ribs; ++ii) {
      //tire.resize(ii+1); // Enve
      tire.resize(1); // Rill
      for (size_t jj = 0; jj < road.size(); ++jj) {
        std::cout << "Rib = " << ii+1 << " - Road = " << jj+1 << std::endl;
        for (size_t kk = 0; kk < times; ++kk) {

          // Start chronometer
          tictoc.tic();

          // Set an orientation and calculate parameters
          tire.setup(road[jj], pose, method);

          // Data extraction (for real numbers)
          tire.contactPoint(contact_point);
          tire.contactNormal(contact_normal);
          tire.contactFriction(friction);
          tire.contactDepth(depth);
          tire.relativeAngles(relative_angles);

          // Stop chronometer
          tictoc.toc();

          // Update single disk timing

          times_tmp[kk] = tictoc.elapsed_ms();

          // Update common variables
          time_mat(ii,jj) = times_tmp.mean();
          var_mat(ii,jj) = 0.0;
          for (integer i = 0; i < times_tmp.size(); ++i)
            {var_mat(ii,jj) += (times_tmp[kk] - time_mat(ii,jj)) * (times_tmp[kk] - time_mat(ii,jj));}
          var_mat(ii,jj) /= times_tmp.size();
          std_mat(ii,jj) = std::sqrt(var_mat(ii,jj));

          // Update common variables
          road[jj].intersection(tire.bbox(), triangles_list);
          triangles_list_size += triangles_list.size();
          triangles_list.clear();
        }
      }
    }

    // Output performance data
    std::cout
      << "ENVE PERFORMANCE REPORT" << std::endl
      << "Method         = " << method << std::endl
      << "Variance       = " << std::endl << var_mat << " ms" << std::endl
      << "Std. dev.      = " << std::endl << std_mat << " ms" << std::endl
      << "Time           = " << std::endl << time_mat << std::endl
      << "Avg. triangles = " << triangles_list_size << std::endl;

    // End of test
    std::cout
      << std::endl
      << "RTF 00: Completed" << std::endl
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
/// eof: enve_rtf_00.cc
///
