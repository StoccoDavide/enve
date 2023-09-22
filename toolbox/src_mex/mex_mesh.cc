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
/// file: mex_mesh.cc
///

#include "mex_utils.hh"
#include "acme.hh"
#include "enve.hh"

#define ASSERT(COND, MSG)               \
  if (!(COND))                          \
  {                                     \
    std::ostringstream ost;             \
    ost << "mex_mesh: " << MSG << "\n"; \
    mexErrMsgTxt(ost.str().c_str());    \
  }

#define MEX_ERROR_MESSAGE                                                     \
  "%=====================================================================%\n" \
  "% mex_mesh: Mex wrapper for ENVE mesh object.                         %\n" \
  "%                                                                     %\n" \
  "% CONSTRUCTORS:                                                       %\n" \
  "%   OUT = mex_mesh( 'new',                                            %\n" \
  "%                   path : Path to ground file as string,             %\n" \
  "%                   pose : Pose of the mesh as 4x4 matrix             %\n" \
  "%                 );                                                  %\n" \
  "%                                                                     %\n" \
  "% DESTRUCTOR:                                                         %\n" \
  "%   mex_mesh( 'delete', OBJ );                                        %\n" \
  "%                                                                     %\n" \
  "% USAGE:                                                              %\n" \
  "%   OUT = mex_mesh( 'normal', OBJ );                                  %\n" \
  "%   OUT = mex_mesh( 'getTriangleground', OBJ, I );                    %\n" \
  "%   OUT = mex_mesh( 'size', OBJ );                                    %\n" \
  "%         mex_mesh( 'copy', OBJ, OTHER_OBJ );                         %\n" \
  "%         mex_mesh( 'load', OBJ, PATH, [, FRICTION] );                %\n" \
  "%                                                                     %\n" \
  "%=====================================================================%\n" \
  "%                                                                     %\n" \
  "% This file is part of the ENVE project.                              %\n" \
  "%                                                                     %\n" \
  "% Copyright (c) 2020, Davide Stocco, Matteo Larcher and Enrico        %\n" \
  "% Bertolazzi.                                                         %\n" \
  "%                                                                     %\n" \
  "% The ENVE project and its components are supplied under the terms of %\n" \
  "% the open source BSD 3-Clause License. The contents of the ENVE      %\n" \
  "% project and its components may not be copied or disclosed except in %\n" \
  "% accordance with the terms of the BSD 3-Clause License.              %\n" \
  "%                                                                     %\n" \
  "%    Davide Stocco                                                    %\n" \
  "%    Department of Industrial Engineering                             %\n" \
  "%    University of Trento                                             %\n" \
  "%    e-mail: davide.stocco@unitn.it                                   %\n" \
  "%                                                                     %\n" \
  "%    Enrico Bertolazzi                                                %\n" \
  "%    Department of Industrial Engineering                             %\n" \
  "%    University of Trento                                             %\n" \
  "%    e-mail: enrico.bertolazzi@unitn.it                               %\n" \
  "%                                                                     %\n" \
  "%=====================================================================%\n"

using namespace std;

typedef double real_type;

static void
DATA_NEW(
    mxArray *&mx_id,
    enve::ground::mesh *ptr)
{
  mx_id = utils::mex_convert_ptr_to_mx<enve::ground::mesh>(ptr);
}

static inline enve::ground::mesh *
DATA_GET(
    mxArray const *&mx_id)
{
  return utils::mex_convert_mx_to_ptr<enve::ground::mesh>(mx_id);
}

