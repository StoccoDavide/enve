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
/// file: mex_triangleground.cc
///

#include "acme.hh"
#include "enve.hh"
#include "mex_utils.hh"

#define ASSERT(COND, MSG)                         \
  if (!(COND))                                    \
  {                                               \
    std::ostringstream ost;                       \
    ost << "mex_triangleground: " << MSG << "\n"; \
    mexErrMsgTxt(ost.str().c_str());              \
  }

#define MEX_ERROR_MESSAGE                                                     \
  "%=====================================================================%\n" \
  "% mex_triangleground: Mex wrapper for ENVE triangleground object.     %\n" \
  "%                                                                     %\n" \
  "% CONSTRUCTORS:                                                       %\n" \
  "%   OUT = mex_triangleground( 'new' );                                %\n" \
  "%   OUT = mex_triangleground( 'new',                                  %\n" \
  "%                           ID,        : Triangleground ID            %\n" \
  "%                           MU,        : Triangleground face friction %\n" \
  "%                           [X; Y; Z], : Triangleground point 1       %\n" \
  "%                           [X; Y; Z], : Triangleground point 2       %\n" \
  "%                           [X; Y; Z]  : Triangleground point 3       %\n" \
  "%                         );                                          %\n" \
  "%   OUT = mex_triangleground( 'new',                                  %\n" \
  "%                           ID,  : Triangleground ID                  %\n" \
  "%                           MU,  : Triangleground face friction       %\n" \
  "%                           V1X, : Triangleground vertex 1 x value    %\n" \
  "%                           V1Y, : Triangleground vertex 1 y value    %\n" \
  "%                           V1Z, : Triangleground vertex 1 z value    %\n" \
  "%                           V2X, : Triangleground vertex 2 x value    %\n" \
  "%                           V2Y, : Triangleground vertex 2 y value    %\n" \
  "%                           V2Z, : Triangleground vertex 2 z value    %\n" \
  "%                           V3X, : Triangleground vertex 3 x value    %\n" \
  "%                           V3Y, : Triangleground vertex 3 y value    %\n" \
  "%                           V3Z  : Triangleground vertex 3 z value    %\n" \
  "%                         );                                          %\n" \
  "%                                                                     %\n" \
  "% DESTRUCTOR:                                                         %\n" \
  "%   mex_triangleground( 'delete', OBJ );                              %\n" \
  "%                                                                     %\n" \
  "% USAGE:                                                              %\n" \
  "%   OUT = mex_triangleground( 'getID', OBJ );                         %\n" \
  "%         mex_triangleground( 'setID', OBJ, ID );                     %\n" \
  "%   OUT = mex_triangleground( 'getFriction', OBJ );                   %\n" \
  "%         mex_triangleground( 'setFriction', OBJ, MU );               %\n" \
  "%   OUT = mex_triangleground( 'getVertex1', OBJ );                    %\n" \
  "%   OUT = mex_triangleground( 'getVertex2', OBJ );                    %\n" \
  "%   OUT = mex_triangleground( 'getVertex3', OBJ );                    %\n" \
  "%         mex_triangleground( 'setVertex1', OBJ, OTHER_OBJ );         %\n" \
  "%         mex_triangleground( 'setVertex2', OBJ, OTHER_OBJ );         %\n" \
  "%         mex_triangleground( 'setVertex3', OBJ, OTHER_OBJ );         %\n" \
  "%         mex_triangleground( 'copy', OBJ, OTHER_OBJ );               %\n" \
  "%   OUT = mex_triangleground( 'normal', OBJ );                        %\n" \
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
  mxArray             *&mx_id,
  enve::triangleground *ptr)
{
  mx_id = convertPtr2Mat<enve::triangleground>(ptr);
}

static inline enve::triangleground *
DATA_GET(
  mxArray const *&mx_id)
{
  return convertMat2Ptr<enve::triangleground>(mx_id);
}

