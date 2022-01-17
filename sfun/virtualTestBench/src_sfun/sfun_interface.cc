/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Matteo Larcher, Davide Stocco and          *)
(* Enrico Bertolazzi.                                                  *)
(*                                                                     *)
(* The ENVE project and its components are supplied under the terms of *)
(* the open source BSD 2-Clause License. The contents of the ENVE      *)
(* project and its components may not be copied or disclosed except in *)
(* accordance with the terms of the BSD 2-Clause License.              *)
(*                                                                     *)
(* URL: https://opensource.org/licenses/BSD-2-Clause                   *)
(*                                                                     *)
(*    Matteo Larcher                                                   *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: matteo.larcher@unitn.it                                  *)
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

#include "sfun_interface.h"

#ifdef __cplusplus
extern "C"
{
#endif

  void *ground_ptr;
  void *shell_ptr;

  void
  sfun_init(
    const double *r_x,
    const double *m_x,
    const double *r_y,
    const double *m_y,
    const double *l_y,
    const double *size
  )
  {
    char *envar_path_rdf = getenv("ENVE_RDF_PATH");
    if (envar_path_rdf == NULL)
    {
      std::cout << "Environment variable ENVE_RDF_PATH does not exist!" << std::endl;
      return;
    }

    std::string rdf_path(reinterpret_cast<char const *>(envar_path_rdf));
    std::cout << "RDF path: " << rdf_path << std::endl;
    enve::ground::mesh *ground = new enve::ground::mesh(rdf_path);

    shellVehicle *shell = new shellVehicle();
    shell->init(r_x, m_x, r_y, m_y, l_y, size);

    ground_ptr = reinterpret_cast<void *>(ground);
    shell_ptr  = reinterpret_cast<void *>(shell);
  }

  void
  sfun_out(
    const shellRF *input,
    groundContact *output,
    const double  *method,
    const double  *flat_enable
  )
  {
    enve::ground::mesh *ground = reinterpret_cast<enve::ground::mesh *>(ground_ptr);
    shellVehicle       *shell  = reinterpret_cast<shellVehicle *>(shell_ptr);

    output->in_mesh = shell->out(ground, input->RFw, method, output->RFpc_ground, output->rho, output->friction, flat_enable);
  }

  void
  sfun_end()
  {
    sfun_destroy_ground(ground_ptr);
    sfun_destroy_shell(shell_ptr);
  }

  void
  sfun_destroy_shell(void *shell_sf)
  {
    shellVehicle *shell = reinterpret_cast<shellVehicle *>(shell_sf);
    if (shell != nullptr)
    {
      delete shell;
      shell_sf = nullptr;
    }
  }

  void
  sfun_destroy_ground(void *ground_sf)
  {
    enve::ground::mesh *ground = reinterpret_cast<enve::ground::mesh *>(ground_sf);
    if (ground != nullptr)
    {
      delete ground;
      ground_sf = nullptr;
    }
  }

#ifdef __cplusplus
}
#endif