static void
DATA_DELETE(
    mxArray const *&mx_id)
{
  utils::mex_destroy_object<enve::ground::mesh>(mx_id);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_new(int nlhs, mxArray *plhs[],
       int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'new', [, args] ): "
  UTILS_MEX_ASSERT(nrhs == 1 || nrhs == 2 || nrhs == 3 || nrhs == 4, CMD "expected 1, 2, 3 or 4 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  UTILS_MEX_ASSERT(
      mxIsChar(arg_in_0),
      CMD "first argument must be a string, found " << mxGetClassName(arg_in_0) << "\n");

  enve::ground::mesh *self = new enve::ground::mesh();

  if (nrhs == 2)
  {
    string path = mxArrayToString(arg_in_1);
    if (path.substr(path.size() - 4, 4) != ".rdf")
      std::cout << "Cannot load: not a *.rdf or *.obj file!" << std::endl;
    else
      self->load(path);
  }
  else if (nrhs == 3)
  {
    string path = mxArrayToString(arg_in_1);
    if (path.substr(path.size() - 4, 4) == ".obj" && mxIsScalar(arg_in_2))
    {
      real_type friction = utils::mex_get_scalar_value(arg_in_2, CMD "error in reading friction coefficient value");
      self->load(path, friction);
    }
    else if (path.substr(path.size() - 4, 4) == ".rdf")
    {
      mwSize rows, cols;
      real_type const *matrix_ptr;
      matrix_ptr = utils::mex_matrix_pointer(arg_in_2, rows, cols, CMD "error in reading affine transformation matrix");
      UTILS_MEX_ASSERT(rows == 4 || cols == 4, CMD "expected rows = 4 and cols = 4 found, rows = " << rows << ", cols = " << cols << "\n");
      acme::affine pose;
      pose.matrix() << matrix_ptr[0], matrix_ptr[4], matrix_ptr[8],  matrix_ptr[12],
                       matrix_ptr[1], matrix_ptr[5], matrix_ptr[9],  matrix_ptr[13],
                       matrix_ptr[2], matrix_ptr[6], matrix_ptr[10], matrix_ptr[14],
                       matrix_ptr[3], matrix_ptr[7], matrix_ptr[11], matrix_ptr[15];
      self->load(path, pose);
    }
    else
    {
      std::cout << "Wrong input arguments!" << std::endl;
    }
  }
  else if (nrhs == 4)
  {
    string path = mxArrayToString(arg_in_1);
    real_type friction = utils::mex_get_scalar_value(arg_in_2, CMD "error in reading friction coefficient value");
    mwSize rows, cols;
    real_type const *matrix_ptr;
    matrix_ptr = utils::mex_matrix_pointer(arg_in_3, rows, cols, CMD "error in second input matrix");
    if (path.substr(path.size() - 4, 4) == ".obj" && rows == 4 && cols == 4)
    {
      acme::affine pose;
      pose.matrix() << matrix_ptr[0], matrix_ptr[4], matrix_ptr[8],  matrix_ptr[12],
                       matrix_ptr[1], matrix_ptr[5], matrix_ptr[9],  matrix_ptr[13],
                       matrix_ptr[2], matrix_ptr[6], matrix_ptr[10], matrix_ptr[14],
                       matrix_ptr[3], matrix_ptr[7], matrix_ptr[11], matrix_ptr[15];
      self->load(path, friction, pose);
    }
    else
    {
      std::cout << "Wrong input arguments!" << std::endl;
    }
  }

  DATA_NEW(arg_out_0, self);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_delete(int nlhs, mxArray *plhs[],
          int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'delete', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

  DATA_DELETE(arg_in_1);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getTriangleground(int nlhs, mxArray *plhs[],
                     int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'getTriangleground', OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::ground::mesh *self = DATA_GET(arg_in_1);
  int i = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  enve::triangleground *out = new enve::triangleground();
  out->copy(*self->ptrTriangleground(i - 1));
  arg_out_0 = utils::mex_convert_ptr_to_mx<enve::triangleground>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getTrianglegroundVertices(int nlhs, mxArray *plhs[],
                             int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'do_getTrianglegroundVertices', OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::ground::mesh *self = DATA_GET(arg_in_1);
  int i = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  enve::triangleground *tmp = new enve::triangleground();
  tmp->copy(*self->ptrTriangleground(i - 1));
  real_type *output = utils::mex_create_matrix_value(arg_out_0, 3, 3);
  output[0] = tmp->triangle::vertex(0).x();
  output[1] = tmp->triangle::vertex(0).y();
  output[2] = tmp->triangle::vertex(0).z();
  output[3] = tmp->triangle::vertex(1).x();
  output[4] = tmp->triangle::vertex(1).y();
  output[5] = tmp->triangle::vertex(1).z();
  output[6] = tmp->triangle::vertex(2).x();
  output[7] = tmp->triangle::vertex(2).y();
  output[8] = tmp->triangle::vertex(2).z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_size(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'size', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::ground::mesh *self = DATA_GET(arg_in_1);
  utils::mex_set_scalar_int64(arg_out_0, self->size());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_copy(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'copy', OBJ, OTHER_OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

  enve::ground::mesh *self = DATA_GET(arg_in_1);
  enve::ground::mesh *other = DATA_GET(arg_in_2);
  self->copy(*other);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_load(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'load', OBJ, PATH, [, FRICTION] ): "
  UTILS_MEX_ASSERT(nrhs == 3 || nrhs == 4, CMD "expected 3 or 4 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::ground::mesh *self = DATA_GET(arg_in_1);
  string path = mxArrayToString(arg_in_2);

  if (nrhs == 3)
  {
    if (path.substr(path.size() - 4, 4) != ".rdf")
      std::cout << "Cannot load: not a *.rdf or *.obj file!" << std::endl;
    else
      self->load(path);
  }
  else if (nrhs == 4)
  {
    if (path.substr(path.size() - 4, 4) != ".obj")
    {
      std::cout << "Cannot load: not a *.rdf or *.obj file!" << std::endl;
    }
    else
    {
      real_type friction = utils::mex_get_scalar_value(arg_in_3, CMD "error in reading input value");
      self->load(path, friction);
    }
  }
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef void (*DO_CMD)(int nlhs, mxArray *plhs[],
                       int nrhs, mxArray const *prhs[]);

static map<string, DO_CMD> cmd_to_fun = {
    {"new", do_new},
    {"delete", do_delete},
    {"getTriangleground", do_getTriangleground},
    {"getTrianglegroundVertices", do_getTrianglegroundVertices},
    {"size", do_size},
    {"copy", do_copy},
    {"load", do_load}};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

extern "C" void
mexFunction(int nlhs, mxArray *plhs[],
            int nrhs, mxArray const *prhs[])
{
  // First argument must be a string
  if (nrhs == 0)
  {
    mexErrMsgTxt(MEX_ERROR_MESSAGE);
    return;
  }

  try
  {
    UTILS_MEX_ASSERT(mxIsChar(arg_in_0), "first argument must be a string\n");
    string cmd = mxArrayToString(arg_in_0);
    DO_CMD pfun = cmd_to_fun.at(cmd);
    pfun(nlhs, plhs, nrhs, prhs);
  }
  catch (exception const &e)
  {
    mexErrMsgTxt((string("mex_mesh Error: ") + e.what()).c_str());
  }
  catch (...)
  {
    mexErrMsgTxt("mex_mesh failed\n");
  }
}

///
/// eof: mex_mesh.cc
///
