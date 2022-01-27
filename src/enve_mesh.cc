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
/// file: enve_mesh.cc
///

#include "enve_mesh.hh"

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

    mesh::~mesh(void)
    {
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    mesh::mesh(void)
      : m_AABBtree(std::make_shared<AABBtree>())
    {
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    mesh::mesh(
      triangleground::vecptr const &triangles)
      : mesh()
    {
      this->m_triangles = triangles;
      this->updateBBoxes();
      this->m_AABBtree->build(this->m_bboxes);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    mesh::mesh(
      std::string const &path)
      : mesh()
    {
      bool load_bool = load(path);
      ENVE_ASSERT(load_bool, "Error while reading file\n");
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    mesh::mesh(
      std::string const &path,
      real               friction)
      : mesh()
    {
      bool load_bool = load(path, friction);
      ENVE_ASSERT(load_bool, "Error while reading file\n");
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::copy(
      mesh const &mesh_in)
    {
      this->m_triangles = mesh_in.m_triangles;
      this->m_bboxes    = mesh_in.m_bboxes;
      this->m_AABBtree  = mesh_in.m_AABBtree;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::clear(void)
    {
      if (!this->m_bboxes.empty())
      {
        for (size_t i = 0; i < this->size(); ++i)
          this->m_bboxes[i].reset();
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
      size_t i)
      const
    {
      return this->m_triangles[i];
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    AABBtree::ptr const
    mesh::ptrAABBtree(void)
      const
    {
      return this->m_AABBtree;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::print(
      std::string const &path)
      const
    {
      // Create Out.txt
      std::ofstream file(path);
      // Print introduction
      file
        << "LOADED RDF MESH DATA" << std::endl
        << std::endl
        << "Legend:" << std::endl
        << "Vi : i-th vertex" << std::endl
        << "N  : normal to the face" << std::endl
        << "F  : friction coefficient" << std::endl
        << std::endl;
      for (size_t i = 0; i < this->m_triangles.size(); ++i)
      {
        triangleground const &Ti = *this->m_triangles[i];
        point const          &V0 = Ti.triangle::vertex(0);
        point const          &V1 = Ti.triangle::vertex(1);
        point const          &V2 = Ti.triangle::vertex(2);
        vec3 const           &N  = Ti.normal();
        // Print vertices, normal and friction
        file << "TRIANGLE " << i << std::endl
             << "V0 = [ " << V0.x() << ", " << V0.y() << ", " << V0.z() << " ]" << std::endl
             << "V1 = [ " << V1.x() << ", " << V1.y() << ", " << V1.z() << " ]" << std::endl
             << "V2 = [ " << V2.x() << ", " << V2.y() << ", " << V2.z() << " ]" << std::endl
             << "N  = [ " << N.x() << ", " << N.y() << ", " << N.z() << " ]" << std::endl
             << "F  = " << Ti.friction() << std::endl
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
      std::string const &path
    )
    {
      // Check if the file is an ".rdf" file, if not return false
      if (path.substr(path.size() - 4, 4) != ".rdf")
      {
        std::cerr << "enve::load(path): not a *.rdf file!" << std::endl;
        return false;
      }
      // Check if the file had been correctly open, if not return false
      std::ifstream file(path);
      if (!file.is_open())
      {
        std::cerr << "enve::load(path): rdf file not opened" << std::endl;
        return false;
      }
      // Vector for nodes coordinates
      std::vector<point> nodes;
      bool               nodes_parse    = false;
      bool               elements_parse = false;

#ifdef ENVE_CONSOLE_OUTPUT
      const size_t output_every     = 5000;
      size_t       output_indicator = output_every;
#endif
      std::string curline;
      while (std::getline(file, curline))
      {
#ifdef ENVE_CONSOLE_OUTPUT
        if ((output_indicator = ((output_indicator + 1) % output_every)) == 1)
        {
          std::cout
            << "\rLoading mesh... "
            << this->m_triangles.size()
            << " triangles detected " << std::endl;
        }
#endif
        std::string token = this->firstToken(curline);
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
          std::vector<std::string> spos;
          point                    vpos;
          this->split(this->tail(curline), spos, " ");
          vpos[0] = std::stod(spos[0]);
          vpos[1] = std::stod(spos[1]);
          vpos[2] = std::stod(spos[2]);
          nodes.push_back(vpos);
        }
        // Generate a face (vertices & indices)
        if (elements_parse)
        {
          // Generate the triangle vertices from the elements
          std::vector<std::string> spos;
          std::vector<integer>     ipos(3);
          real ifriction;
          this->split(curline, spos, " ");
          ipos[0]   = std::stoi(spos[0]) - 1;
          ipos[1]   = std::stoi(spos[1]) - 1;
          ipos[2]   = std::stoi(spos[2]) - 1;
          ifriction = std::stod(spos[3]);
          ENVE_ASSERT(ipos[0] >= 0, "enve::ground::load(path): element 0 index cannot be negative\n");
          ENVE_ASSERT(ipos[1] >= 0, "enve::ground::load(path): element 1 index cannot be negative\n");
          ENVE_ASSERT(ipos[2] >= 0, "enve::ground::load(path): element 2 index cannot be negative\n");
          ENVE_ASSERT(ifriction >= 0, "enve::ground::load(path): element friction cannot be negative\n");

          // Create a shared pointer for the last triangle and push it in the pointer vector
          this->m_triangles.push_back(std::make_shared<triangleground const>(nodes[ipos[0]], 
                                                                             nodes[ipos[1]], 
                                                                             nodes[ipos[2]], 
                                                                             ifriction));
          continue;
        }
      }
#ifdef ENVE_CONSOLE_OUTPUT
      std::cout << std::endl;
#endif
      file.close();
      if (this->m_triangles.empty())
      {
        perror("Loaded mesh is empty");
        return false;
      }
      else
      {
        // Update the local intersected triangles list
#ifdef ENVE_CONSOLE_OUTPUT
        std::cout << "Building AABB tree... ";
#endif
        this->updateBBoxes();
        this->m_AABBtree->build(this->m_bboxes);
#ifdef ENVE_CONSOLE_OUTPUT
        std::cout << "Done" << std::endl
                  << std::endl;
#endif
        return true;
      }
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool
    mesh::load(
      std::string const &path,
      real               friction
    )
    {
      // Check if the file is an ".obj" file, if not return false
      if (path.substr(path.size() - 4, 4) != ".obj")
      {
        std::cerr << "enve::load(path, friction): not a *.obj file!" << std::endl;
        return false;
      }
      // Check if the file had been correctly open, if not return false
      std::ifstream file(path);
      if (!file.is_open())
      {
        std::cerr << "enve::load(path, friction): obj file not opened" << std::endl;
        return false;
      }
      // Vector for nodes coordinates
      std::vector<point> nodes;

#ifdef ENVE_CONSOLE_OUTPUT
      const size_t output_every     = 5000;
      size_t       output_indicator = output_every;
#endif
      std::string curline;
      while (std::getline(file, curline))
      {
#ifdef ENVE_CONSOLE_OUTPUT
        if ((output_indicator = ((output_indicator + 1) % output_every)) == 1)
        {
          std::cout
            << "\rLoading mesh... "
            << this->m_triangles.size()
            << " triangles detected " << std::endl;
        }
#endif
        std::string token = this->firstToken(curline);
        if (token == "v")
        {
          // Generate a vertex position
          std::vector<std::string> spos;
          point                    vpos;
          this->split(this->tail(curline), spos, " ");
          vpos[0] = std::stod(spos[0]);
          vpos[1] = std::stod(spos[1]);
          vpos[2] = std::stod(spos[2]);
          nodes.push_back(vpos);
          continue;
        }
        else if (token == "f")
        {
          // Generate the triangle vertices from the elements
          std::vector<std::string> spos;
          std::vector<integer>     ipos(3);
          this->split(this->tail(curline), spos, " ");
          ipos[0] = std::stoi(spos[0]) - 1;
          ipos[1] = std::stoi(spos[1]) - 1;
          ipos[2] = std::stoi(spos[2]) - 1;
          ENVE_ASSERT(ipos[0] >= 0, "enve::ground::load(path, friction): element 0 index cannot be negative\n");
          ENVE_ASSERT(ipos[1] >= 0, "enve::ground::load(path, friction): element 1 index cannot be negative\n");
          ENVE_ASSERT(ipos[2] >= 0, "enve::ground::load(path, friction): element 2 index cannot be negative\n");

          // Create a shared pointer for the last triangle and push it in the pointer vector
          this->m_triangles.push_back(std::make_shared<triangleground const>(nodes[ipos[0]], 
                                                                             nodes[ipos[1]], 
                                                                             nodes[ipos[2]], 
                                                                             friction));
          continue;
        }
        else if (token[0] == '%' || token[0] == '#' || token[0] == '\r')
        {
          // Check comments or empty lines
          continue;
        }
      }
#ifdef ENVE_CONSOLE_OUTPUT
      std::cout << std::endl;
#endif
      file.close();
      if (this->m_triangles.empty())
      {
        perror("Loaded mesh is empty");
        return false;
      }
      else
      {
        // Update the local intersected triangles list
#ifdef ENVE_CONSOLE_OUTPUT
        std::cout << "Building AABB tree... ";
#endif
        this->updateBBoxes();
        this->m_AABBtree->build(this->m_bboxes);
#ifdef ENVE_CONSOLE_OUTPUT
        std::cout << "Done" << std::endl
                  << std::endl;
#endif
        return true;
      }
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool
    mesh::intersection(
      AABBtree::ptr const     ptrAABBtree,
      triangleground::vecptr &triangles)
      const
    {
      triangles.clear();
      aabb::vecpairptr intersection_list;
      this->m_AABBtree->intersection(*ptrAABBtree, intersection_list);
      for (size_t i = 0; i < intersection_list.size(); ++i)
        triangles.emplace_back(this->ptrTriangleground((intersection_list[i].first)->id()));
      return triangles.size() > 0;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool
    mesh::intersection(
      aabb::vecptr const     &ptrVecbox,
      triangleground::vecptr &triangles)
      const
    {
      AABBtree::ptr ptrAABBtree(std::make_shared<AABBtree>());
      ptrAABBtree->build(ptrVecbox);
      return this->intersection(ptrAABBtree, triangles);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    bool
    mesh::intersection(
      aabb::ptr const         ptrbox,
      triangleground::vecptr &triangles)
      const
    {
      aabb::vecptr ptrVecbox;
      ptrVecbox.push_back(ptrbox);
      return this->intersection(ptrVecbox, triangles);
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::updateBBoxes(void)
    {
      this->m_bboxes.clear();
      aabb ibox;
      for (size_t i = 0; i < this->m_triangles.size(); ++i)
      {
        ibox = this->m_triangles[i]->bbox();
        this->m_bboxes.push_back(std::make_shared<aabb>(ibox.min(0), ibox.min(1), ibox.min(2), ibox.max(0), ibox.max(1), ibox.max(2), i, 0));
        ibox.clear();
      }
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    void
    mesh::split(
      std::string const        &in,
      std::vector<std::string> &out,
      std::string const        &token)
      const
    {
      out.clear();
      std::string tmp;

      for (size_t i = 0; i < in.size(); ++i)
      {
        std::string test = in.substr(i, token.size());
        if (test == token)
        {
          if (!tmp.empty())
          {
            out.push_back(tmp);
            tmp.clear();
            i += token.size() - 1;
          }
          else
          {
            //out.push_back("");
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
      std::string const &in)
      const
    {
      size_t token_start = in.find_first_not_of(" \t");
      size_t space_start = in.find_first_of(" \t", token_start);
      size_t tail_start  = in.find_first_not_of(" \t", space_start);
      size_t tail_end    = in.find_last_not_of(" \t");
      if (tail_start != std::string::npos && tail_end != std::string::npos)
      {
        return in.substr(tail_start, tail_end - tail_start + 1);
      }
      else if (tail_start != std::string::npos)
      {
        return in.substr(tail_start);
      }
      return "";
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    std::string
    mesh::firstToken(
      std::string const &in)
      const
    {
      if (!in.empty())
      {
        size_t token_start = in.find_first_not_of(" \t\r\n");
        if (token_start != std::string::npos)
        {
          size_t token_end = in.find_first_of(" \t\r\n", token_start);
          if (token_end != std::string::npos)
          {
            return in.substr(token_start, token_end - token_start);
          }
          else
          {
            return in.substr(token_start);
          }
        }
      }
      return "";
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  } // namespace rdf

} // namespace enve

///
/// eof: enve_mesh.cc
///
