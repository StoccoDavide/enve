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
/// file: mesh.cc
///

#include "enve.hh"
#include "Utils.hh"

//#define ENVE_DEBUG

#ifdef ENVE_DEBUG
  #define ENVE_DEBUG_TICTOC      Utils::TicToc tictoc
  #define ENVE_DEBUG_TIC         tictoc.tic()
  #define ENVE_DEBUG_TOC         tictoc.toc()
  #define ENVE_MESSAGE_DEBUG(...) std::cout << fmt::format(__VA_ARGS__) << std::flush
#else
  #define ENVE_DEBUG_TICTOC
  #define ENVE_DEBUG_TIC
  #define ENVE_DEBUG_TOC
  #define ENVE_MESSAGE_DEBUG(...)
#endif

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

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    mesh::mesh(void)
    {
      #ifdef ENVE_USE_UTILS_AABBTREE
      #else
      this->m_AABBtree = std::make_shared<AABBtree>();
      #endif
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    mesh::mesh(
      triangleground::vecptr const & triangles
    )
      : mesh()
    {
      this->buildAABBtree(triangles);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    mesh::mesh(
      std::string const & path
    )
      : mesh()
    {
      #define CMD "enve::mesh::mesh(...): "

      ENVE_ASSERT(this->load(path),
        CMD "error while reading file.");

      #undef CMD
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    mesh::mesh(
      std::string const & path,
      real                friction
    )
      : mesh()
    {
      #define CMD "enve::mesh::mesh(...): "

      ENVE_ASSERT(this->load(path, friction),
        CMD "error while reading file.");

      #undef CMD
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::copy(
      mesh const & mesh_obj
    )
    {
      this->m_triangles = mesh_obj.m_triangles;
      this->m_bboxes    = mesh_obj.m_bboxes;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::clear(void)
    {
      if (!this->m_bboxes.empty())
      {
        for (size_t i = 0; i < this->size(); ++i)
          {this->m_bboxes[i].reset();}
      }
      this->m_bboxes.clear();
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    triangleground::vecptr const &
    mesh::vecptrTriangleground(void)
      const
    {
      return this->m_triangles;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    triangleground::ptr
    mesh::ptrTriangleground(
      size_t i
    )
      const
    {
      return this->m_triangles[i];
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::print(
      std::string const & path
    )
      const
    {
      // Create Out.txt
      std::ofstream file(path);
      // Print introduction
      file
        << "MESH DATA" << std::endl
        << std::endl
        << "Legend:" << std::endl
        << "T  : i-th triangle position" << std::endl
        << "V0 : triangle vertex 0" << std::endl
        << "V1 : triangle vertex 1" << std::endl
        << "V2 : triangle vertex 2" << std::endl
        << "N  : normal to the face" << std::endl
        << "F  : friction coefficient" << std::endl
        << std::endl;
      for (size_t i = 0; i < this->m_triangles.size(); ++i)
      {
        triangleground const & Ti = *this->m_triangles[i];
        point          const & V0 = Ti.triangle::vertex(0);
        point          const & V1 = Ti.triangle::vertex(1);
        point          const & V2 = Ti.triangle::vertex(2);
        vec3           const & N  = Ti.normal();
        real           const & F  = Ti.friction();
        // Print vertices, normal and friction
        file
          << "T  = " << i  << std::endl
          << "V0 = " << V0 << std::endl
          << "V1 = " << V1 << std::endl
          << "V2 = " << V2 << std::endl
          << "N  = " << N  << std::endl
          << "F  = " << F  << std::endl
          << std::endl;
      }
      // Close File
      file.close();
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    aabb::vecptr const &
    mesh::bboxes(void)
      const
    {
      return this->m_bboxes;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    size_t
    mesh::size(void)
      const
    {
      return this->m_triangles.size();
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool
    mesh::load(
      std::string const & path
    )
    {
      #define CMD "enve::ground::load(...): "

      // Start loading mesh
      std::cout << "Loading *.rdf mesh... ";

      // Check if the file is an ".rdf" file
      if (path.substr(path.size() - 4, 4) != ".rdf")
      {
        std::cout << "Failed" << std::endl;
        ENVE_ERROR(CMD "not a *.rdf file.");
        //return false;
      }

      // Check if the file had been correctly open
      std::ifstream file(path);
      if (!file.is_open())
      {
        std::cout << "Failed" << std::endl;
        ENVE_ERROR(CMD "*.rdf file not opened.");
        //return false;
      }

      // Vector for nodes coordinates
      std::vector<point> nodes;
      nodes.reserve(25000);
      this->m_triangles.reserve(100000);
      size_t nodes_count    = size_t(0);
      size_t elements_count = size_t(0);
      bool   nodes_parse    = false;
      bool   elements_parse = false;

      // Instantiate temporaries
      std::string curline, token;
      std::vector<std::string> s_node;
      s_node.reserve(4);
      point p_node;
      std::vector<integer> i_element(3);
      real i_friction;
      while (std::getline(file, curline))
      {
        token = this->firstToken(curline);
        if (token == "[NODES]" || token == "NODES")
        {
          nodes_parse    = true;
          elements_parse = false;
          continue;
        }
        else if (token == "[ELEMENTS]" || token == "ELEMENTS")
        {
          nodes_parse    = false;
          elements_parse = true;
          continue;
        }
        else if (token[0] == '{')
        {
          // Multi-line comment, should read until '}' - NOT IMPLEMENTED
          // Treated as a sigle-line comment
          continue;
        }
        else if (token[0] == '%' || token[0] == '#' || token[0] == '\r')
        {
          // Check comments or empty lines
          continue;
        }

        // Generate a vertex position
        if (nodes_parse)
        {
          this->split(this->tail(curline), s_node, " ");
          ENVE_ASSERT(s_node.size() == size_t(3),
            CMD "wrong numbder of elements detected.");
          p_node[0] = real(std::stod(s_node[0]));
          p_node[1] = real(std::stod(s_node[1]));
          p_node[2] = real(std::stod(s_node[2]));
          nodes.push_back(p_node);
          ++nodes_count;
        }
        // Generate a face (vertices & indices)
        if (elements_parse)
        {
          // Generate the triangle vertices from the element
          this->split(curline, s_node, " ");
          ENVE_ASSERT(s_node.size() == size_t(4),
            CMD "wrong numbder of elements detected.");
          i_element[0] = integer(std::stoi(s_node[0]));
          i_element[1] = integer(std::stoi(s_node[1]));
          i_element[2] = integer(std::stoi(s_node[2]));
          i_friction   = real(std::stod(s_node[3]));
          ENVE_ASSERT(i_element[0] >= integer(0),
            CMD "element 0 index cannot be negative.");
          ENVE_ASSERT(i_element[1] >= integer(0),
            CMD "element 1 index cannot be negative.");
          ENVE_ASSERT(i_element[2] >= integer(0),
            CMD "element 2 index cannot be negative.");
          ENVE_ASSERT(i_friction >= real(0.0),
            CMD "element friction cannot be negative.");

          // Create a shared pointer for the last triangle
          this->m_triangles.push_back(
            std::make_shared<triangleground const>(
              elements_count, i_friction,
              nodes[i_element[0]], nodes[i_element[1]], nodes[i_element[2]]
            ));
            ++elements_count;
          continue;
        }
      }
      std::cout
        << "Done" << std::endl;

      // Perform safety check
      ENVE_ASSERT(nodes.size() == nodes_count && this->m_triangles.size() == elements_count,
        CMD "safety check not passed.");

      file.close();
      if (this->m_triangles.empty())
      {
        ENVE_ERROR(CMD "*.rdf loaded mesh is empty.");
        //return false;
      }
      else
      {
        // Update the local intersected triangles list
        std::cout << "Building AABB tree... ";
        this->buildAABBtree(this->m_triangles);
        std::cout
          << "Done" << std::endl
          << std::endl;
        return true;
      }

      #undef CMD
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool
    mesh::load(
      std::string const & path,
      real                friction
    )
    {
      #define CMD "enve::ground::load(...): "

      // Start loading mesh
      std::cout << "Loading *.obj mesh... ";

      // Check if the file is an ".obj" file
      if (path.substr(path.size() - 4, 4) != ".obj")
      {
        std::cout << "Failed" << std::endl;
        ENVE_ERROR(CMD "not a *.obj file.");
        //return false;
      }

      // Check if the file had been correctly open
      std::ifstream file(path);
      if (!file.is_open())
      {
        std::cout << "Failed" << std::endl;
        ENVE_ERROR(CMD "*.obj file not opened.");
        //return false;
      }

      // Vector for nodes coordinates
      std::vector<point> nodes;
      nodes.reserve(25000);
      this->m_triangles.reserve(100000);
      size_t nodes_count    = size_t(0);
      size_t elements_count = size_t(0);

      // Instantiate temporaries
      std::string curline, token;
      std::vector<std::string> s_node;
      s_node.reserve(4);
      std::vector<integer> i_element(3);
      point p_node;
      while (std::getline(file, curline))
      {
        token = this->firstToken(curline);
        if (token == "v")
        {
          // Generate a vertex position
          this->split(this->tail(curline), s_node, " ");
          ENVE_ASSERT(s_node.size() == size_t(3),
            CMD "wrong numbder of elements detected.");
          p_node[0] = std::stod(s_node[0]);
          p_node[1] = std::stod(s_node[1]);
          p_node[2] = std::stod(s_node[2]);
          nodes.push_back(p_node);
          ++nodes_count;
          continue;
        }
        else if (token == "f")
        {
          // Generate the triangle vertices from the element
          this->split(this->tail(curline), s_node, " ");
          ENVE_ASSERT(s_node.size() == size_t(3),
            CMD "wrong numbder of elements detected.");
          i_element[0] = std::stoi(s_node[0]) - 1;
          i_element[1] = std::stoi(s_node[1]) - 1;
          i_element[2] = std::stoi(s_node[2]) - 1;
          ENVE_ASSERT(i_element[0] >= integer(0),
            CMD "element 0 index cannot be negative.");
          ENVE_ASSERT(i_element[1] >= integer(0),
            CMD "element 1 index cannot be negative.");
          ENVE_ASSERT(i_element[2] >= integer(0),
            CMD "element 2 index cannot be negative.");

          // Create a shared pointer for the last triangle
          this->m_triangles.push_back(
            std::make_shared<triangleground const>(
              elements_count, friction,
              nodes[i_element[0]], nodes[i_element[1]], nodes[i_element[2]]
            ));
            ++elements_count;
          continue;
        }
        else if (token[0] == '%' || token[0] == '#' || token[0] == '\r')
        {
          // Check comments or empty lines
          continue;
        }
      }
      std::cout
        << "Done" << std::endl;

      // Perform safety check
      ENVE_ASSERT(nodes.size() == nodes_count && this->m_triangles.size() == elements_count,
        CMD "safety check not passed.");

      file.close();
      if (this->m_triangles.empty())
      {
        ENVE_ERROR(CMD "*.obj loaded mesh is empty.");
        //return false;
      }
      else
      {
        // Update the local intersected triangles list
        std::cout << "Building AABB tree... ";
        this->buildAABBtree(this->m_triangles);
        std::cout
          << "Done" << std::endl
          << std::endl;
        return true;
      }

      #undef CMD
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool
    mesh::intersection(
      aabb::ptr const          box,
      triangleground::vecptr & triangles
    )
      const
    {
      ENVE_DEBUG_TICTOC;

      #ifdef ENVE_USE_UTILS_AABBTREE

      ENVE_DEBUG_TIC;
      AABBset intersectList;
      real bbox[6];
      bbox[0] = box->min(0);
      bbox[1] = box->min(1);
      bbox[2] = box->min(2);
      bbox[3] = box->max(0);
      bbox[4] = box->max(1);
      bbox[5] = box->max(2);
      this->m_AABBtree.intersect_with_one_bbox( bbox, intersectList );
      ENVE_DEBUG_TOC;
      ENVE_MESSAGE_DEBUG(
        "mesh::intersection, intersect_with_one_bbox_and_refine, elapsed {}ms\n",
        tictoc.elapsed_ms()
      );

      ENVE_DEBUG_TIC;
      triangles.resize(intersectList.size());
      integer list = 0;
      for ( integer const & i : intersectList )
      {
        triangles[list] = this->m_triangles[i];
        ++list;
      }
      ENVE_DEBUG_TOC;
      ENVE_MESSAGE_DEBUG(
        "mesh::intersection, resize, elapsed {}ms\n",
        tictoc.elapsed_ms()
      );
      return list > integer(0);

      #else

      ENVE_DEBUG_TIC;
      aabb::vecptr ptrVecbox{box};
      AABBtree::ptr ptrAABBtree(std::make_shared<AABBtree>());
      ptrAABBtree->build(ptrVecbox);
      triangles.clear();
      aabb::vecpairptr intersection_list;
      this->m_AABBtree->intersection(*ptrAABBtree, intersection_list);
      for (size_t i = 0; i < intersection_list.size(); ++i)
        {triangles.emplace_back(this->ptrTriangleground((intersection_list[i].first)->id()));}
      ENVE_DEBUG_TOC;
      ENVE_MESSAGE_DEBUG(
        "mesh::intersection, intersect, elapsed {}ms (old)\n",
        tictoc.elapsed_ms()
      );

      return triangles.size() > size_t(0);

      #endif
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::buildAABBtree(
      triangleground::vecptr const & triangles
    )
    {

      ENVE_DEBUG_TICTOC;

      this->m_triangles = triangles;
      this->updateBBoxes();

      #ifdef ENVE_USE_UTILS_AABBTREE

      ENVE_DEBUG_TIC;
      this->m_AABBtree.set_max_num_objects_per_node( ENVE_AABBTREE_NODE_SIZE );
      this->m_AABBtree.allocate( triangles.size(), integer(3) );
      integer aabb_pos = 0;
      for ( triangleground::ptr tri : triangles )
      {
        this->m_AABBtree.replace_bbox(
          tri->bbox().min().data(),
          tri->bbox().max().data(),
          aabb_pos
        );
        ++aabb_pos;
      }
      this->m_AABBtree.build();
      ENVE_DEBUG_TOC;
      ENVE_MESSAGE_DEBUG(
        "mesh::buildAABBtree, build, elapsed {}ms\n",
        tictoc.elapsed_ms()
      );

      #else

      ENVE_DEBUG_TIC;
      this->m_AABBtree->build(this->m_bboxes);
      ENVE_DEBUG_TOC;
      ENVE_MESSAGE_DEBUG(
        "mesh::buildAABBtree, build, elapsed {}ms AABB old\n",
        tictoc.elapsed_ms()
      );

      #endif
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::updateBBoxes(void)
    {
      this->m_bboxes.clear();
      for (size_t i = 0; i < this->m_triangles.size(); ++i)
      {
        this->m_bboxes.push_back(
          std::make_shared<aabb const>(this->m_triangles[i]->bbox())
        );
      }
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::split(
      std::string              const & in,
      std::vector<std::string>       & out,
      std::string              const & token
    )
      const
    {
      std::string tmp, test;
      out.clear();
      for (size_t i = 0; i < in.size(); ++i)
      {
        test = in.substr(i, token.size());
        if (test == token)
        {
          if (!tmp.empty())
          {
            out.push_back(tmp);
            tmp.clear();
            i += token.size() - 1;
          }
        }
        else if (i + token.size() >= in.size())
        {
          tmp += in.substr(i, token.size());
          out.push_back(tmp);
          break;
        }
        else
        {
          tmp += in[i];
        }
      }
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    std::string
    mesh::tail(
      std::string const & in
    )
      const
    {
      size_t token_start = in.find_first_not_of(" \t");
      size_t space_start = in.find_first_of(" \t", token_start);
      size_t tail_start  = in.find_first_not_of(" \t", space_start);
      size_t tail_end    = in.find_last_not_of(" \t");
      if (tail_start != std::string::npos && tail_end != std::string::npos)
        {return in.substr(tail_start, tail_end - tail_start + 1);}
      else if (tail_start != std::string::npos)
        {return in.substr(tail_start);}
      return "";
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    std::string
    mesh::firstToken(
      std::string const & in
    )
      const
    {
      if (!in.empty())
      {
        size_t token_start = in.find_first_not_of(" \t\r\n");
        if (token_start != std::string::npos)
        {
          size_t token_end = in.find_first_of(" \t\r\n", token_start);
          if (token_end != std::string::npos)
            {return in.substr(token_start, token_end - token_start);}
          else
            {return in.substr(token_start);}
        }
      }
      return "";
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  } // namespace rdf

} // namespace enve

///
/// eof: mesh.cc
///
