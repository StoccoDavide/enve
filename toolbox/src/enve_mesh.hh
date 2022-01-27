/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Enrico Bertolazzi.       *)
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
(*    Enrico Bertolazzi                                                *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: enrico.bertolazzi@unitn.it                               *)
(*                                                                     *)
(***********************************************************************)
*/

///
/// file: enve_mesh.hh
///

#pragma once

#ifndef INCLUDE_ENVE_MESH
#define INCLUDE_ENVE_MESH

// Print progress to console while loading (large models)
#define ENVE_CONSOLE_OUTPUT

#include <acme.hh>
#include <acme_AABBtree.hh>
#include <acme_aabb.hh>
#include <acme_utils.hh>
#include <acme_triangle.hh>

#include "enve.hh"
#include "enve_triangleground.hh"

using namespace acme;

namespace enve
{

  namespace ground
  {

    /*\
     |                       _
     |   _ __ ___   ___  ___| |__
     |  | '_ ` _ \ / _ \/ __| '_ \
     |  | | | | | |  __/\__ \ | | |
     |  |_| |_| |_|\___||___/_| |_|
     |
    \*/

    //! Triangular mesh class
    class mesh
    {
    public:
      typedef std::shared_ptr<mesh const> ptr;    //!< Pointer to mesh object
      typedef std::vector<mesh::ptr>      vecptr; //!< Vector of pointers to mesh objects

    private:
      triangleground::vecptr m_triangles; //!< Ground triangles pointer vector
      aabb::vecptr           m_bboxes;    //!< Bounding boxes pointers vector
      AABBtree::ptr          m_AABBtree;  //!< Mesh tree pointer

    public:
      //! Mesh class destructor
      ~mesh(void);

      //!< Mesh copy constructor
      mesh(mesh const &) = delete;

      //!< Mesh move constructor
      mesh(mesh const &&) = delete;

      //! Mesh class constructor
      mesh(void);

      //! Mesh class constructor
      mesh(
        triangleground::vecptr const &triangles //!< Ground triangles pointer vector list
      );

      //! Mesh class constructor
      mesh(
        std::string const &path //!< Path to the RDF file
      );

      //! Mesh class constructor
      mesh(
        std::string const &path,    //!< Path to the OBJ file
        real               friction //!< Friction scaling coefficient
      );

      //! Copy mesh object
      void
      copy(
        mesh const &mesh_in //!< Mesh object to be copied
      );

      //! Clear all mesh object data
      void
      clear(void);

      //! Get all triangleground pointers inside the mesh as a vector
      triangleground::vecptr const &
      vecptrTriangleground(void) const;

      //! Get i-th triangleground pointer
      triangleground::ptr
      ptrTriangleground(
        size_t i //!< Triangle index
      ) const;

      //! Get AABBtree object
      AABBtree::ptr const
      ptrAABBtree(void) const;

      //! Print data in file
      void
      print(
        std::string const &path //!< File name in which print data
      ) const;

      //! Get the mesh bounding boxes pointers vector
      aabb::vecptr const &
      bboxes(void) const;

      //! Return number of triangles in the mesh
      size_t
      size(void) const;

      //! Load ground data as a *.rdf file
      bool
      load(
        std::string const &path //!< Path to the file
      );

      //! Load ground data as a *.obj file
      bool
      load(
        std::string const &path,    //!< Path to the file
        real               friction //!< Friction coefficient scaling factor
      );

      //! Intersect the mesh AABB tree with an external AABB tree
      bool
      intersection(
        AABBtree::ptr const     AABBtree, //!< External AABBtree object pointer
        triangleground::vecptr &triangles //!< Intersected triangleground vector list
      ) const;

      //! Update the mesh AABBtree with an external aabb object pointer vector
      bool
      intersection(
        aabb::vecptr const     &boxes,    //!< External aabb object pointer vector
        triangleground::vecptr &triangles //!< Intersected triangleground vector list
      ) const;

      //! Update the mesh AABBtree with an external aabb object pointer
      bool
      intersection(
        aabb::ptr const         box,      //!< External aabb object pointer
        triangleground::vecptr &triangles //!< Intersected triangleground vector list
      ) const;

    private:
      //! Update the mesh bounding boxes pointers
      void
      updateBBoxes(void);

      //! Split a string into a string array at a given token
      void
      split(
        std::string const        &in,   //!< Input string
        std::vector<std::string> &out,  //!< Output string vector
        std::string const        &token //!< Token
      ) const;

      //! Get tail of string after first token and possibly following spaces
      std::string
      tail(
        std::string const &in //!< Input string
      ) const;

      //! Get first token of string
      std::string
      firstToken(
        std::string const &in //!< Input string
      ) const;

    };

  } // namespace ground

} // namespace enve

#endif

///
/// eof: enve_mesh.hh
///