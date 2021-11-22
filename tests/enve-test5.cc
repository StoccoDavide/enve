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

// TEST 5 - CHECK POLYNOM SHAPE

#include <chrono>
#include <fstream>
#include <iostream>

#include <acme.hh>
#include <acme_math.hh>

#include <Utils/TicToc.hxx>

#include "enve.hh"
#include "enve_mesh.hh"
#include "enve_polynom.hh"
#include "enve_shape.hh"

using namespace acme;
using namespace enve;

// Main function
int
main()
{

  try
  {
    std::cout << std::endl
              << "ENVE TERRAIN SERVER TEST 5 - CHECK POLYNOM SHAPE" << std::endl
              << std::endl;

    // Initialize the tire shape data
    vecN   dataR{{0.1, 0.12, 0.11}}; // Vector of radius data (m)
    vecN   dataY{{-0.1, 0.0, 0.11}}; // Vector of y data (m)
    size_t order = 2;               // Polynom order

    polynom tire_shape(dataR, dataY, order);

    // Display current tire data on command line
    tire_shape.print(std::cout);

    std::cout << "Surface radius" << std::endl
              << tire_shape.surfaceRadius(-0.1) << " m" << std::endl
              << tire_shape.surfaceRadius(0.0) << " m" << std::endl
              << tire_shape.surfaceRadius(0.1) << " m" << std::endl;

    std::cout << "Surface derivative" << std::endl
              << tire_shape.surfaceDerivative(-0.1) << std::endl
              << tire_shape.surfaceDerivative(0.0) << std::endl
              << tire_shape.surfaceDerivative(0.1) << std::endl;

    // Output performance data
    std::cout << "Check the results..." << std::endl
              << "enve TERRAIN SERVER TEST 5: Completed" << std::endl
              << std::endl;
  }
  catch (std::exception const &exc)
  {
    std::cerr << exc.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "enve TERRAIN SERVER TEST 5: Unknown error" << std::endl;
  }
}
