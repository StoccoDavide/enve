/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * This file is part of the ENVE project.                              *
 *                                                                     *
 * Copyright (c) 2022, Davide Stocco. All rights reserved.             *
 *                                                                     *
 * The ENVE project can not be copied and/or distributed without       *
 * the express permission of Davide Stocco.                            *
 *                                                                     *
 *    Davide Stocco                                                    *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: davide.stocco@unitn.it                                   *
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
    public:
      typedef std::shared_ptr<mesh const> ptr;    //!< Pointer to mesh object
      typedef std::vector<mesh::ptr>      vecptr; //!< Vector of pointers to mesh objects

    private:
      triangleground::vecptr m_triangles;    //!< Ground triangles pointer vector
      aabb::vecptr           m_bboxes;       //!< Bounding boxes pointers vector

      #ifdef ENVE_USE_UTILS_AABBTREE
      AABBtreeUtils m_AABBtree; //!< Utils mesh tree pointer
      #else
      AABBtree::ptr m_AABBtree;      //!< Acme mesh tree pointer
      #endif

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
        std::string const & path //!< Path to the RDF file
      );

      //! Mesh class constructor
      mesh(
        std::string const & path,    //!< Path to the OBJ file
        real                friction //!< Friction scaling coefficient
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

      //! Print data in file
      void
      print(
        std::string const & path //!< File name in which print data
      ) const;

      //! Get the mesh bounding boxes pointers vector
      aabb::vecptr const &
      bboxes(void)
      const;

      //! Return number of triangles in the mesh
      size_t
      size(void)
      const;

      //! Load ground data as a *.rdf file
      bool
      load(
        std::string const & path //!< Path to the file
      );

      //! Load ground data as a *.obj file
      bool
      load(
        std::string const & path,    //!< Path to the file
        real                friction //!< Friction coefficient scaling factor
      );

      //! Intersect the mesh AABBtree with an external aabb object pointer
      bool
      intersection(
        aabb::ptr              const   box,      //!< External aabb object pointer
        triangleground::vecptr       & triangles //!< Intersected triangleground vector list
      ) const;

      //! Build mesh AABBtree
      void
      buildAABBtree(
        triangleground::vecptr const & triangles //!< Ground triangles pointer vector list
      );

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
