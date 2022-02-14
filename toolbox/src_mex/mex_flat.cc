/*
(***********************************************************************)
(*                                                                     *)
(* The ENVE project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *)
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

#include "acme.hh"
#include "acme_plane.hh"
#include "enve_flat.hh"
#include "mex_utils.hh"

#define ASSERT(COND, MSG)               \
  if (!(COND))                          \
  {                                     \
    std::ostringstream ost;             \
    ost << "mex_flat: " << MSG << '\n'; \
    mexErrMsgTxt(ost.str().c_str());    \
  }

#define MEX_ERROR_MESSAGE                                                     \
  "%=====================================================================%\n" \
  "% mex_flat: Mex wrapper for ENVE flat object.                         %\n" \
  "%                                                                     %\n" \
  "% CONSTRUCTORS:                                                       %\n" \
  "%   obj = mex_flat( 'new' );                                          %\n" \
  "%   obj = mex_flat( 'new',                                            %\n" \
  "%                    [X; Y; Z], : Ground plane origin                 %\n" \
  "%                    [X; Y; Z], : Ground plane normal                 %\n" \
  "%                    FRICTION  : Ground plane friction                %\n" \
  "%                   );                                                %\n" \
  "%                                                                     %\n" \
  "% DESTRUCTOR:                                                         %\n" \
  "%   mex_flat( 'delete', OBJ );                                        %\n" \
  "%                                                                     %\n" \
  "% USAGE:                                                              %\n" \
  "%   OUT = mex_flat( 'getOrigin', OBJ );                               %\n" \
  "%         mex_flat( 'setOrigin', OBJ, OTHER_OBJ );                    %\n" \
  "%   OUT = mex_flat( 'getNormal', OBJ );                               %\n" \
  "%         mex_flat( 'setNormal', OBJ, OTHER_OBJ );                    %\n" \
  "%   OUT = mex_flat( 'getPlane', OBJ, OTHER_OBJ );                     %\n" \
  "%         mex_flat( 'setPlane', OBJ, OTHER_OBJ );                     %\n" \
  "%   OUT = mex_flat( 'getFriction', OBJ );                             %\n" \
  "%         mex_flat( 'setFriction', OBJ, FRICTION );                   %\n" \
  "%   OUT = mex_flat( 'isDegenerated', OBJ );                           %\n" \
  "%   OUT = mex_flat( 'isApprox', OBJ, OTHER_OBJ );                     %\n" \
  "%         mex_flat( 'copy', OBJ, OTHER_OBJ );                         %\n" \
  "%                                                                     %\n" \
  "%=====================================================================%\n" \
  "%                                                                     %\n" \
  "%    Davide Stocco                                                    %\n" \
  "%    Department of Industrial Engineering                             %\n" \
  "%    University of Trento                                             %\n" \
  "%    davide.stocco@unitn.it                                           %\n" \
  "%                                                                     %\n" \
  "%    Enrico Bertolazzi                                                %\n" \
  "%    Department of Industrial Engineering                             %\n" \
  "%    University of Trento                                             %\n" \
  "%    enrico.bertolazzi@unitn.it                                       %\n" \
  "%                                                                     %\n" \
  "%=====================================================================%\n"

using namespace std;

typedef double real_type;

static void
DATA_NEW(
  mxArray           *&mx_id,
  enve::ground::flat *ptr)
{
  mx_id = convertPtr2Mat<enve::ground::flat>(ptr);
}

static inline enve::ground::flat *
DATA_GET(
  mxArray const *&mx_id)
{
  return convertMat2Ptr<enve::ground::flat>(mx_id);
}

static void
DATA_DELETE(
  mxArray const *&mx_id)
{
  destroyObject<enve::ground::flat>(mx_id);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_new(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'new', [, args] ): "
  MEX_ASSERT(nrhs == 1 || nrhs == 4 || nrhs == 8, CMD "expected 1, 4 or 8 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  MEX_ASSERT(
    mxIsChar(arg_in_0),
    CMD << "first argument must be a string, found ``" << mxGetClassName(arg_in_0) << "''\n");

  real_type ox = acme::QUIET_NAN;
  real_type oy = acme::QUIET_NAN;
  real_type oz = acme::QUIET_NAN;
  real_type nx = acme::QUIET_NAN;
  real_type ny = acme::QUIET_NAN;
  real_type nz = acme::QUIET_NAN;
  real_type mu = acme::QUIET_NAN;

  if (nrhs == 4)
  {
    real_type const *matrix1_ptr;
    mwSize           rows1, cols1;
    matrix1_ptr = getMatrixPointer(arg_in_1, rows1, cols1, CMD "Error in first input matrix");
    MEX_ASSERT(rows1 == 3 || cols1 == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows1 << ", cols = " << cols1 << '\n');
    ox = matrix1_ptr[0];
    oy = matrix1_ptr[1];
    oz = matrix1_ptr[2];
    real_type const *matrix2_ptr;
    mwSize           rows2, cols2;
    matrix2_ptr = getMatrixPointer(arg_in_2, rows2, cols2, CMD "Error in second input matrix");
    MEX_ASSERT(rows2 == 3 || cols2 == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows2 << ", cols = " << cols2 << '\n');
    nx = matrix2_ptr[0];
    ny = matrix2_ptr[1];
    nz = matrix2_ptr[2];
    mu = getScalarValue(arg_in_3, CMD "Error in reading input friction value");
  }
  else if (nrhs == 8)
  {
    ox = getScalarValue(arg_in_1, CMD "Error in reading input origin x value");
    oy = getScalarValue(arg_in_2, CMD "Error in reading input origin y value");
    oz = getScalarValue(arg_in_3, CMD "Error in reading input origin z value");
    nx = getScalarValue(arg_in_4, CMD "Error in reading input normal x value");
    ny = getScalarValue(arg_in_5, CMD "Error in reading input normal y value");
    nz = getScalarValue(arg_in_6, CMD "Error in reading input normal z value");
    mu = getScalarValue(arg_in_7, CMD "Error in reading input friction value");
  }

  enve::ground::flat *self = new enve::ground::flat(ox, oy, oz, nx, ny, nz, mu);

  DATA_NEW(arg_out_0, self);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_delete(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'delete', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  DATA_DELETE(arg_in_1);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getOrigin(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'getOrigin', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::ground::flat *self = DATA_GET(arg_in_1);
  acme::point        *out  = new acme::point(self->origin());
  arg_out_0                = convertPtr2Mat<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_setOrigin(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'setOrigin', OBJ, OTHER_OBJ ): "
  enve::ground::flat *self = DATA_GET(arg_in_1);
  real_type const    *matrix_ptr;
  mwSize              rows, cols;
  matrix_ptr = getMatrixPointer(arg_in_2, rows, cols, CMD "Error in first input matrix");
  MEX_ASSERT(rows == 3 || cols == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows << ", cols = " << cols << '\n');
  self->origin() = acme::point(matrix_ptr[0], matrix_ptr[1], matrix_ptr[2]);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getNormal(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'getNormal', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::ground::flat *self   = DATA_GET(arg_in_1);
  real_type          *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3          outvec(self->acme::plane::normal());
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_setNormal(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'setNormal', OBJ, OTHER_OBJ ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  enve::ground::flat *self = DATA_GET(arg_in_1);
  real_type const    *matrix_ptr;
  mwSize              rows, cols;
  matrix_ptr = getMatrixPointer(arg_in_2, rows, cols, CMD "Error in first input matrix");
  MEX_ASSERT(rows == 3 || cols == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows << ", cols = " << cols << '\n');
  self->normal() = acme::vec3(matrix_ptr[0], matrix_ptr[1], matrix_ptr[2]);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getPlane(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'getPlane', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::ground::flat *self = DATA_GET(arg_in_1);
  acme::plane        *out  = new acme::plane(self->layingPlane());
  arg_out_0                = convertPtr2Mat<acme::plane>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_setPlane(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'setPlane', OBJ ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  enve::ground::flat *self  = DATA_GET(arg_in_1);
  acme::plane        *other = DATA_GET(arg_in_2);
  self->layingPlane()       = *other;
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_getFriction(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{

#define CMD "mex_flat( 'getFriction', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::ground::flat *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->friction());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_setFriction(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{

#define CMD "mex_flat( 'setFriction', OBJ, FRICTION ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  enve::ground::flat *self  = DATA_GET(arg_in_1);
  real_type           other = getScalarValue(arg_in_2, CMD "Error in reading input value");
  self->friction()          = other;
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_isDegenerated(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'isDegenerated', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::ground::flat *self = DATA_GET(arg_in_1);
  setScalarBool(arg_out_0, self->isDegenerated());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_isApprox(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'isApprox', OBJ, OTHER_OBJ ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::ground::flat *self  = DATA_GET(arg_in_1);
  enve::ground::flat *other = DATA_GET(arg_in_2);
  setScalarBool(arg_out_0, self->isApprox(*other));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_copy(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_flat( 'copy', OBJ, OTHER_OBJ ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  enve::ground::flat *self  = DATA_GET(arg_in_1);
  enve::ground::flat *other = DATA_GET(arg_in_2);
  *self                     = *other;
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef void (*DO_CMD)(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[]);

static map<string, DO_CMD> cmd_to_fun = {
  {"new",           do_new},
  {"delete",        do_delete},
  {"getOrigin",     do_getOrigin},
  {"setOrigin",     do_setOrigin},
  {"getNormal",     do_getNormal},
  {"setNormal",     do_setNormal},
  {"getPlane",      do_getPlane},
  {"setPlane",      do_setPlane},
  {"setFriction",   do_setFriction},
  {"getFriction",   do_getFriction},
  {"isDegenerated", do_isDegenerated},
  {"isApprox",      do_isApprox},
  {"copy",          do_copy}};

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
    MEX_ASSERT(mxIsChar(arg_in_0), "First argument must be a string");
    string cmd  = mxArrayToString(arg_in_0);
    DO_CMD pfun = cmd_to_fun.at(cmd);
    pfun(nlhs, plhs, nrhs, prhs);
  }
  catch (exception const &e)
  {
    mexErrMsgTxt((string("mex_flat Error: ") + e.what()).c_str());
  }
  catch (...)
  {
    mexErrMsgTxt("mex_flat failed\n");
  }
}
