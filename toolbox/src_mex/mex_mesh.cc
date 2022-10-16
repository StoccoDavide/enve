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
/// file: mex_mesh.cc
///

#include "acme.hh"
#include "enve.hh"
#include "mex_utils.hh"

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
  "%                   ground_FILE : Path to ground file as string       %\n" \
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
  "% Copyright (c) 2022, Davide Stocco. All rights reserved.             %\n" \
  "%                                                                     %\n" \
  "% The ENVE project can not be copied and/or distributed without       %\n" \
  "% the express permission of Davide Stocco.                            %\n" \
  "%                                                                     %\n" \
  "%    Davide Stocco                                                    %\n" \
  "%    Department of Industrial Engineering                             %\n" \
  "%    University of Trento                                             %\n" \
  "%    e-mail: davide.stocco@unitn.it                                   %\n" \
  "%                                                                     %\n" \
  "%=====================================================================%\n"

using namespace std;

typedef double real_type;

static void
DATA_NEW(
    mxArray *&mx_id,
    enve::ground::mesh *ptr)
{
  mx_id = convertPtr2Mat<enve::ground::mesh>(ptr);
}

static inline enve::ground::mesh *
DATA_GET(
    mxArray const *&mx_id)
{
  return convertMat2Ptr<enve::ground::mesh>(mx_id);
}

static void
DATA_DELETE(
    mxArray const *&mx_id)
{
  destroyObject<enve::ground::mesh>(mx_id);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_new(int nlhs, mxArray *plhs[],
       int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'new', [, args] ): "
  MEX_ASSERT(nrhs == 1 || nrhs == 2 || nrhs == 3, CMD "expected 1, 2 or 3 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  MEX_ASSERT(
      mxIsChar(arg_in_0),
      CMD << "first argument must be a string, found ``" << mxGetClassName(arg_in_0) << "''\n");

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
    if (path.substr(path.size() - 4, 4) != ".obj")
    {
      std::cout << "Cannot load: not a *.rdf or *.obj file!" << std::endl;
    }
    else
    {
      real_type friction = getScalarValue(arg_in_2, CMD "error in reading input value");
      self->load(path, friction);
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
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

  DATA_DELETE(arg_in_1);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getTriangleground(int nlhs, mxArray *plhs[],
                   int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'getTriangleground', OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::ground::mesh *self = DATA_GET(arg_in_1);
  int i = getInt(arg_in_2, CMD "error in reading input value");
  enve::triangleground *out = new enve::triangleground();
  out->copy(*self->ptrTriangleground(i - 1));
  arg_out_0 = convertPtr2Mat<enve::triangleground>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_size(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'size', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::ground::mesh *self = DATA_GET(arg_in_1);
  setScalarInt(arg_out_0, self->size());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_copy(int nlhs, mxArray *plhs[],
        int nrhs, mxArray const *prhs[])
{
#define CMD "mex_mesh( 'copy', OBJ, OTHER_OBJ ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

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
  MEX_ASSERT(nrhs == 3 || nrhs == 4, CMD "expected 3 or 4 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

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
      real_type friction = getScalarValue(arg_in_3, CMD "error in reading input value");
      self->load(path, friction);
    }
  }
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef void (*DO_CMD)(int nlhs, mxArray *plhs[],
                       int nrhs, mxArray const *prhs[]);

static map<string, DO_CMD> cmd_to_fun = {
    {"new",               do_new},
    {"delete",            do_delete},
    {"getTriangleground", do_getTriangleground},
    {"size",              do_size},
    {"copy",              do_copy},
    {"load",              do_load}};

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
    MEX_ASSERT(mxIsChar(arg_in_0), "first argument must be a string\n");
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
