/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020, Matteo Larcher, Davide Stocco and Enrico        *)
(* Bertolazzi.                                                         *)
(*                                                                     *)
(* The ENVE project and its components are supplied under the terms of *)
(* the open source BSD 2-Clause License. The contents of the ENVE      *)
(* project and its components may not be copied or disclosed except in *)
(* accordance with the terms of the BSD 2-Clause License.              *)
(*                                                                     *)
(* URL: https://opensource.org/licenses/BSD-2-Clause                   *)
(*                                                                     *)
(*    Davide Stocco                                                    *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: davide.stocco@unitn.it                                   *)
(*                                                                     *)
(*    Matteo Larcher                                                   *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: matteo.larcher@unitn.it                                  *)
(*                                                                     *)
(*    Enrico Bertolazzi                                                *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: enrico.bertolazzi@unitn.it                               *)
(*                                                                     *)
(***********************************************************************)
*/

#include "sfun_interface.h"
#include "sfun_shellVehicle.hh"

#ifdef __cplusplus
extern "C"
{
#endif

  void *ground_ptr;
  void *shell_rr_ptr;
  void *shell_rl_ptr;
  void *shell_fr_ptr;
  void *shell_fl_ptr;

  void
  sfun_init(
    const double *size,
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
    const double *flatHeight,
    const double *flatFriction
  )
  {
    char *envar_ground_path = getenv("ENVE_GROUND_PATH");
    if (envar_ground_path == NULL)
    {
      std::cout << "Environment variable ENVE_GROUND_PATH does not exist!" << std::endl;
      return;
    }

    std::string ground_path(reinterpret_cast<char const *>(envar_ground_path));

    std::cout << "ENVE_GROUND_PATH: " << ground_path << std::endl;

    std::string extension = ground_path.substr(ground_path.size() - 4, 4);
    enve::ground::mesh *ground;
    if (extension == ".rdf")
      ground = new enve::ground::mesh(ground_path);
    else if (extension == ".obj")
      ground = new enve::ground::mesh(ground_path, 1.0);

    shellVehicle *shell_rr = new shellVehicle();
    shellVehicle *shell_rl = new shellVehicle();
    shellVehicle *shell_fr = new shellVehicle();
    shellVehicle *shell_fl = new shellVehicle();

    shell_rr->init(size, r_x_r, m_x_r, r_y_r, m_y_r, l_y_r, flatHeight, flatFriction);
    shell_rl->init(size, r_x_r, m_x_r, r_y_r, m_y_r, l_y_r, flatHeight, flatFriction);
    shell_fr->init(size, r_x_f, m_x_f, r_y_f, m_y_f, l_y_f, flatHeight, flatFriction);
    shell_fl->init(size, r_x_f, m_x_f, r_y_f, m_y_f, l_y_f, flatHeight, flatFriction);

    ground_ptr = reinterpret_cast<void *>(ground);

    shell_rr_ptr = reinterpret_cast<void *>(shell_rr);
    shell_rl_ptr = reinterpret_cast<void *>(shell_rl);
    shell_fr_ptr = reinterpret_cast<void *>(shell_fr);
    shell_fl_ptr = reinterpret_cast<void *>(shell_fl);
  }

  void
  sfun_out(
    const shellsRF *input,
    groundContact  *output,
    const double   *method,
    const double   *flat_enable
  )
  {
    enve::ground::mesh *ground = reinterpret_cast<enve::ground::mesh *>(ground_ptr);

    shellVehicle *shell_fl = reinterpret_cast<shellVehicle *>(shell_fl_ptr);
    shellVehicle *shell_fr = reinterpret_cast<shellVehicle *>(shell_fr_ptr);
    shellVehicle *shell_rl = reinterpret_cast<shellVehicle *>(shell_rl_ptr);
    shellVehicle *shell_rr = reinterpret_cast<shellVehicle *>(shell_rr_ptr);

    bool in_mesh_fl = shell_fl->out(ground, input->RFw_fl, method, output->RFpc_fl_ground, output->rho_fl, output->friction_fl, flat_enable);
    bool in_mesh_fr = shell_fr->out(ground, input->RFw_fr, method, output->RFpc_fr_ground, output->rho_fr, output->friction_fr, flat_enable);
    bool in_mesh_rl = shell_rl->out(ground, input->RFw_rl, method, output->RFpc_rl_ground, output->rho_rl, output->friction_rl, flat_enable);
    bool in_mesh_rr = shell_rr->out(ground, input->RFw_rr, method, output->RFpc_rr_ground, output->rho_rr, output->friction_rr, flat_enable);

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