static void
DATA_DELETE(
  mxArray const *&mx_id)
{
  destroyObject<enve::triangleground>(mx_id);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_new(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{

#define CMD "mex_triangleground( 'new', [, args] ): "
  MEX_ASSERT(nrhs == 1 || nrhs == 6, CMD "expected 1 or 6 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  MEX_ASSERT(
    mxIsChar(arg_in_0),
    CMD << "first argument must be a string, found ``" << mxGetClassName(arg_in_0) << "''\n");
  string tname = mxArrayToString(arg_in_0);

  real_type id = acme::integer(0);
  real_type mu = acme::QUIET_NAN;
  real_type x1 = acme::QUIET_NAN;
  real_type y1 = acme::QUIET_NAN;
  real_type z1 = acme::QUIET_NAN;
  real_type x2 = acme::QUIET_NAN;
  real_type y2 = acme::QUIET_NAN;
  real_type z2 = acme::QUIET_NAN;
  real_type x3 = acme::QUIET_NAN;
  real_type y3 = acme::QUIET_NAN;
  real_type z3 = acme::QUIET_NAN;

  if (nrhs == 6)
  {
    id = getInt(arg_in_1, CMD "error in reading 1st input value");
    mu = getScalarValue(arg_in_2, CMD "error in reading 2nd input value");
    real_type const *matrix1_ptr;
    mwSize           rows1, cols1;
    matrix1_ptr = getMatrixPointer(arg_in_3, rows1, cols1, CMD "error in reading 3rd input matrix");
    MEX_ASSERT(rows1 == 3 || cols1 == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows1 << ", cols = " << cols1 << "\n");
    x1 = matrix1_ptr[0];
    y1 = matrix1_ptr[1];
    z1 = matrix1_ptr[2];
    real_type const *matrix2_ptr;
    mwSize           rows2, cols2;
    matrix2_ptr = getMatrixPointer(arg_in_4, rows2, cols2, CMD "error in reading 4th input matrix");
    MEX_ASSERT(rows2 == 3 || cols2 == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows2 << ", cols = " << cols2 << "\n");
    x2 = matrix2_ptr[0];
    y2 = matrix2_ptr[1];
    z2 = matrix2_ptr[2];
    real_type const *matrix3_ptr;
    mwSize           rows3, cols3;
    matrix3_ptr = getMatrixPointer(arg_in_5, rows3, cols3, CMD "error in reading 5th input matrix");
    MEX_ASSERT(rows3 == 3 || cols3 == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows3 << ", cols = " << cols3 << "\n");
    x3 = matrix3_ptr[0];
    y3 = matrix3_ptr[1];
    z3 = matrix3_ptr[2];
  }

  enve::triangleground *ptr = new enve::triangleground(id, mu, acme::point(x1, y1, z1), acme::point(x2, y2, z2), acme::point(x3, y3, z3));
  DATA_NEW(arg_out_0, ptr);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_delete(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{

#define CMD "mex_triangleground( 'delete', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

  DATA_DELETE(arg_in_1);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getID(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{

#define CMD "mex_triangleground( 'getID', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::triangleground *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->id());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getFriction(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{

#define CMD "mex_triangleground( 'getFriction', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::triangleground *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->friction());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getVertex1(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{

#define CMD "mex_triangleground( 'getVertex1', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::triangleground *self = DATA_GET(arg_in_1);
  acme::point          *out  = new acme::point(self->triangle::vertex(0));
  arg_out_0                  = convertPtr2Mat<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getVertex2(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{

#define CMD "mex_triangleground( 'getVertex2', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::triangleground *self = DATA_GET(arg_in_1);
  acme::point          *out  = new acme::point(self->triangle::vertex(1));
  arg_out_0                  = convertPtr2Mat<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getVertex3(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{

#define CMD "mex_triangleground( 'getVertex3', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::triangleground *self = DATA_GET(arg_in_1);
  acme::point          *out  = new acme::point(self->triangle::vertex(2));
  arg_out_0                  = convertPtr2Mat<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_copy(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{

#define CMD "mex_triangleground( 'copy', OBJ, OTHER_OBJ ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

  enve::triangleground *self  = DATA_GET(arg_in_1);
  enve::triangleground *other = DATA_GET(arg_in_2);
  self->copy(*other);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_normal(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_triangleground( 'normal', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::triangleground *self   = DATA_GET(arg_in_1);
  real_type            *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3            outvec(self->normal());
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef void (*DO_CMD)(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[]);

static map<string, DO_CMD> cmd_to_fun = {
  {"new",         do_new},
  {"delete",      do_delete},
  {"getID",       do_getID},
  {"getFriction", do_getFriction},
  {"getVertex1",  do_getVertex1},
  {"getVertex2",  do_getVertex2},
  {"getVertex3",  do_getVertex3},
  {"copy",        do_copy},
  {"normal",      do_normal}};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

extern "C" void
mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
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
    string cmd  = mxArrayToString(arg_in_0);
    DO_CMD pfun = cmd_to_fun.at(cmd);
    pfun(nlhs, plhs, nrhs, prhs);
  }
  catch (exception const &e)
  {
    mexErrMsgTxt((string("mex_triangleground Error: ") + e.what()).c_str());
  }
  catch (...)
  {
    mexErrMsgTxt("mex_triangleground failed\n");
  }
}

///
/// eof: mex_trianglegroung.cc
///
