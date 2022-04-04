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

// TEST 2 - CREATE A MESH OBJECT FROM A triangleground OBJECT - LOAD TIRE
// DATA AND PERFORM THE INTERSECTION WITH THE CURRENT MESH

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
              << "ENVE TERRAIN SERVER TEST 2 - CHECK INTERSECTION ON KNOWN MESH" << std::endl
              << std::endl;

    // Initialize a quite big triangle
    point vertex[3];
    vertex[0] = point(0.0,    100.0, 0.0);
    vertex[1] = point(100.0,    0.0, 0.0);
    vertex[2] = point(0.0,   -100.0, 0.0);
    triangleground::vecptr triangle_prtVec;
    triangle_prtVec.push_back(
      triangleground::ptr(new triangleground(vertex, 1.0)));

    vertex[0] = point(0.0,    100.0, 0.0);
    vertex[1] = point(-100.0,   0.0, 0.0);
    vertex[2] = point(0.0,    -100.0, 0.0);
    triangle_prtVec.push_back(
      triangleground::ptr(new triangleground(vertex, 0.5)));

    // Build the mesh
    ground::mesh road(triangle_prtVec);

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
    tire_shell.setup(road, pose, "sampling");

    // Stop chronometer
    tictoc.toc();

    // Display current tire data on command line
    tire_shell.print(std::cout);

    affine cp_rib;
    for (size_t i = 0; i < tire_shell.size(); ++i)
    {
      tire_shell.contactPointAffine(i, cp_rib);
      std::cout << "Rib " << i << ":"
                << cp_rib << std::endl
                << std::endl;
    }

    // Output performance data
    std::cout << "Execution time = " << tictoc.elapsed_ms() * 1000 << " us" << std::endl
              << std::endl
              << "Check the results..." << std::endl
              << "enve TERRAIN SERVER TEST 2: Completed" << std::endl
              << std::endl;
  }
  catch (std::exception const &exc)
  {
    std::cerr << exc.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "enve TERRAIN SERVER TEST 2: Unknown error" << std::endl;
  }
}
