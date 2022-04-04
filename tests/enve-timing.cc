/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *)
(*                                                                     *)
(* The ENVE project can not be copied and/or distributed without the   *)
(* express permission of Davide Stocco and Enrico Bertolazzi.          *)
(*                                                                     *)
(*    Davide Stocco                                                    *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: davide.stocco@unitn.it                                   *)
(*                                                                     *)
(*    Enrico Bertolazzi                                                *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: enrico.bertolazzi@unitn.it                               *)
(*                                                                     *)
(***********************************************************************)
*/

// TIMING TEST - PERFORM TIMING ON A LARGE SAMPLING PERIOD

#include <chrono>
#include <fstream>
#include <iostream>

#include <acme.hh>
#include <acme_math.hh>

#include <Utils/TicToc.hxx>

#include "enve.hh"
#include "enve_mesh.hh"
#include "enve_shell.hh"

using namespace acme;
using namespace enve;

// Main function
int
main()
{

  try
  {

    // Instantiate a TicToc object
    Utils::TicToc tictoc;

    std::cout << "ENVE TERRAIN SERVER TIMING TEST" << std::endl
              << std::endl;

    // Load .rdf File
    ground::mesh road("./files_rdf/Eight.rdf");

    // Tire Parameters
    std::string method = "geometric";

    // Initialize the tire shell
    shell tire_shell(20,  // ribs number
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

    // Set starting and arrival positions ("geometric")
    //point start(1.7, -140.0, 0.3);   // 24.13 triangles (22.0% of duty cycle - 20 ribs)
    //point arrival(0.4, +140.0, 0.3); // 24.13 triangles
    //point start(5.0, -140.0, 0.3);   // 5.52 triangles (4.8% of duty cycle - 20 ribs)
    //point arrival(5.0, +140.0, 0.3); // 5.52 triangles
    point start(2.0, -140.0, 0.26);   // 20.39 triangles (18.0% of duty cycle - 20 ribs) (4.8% of duty cycle - 5 ribs)
    point arrival(2.0, +140.0, 0.26); // 20.39 triangles

    // Compute parameters
    real                   step_size = (arrival - start).norm() / speed * frequency;
    point                  step((arrival - start) / step_size);
    point                  origin(start);
    vecN                   time_vec(static_cast<int>(step_size) + 1);
    triangleground::vecptr triangles_list;
    real                   triangles_list_size = 0.0;

    // Create frame object
    affine pose;
    pose = translate(origin) * angleaxis(yaw_angle, UNITZ_VEC3) * angleaxis(camber_angle, UNITX_VEC3) * angleaxis(pitch_angle, UNITY_VEC3);

    // Variable initialization (for real numbers)
    point contact_point;
    vec3  contact_normal;
    real  friction;
    real  depth;
    vec3  relative_angles;

    // Perform timing
    for (unsigned int i = 0; i < step_size; ++i)
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

    for (unsigned i = 0; i < time_vec.size(); ++i)
      variance += (time_vec[i] - mean) * (time_vec[i] - mean);

    variance /= time_vec.size();
    real std_dev = std::sqrt(variance);

    // Output performance data
    std::cout << "ENVE TERRAIN SERVER PERFORMANCE DATA" << std::endl
              << "Enveloping model: " << method << std::endl
              << "Total time    = " << time_vec.sum() << " ms" << std::endl
              << "Avg step time = " << mean << " ms" << std::endl
              << "Variance      = " << variance << " ms" << std::endl
              << "Std_dev       = " << std_dev << " ms" << std::endl
              << "Samples       = " << time_vec.size() << std::endl
              << "AvgTri        = " << triangles_list_size << std::endl
              << std::endl;

    // This constructs a duration object using milliseconds
    std::cout << std::endl
              << "ENVE TIMING TEST: Completed" << std::endl
              << std::endl;
  }
  catch (std::exception const &exc)
  {
    std::cerr << exc.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "ENVE TIMING TEST: Unknown error" << std::endl;
  }
}
