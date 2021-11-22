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
  void *shell_fl_ptr;
  void *shell_fr_ptr;
  void *shell_rl_ptr;
  void *shell_rr_ptr;

  void
  sfun_init(
    const double *r_x_f,
    const double *m_x_f,
    const double *r_y_f,
    const double *m_y_f,
    const double *l_y_f,
    const double *r_x_r,
    const double *m_x_r,
    const double *r_y_r,
    const double *m_y_r,
    const double *l_y_r,
    const double *size,
    const double *threshold)
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

    shellVehicle *shell_fl = new shellVehicle();
    shellVehicle *shell_fr = new shellVehicle();
    shellVehicle *shell_rl = new shellVehicle();
    shellVehicle *shell_rr = new shellVehicle();

    shell_fl->init(r_x_f, m_x_f, r_y_f, m_y_f, l_y_f, size, threshold);
    shell_fr->init(r_x_f, m_x_f, r_y_f, m_y_f, l_y_f, size, threshold);
    shell_rl->init(r_x_r, m_x_r, r_y_r, m_y_r, l_y_r, size, threshold);
    shell_rr->init(r_x_r, m_x_r, r_y_r, m_y_r, l_y_r, size, threshold);

    ground_ptr = reinterpret_cast<void *>(ground);

    shell_fl_ptr = reinterpret_cast<void *>(shell_fl);
    shell_fr_ptr = reinterpret_cast<void *>(shell_fr);
    shell_rl_ptr = reinterpret_cast<void *>(shell_rl);
    shell_rr_ptr = reinterpret_cast<void *>(shell_rr);
  }

  void
  sfun_out(
    const shellsRF *input,
    groundContact  *output,
    const double   *flat_enable,
    const double   *time_step)
  {
    enve::ground::mesh *ground = reinterpret_cast<enve::ground::mesh *>(ground_ptr);

    shellVehicle *shell_fl = reinterpret_cast<shellVehicle *>(shell_fl_ptr);
    shellVehicle *shell_fr = reinterpret_cast<shellVehicle *>(shell_fr_ptr);
    shellVehicle *shell_rl = reinterpret_cast<shellVehicle *>(shell_rl_ptr);
    shellVehicle *shell_rr = reinterpret_cast<shellVehicle *>(shell_rr_ptr);

    bool in_mesh_fl = shell_fl->out(ground, input->RFw_fl, output->RFpc_fl_ground, output->rho_fl, output->rho_dot_fl, output->friction_fl, flat_enable, time_step);
    bool in_mesh_fr = shell_fr->out(ground, input->RFw_fr, output->RFpc_fr_ground, output->rho_fr, output->rho_dot_fr, output->friction_fr, flat_enable, time_step);
    bool in_mesh_rl = shell_rl->out(ground, input->RFw_rl, output->RFpc_rl_ground, output->rho_rl, output->rho_dot_rl, output->friction_rl, flat_enable, time_step);
    bool in_mesh_rr = shell_rr->out(ground, input->RFw_rr, output->RFpc_rr_ground, output->rho_rr, output->rho_dot_rr, output->friction_rr, flat_enable, time_step);

    // in_mesh equal to 1 only if all the wheels are on the mesh
    if (in_mesh_fl && in_mesh_fr && in_mesh_rl && in_mesh_rr)
      output->in_mesh = 1;
    else
      output->in_mesh = 0;
  }

  void
  sfun_end()
  {
    sfun_destroy_ground(ground_ptr);
    sfun_destroy_shell(shell_fl_ptr);
    sfun_destroy_shell(shell_fr_ptr);
    sfun_destroy_shell(shell_rl_ptr);
    sfun_destroy_shell(shell_rr_ptr);
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
