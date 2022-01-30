/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Enrico Bertolazzi.       *)
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

// TEST 1 - LOAD THE DATA FROM THE RDF FILE THEN PRINT IT INTO A TXT FILE.
// LOAD TIRE DATA AND PERFORM THE INTERSECTION WITH THE CURRENT MESH

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

    std::cout << std::endl
              << "ENVE TERRAIN SERVER TEST 1 - CHECK INTERSECTION ON UNKNOWN MESH" << std::endl
              << std::endl;

    // Load .rdf File
    ground::mesh road("./../files_rdf/sample.rdf");

    // Print OutMesh.txt file
    road.print("bin/OutMesh.txt");

    // Initialize the tire shell
    shell tire_shell(5,      // ribs number
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
    pose = translate(0.0, 0.0, 0.3) * angleaxis(yaw_angle, UNITZ_VEC3) * angleaxis(camber_angle, UNITX_VEC3) * angleaxis(pitch_angle, UNITY_VEC3);

    // Start chronometer
    tictoc.tic();

    // Set an orientation and calculate parameters
    tire_shell.setup(road, pose, "geometric");

    // Stop chronometer
    tictoc.toc();

    // Display current tire data on command line
    tire_shell.print(std::cout);

    // Output performance data
    std::cout << "Execution time = " << tictoc.elapsed_ms() * 1000 << " us" << std::endl
              << std::endl
              << "Check the results..." << std::endl
              << "enve TERRAIN SERVER TEST 1: Completed" << std::endl
              << std::endl;
  }
  catch (std::exception const &exc)
  {
    std::cerr << exc.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "enve TERRAIN SERVER TEST 1: Unknown error" << std::endl;
  }
}
