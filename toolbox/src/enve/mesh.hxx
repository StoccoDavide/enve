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
/// file: mesh.hxx
///

#ifndef INCLUDE_ENVE_MESH_HXX
#define INCLUDE_ENVE_MESH_HXX

#include "triangleground.hxx"

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
    private:
      triangleground::vecptr m_triangles; //!< Ground triangles pointers vector
      aabb::vecptr           m_bboxes;    //!< Bounding boxes pointers vector
      AABBtree::ptr          m_AABBtree;  //!< Mesh AABB tree

    public:
      //! Mesh copy constructor
      mesh(mesh const &) = delete;

      //! Mesh move constructor
      mesh(mesh &&) = delete;

      //! Mesh assignment operator
      mesh & operator=(const mesh &) = delete;

      //! Mesh move assignment operator
      mesh & operator=(mesh &&) = delete;

      //! Mesh class destructor
      ~mesh(void) = default;

      //! Mesh class constructor
      mesh(void);

      //! Mesh class constructor
      mesh(
        triangleground::vecptr const & triangles //!< Ground triangles pointer vector list
      );

      //! Mesh class constructor
      mesh(
        std::string const & path,                  //!< Path to the RDF file
        affine      const & pose = IDENTITY_AFFINE //!< Scaling factor for the mesh
      );

      //! Mesh class constructor
      mesh(
        std::string const & path,                  //!< Path to the OBJ file
        real                friction,              //!< Friction scaling coefficient
        affine      const & pose = IDENTITY_AFFINE //!< Scaling factor for the mesh
      );

      //! Copy mesh object
      void
      copy(
        mesh const & mesh_obj //!< Mesh object to be copied
      );

      //! Clear all mesh object data
      void
      clear(void);

      //! Get all triangleground pointers inside the mesh as a vector
      triangleground::vecptr const &
      vecptrTriangleground(void)
      const;

      //! Get i-th triangleground pointer
      triangleground::ptr
      ptrTriangleground(
        size_t i //!< Triangle index
      ) const;

      //! Get i-th triangleground pointer
      triangleground::ptr
      operator[](
        size_t i //!< Triangle index
      ) const;

      //! Print data in file
      void
      print(
        std::string const & path //!< File name in which print data
      ) const;

      //! Return number of triangles in the mesh
      size_t
      size(void)
      const;

      //! Load ground data as a *.rdf file
      bool
      load(
        std::string const & path,                  //!< Path to the file
        affine      const & pose = IDENTITY_AFFINE //!< Scaling factor for the mesh
      );

      //! Load ground data as a *.obj file
      bool
      load(
        std::string const & path,                  //!< Path to the file
        real                friction,              //!< Friction coefficient scaling factor
        affine      const & pose = IDENTITY_AFFINE //!< Scaling factor for the mesh
      );

      //! Intersect the mesh AABBtree with an external aabb object pointer
      bool
      intersection(
        aabb::ptr              const   box,      //!< External aabb object pointer
        triangleground::vecptr       & triangles //!< Intersected triangleground vector list
      ) const;

      //! Build mesh AABBtree
      void
      buildAABBtree(void);

    private:
      //! Update the mesh bounding boxes pointers
      void
      updateBBoxes(void);

      //! Split a string into a string array at a given token
      void
      split(
        std::string              const & in,   //!< Input string
        std::vector<std::string>       & out,  //!< Output string vector
        std::string              const & token //!< Token
      ) const;

      //! Get tail of string after first token and possibly following spaces
      std::string
      tail(
        std::string const & in //!< Input string
      ) const;

      //! Get first token of string
      std::string
      firstToken(
        std::string const & in //!< Input string
      ) const;

    };

  } // namespace ground

} // namespace enve

#endif

///
/// eof: mesh.hxx
///
