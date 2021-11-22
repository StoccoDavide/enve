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

#include "acme.hh"
#include "acme_point.hh"
#include "enve_shell.hh"
#include "mex_utils.hh"

#define ASSERT(COND, MSG)                \
  if (!(COND))                           \
  {                                      \
    std::ostringstream ost;              \
    ost << "mex_shell: " << MSG << '\n'; \
    mexErrMsgTxt(ost.str().c_str());     \
  }

#define MEX_ERROR_MESSAGE                                                     \
  "%=====================================================================%\n" \
  "% mex_shell: Mex wrapper for ENVE shell object.                       %\n" \
  "%                                                                     %\n" \
  "% CONSTRUCTORS:                                                       %\n" \
  "%   OUT = mex_shell( 'new',                                           %\n" \
  "%                    Sh, : Shell shape object                         %\n" \
  "%                    N   : Number of ribs                             %\n" \
  "%                  );                                                 %\n" \
  "%                                                                     %\n" \
  "%   OUT = mex_shell( 'new',                                           %\n" \
  "%                    N,  : Number of ribs                             %\n" \
  "%                    Rx, : Shell radius on x axis [m]                 %\n" \
  "%                    Mx, : Shell curve degree for x axis              %\n" \
  "%                    Ry, : Shell radius on y axis [m]                 %\n" \
  "%                    My, : Shell curve degree for y axis              %\n" \
  "%                    Ly  : Shell surface half width on y axis [m]     %\n" \
  "%                  );                                                 %\n" \
  "%                                                                     %\n" \
  "%   OUT = mex_shell( 'new',                                           %\n" \
  "%                    N, : Number of ribs                              %\n" \
  "%                    R, : Shell radius vector data [m]                %\n" \
  "%                    Y, : Shell y axis vector data [m]                %\n" \
  "%                    O  : Fitting polynomial order                    %\n" \
  "%                  );                                                 %\n" \
  "%                                                                     %\n" \
  "% DESTRUCTOR:                                                         %\n" \
  "%   mex_shell( 'delete', OBJ );                                       %\n" \
  "%                                                                     %\n" \
  "% USAGE:                                                              %\n" \
  "%   OUT = mex_shell( 'surfaceMaxRadius', OBJ );                       %\n" \
  "%   OUT = mex_shell( 'surfaceRadius', OBJ , Y);                       %\n" \
  "%   OUT = mex_shell( 'surfaceMaxWidth', OBJ );                        %\n" \
  "%   OUT = mex_shell( 'surfaceWidth', OBJ );                           %\n" \
  "%   OUT = mex_shell( 'surfaceDerivative', OBJ, Y );                   %\n" \
  "%   OUT = mex_shell( 'surfaceAngle', OBJ, Y );                        %\n" \
  "%         mex_shell( 'reset', OBJ, N );                               %\n" \
  "%   OUT = mex_shell( 'size', OBJ );                                   %\n" \
  "%   OUT = mex_shell( 'ribRadius', OBJ, I );                           %\n" \
  "%   OUT = mex_shell( 'ribCenter', OBJ, I );                           %\n" \
  "%   OUT = mex_shell( 'ribWidth', OBJ );                               %\n" \
  "%   OUT = mex_shell( 'translation', OBJ );                            %\n" \
  "%         mex_shell( 'translate', OBJ, VECTOR );                      %\n" \
  "%         mex_shell( 'rotate', OBJ, ANGLE, AXIS );                    %\n" \
  "%   OUT = mex_shell( 'rotation', OBJ );                               %\n" \
  "%         mex_shell( 'transform', OBJ, MATRIX );                      %\n" \
  "%   OUT = mex_shell( 'transformation', OBJ );                         %\n" \
  "%   OUT = mex_shell( 'x', OBJ );                                      %\n" \
  "%   OUT = mex_shell( 'y', OBJ );                                      %\n" \
  "%   OUT = mex_shell( 'z', OBJ );                                      %\n" \
  "%   OUT = mex_shell( 'eulerAngles', OBJ );                            %\n" \
  "%   OUT = mex_shell( 'relativeAnglesAvg', OBJ );                      %\n" \
  "%   OUT = mex_shell( 'relativeAngles', OBJ, I );                      %\n" \
  "%   OUT = mex_shell( 'contactDepthAvg', OBJ, DEPTH_OLD,TIME_STEP );   %\n" \
  "%   OUT = mex_shell( 'contactDepth', OBJ, I, DEPTH_OLD, TIME_STEP );  %\n" \
  "%   OUT = mex_shell( 'contactNormalAvg', OBJ );                       %\n" \
  "%   OUT = mex_shell( 'contactNormal', OBJ, I );                       %\n" \
  "%   OUT = mex_shell( 'contactPointAvg', OBJ );                        %\n" \
  "%   OUT = mex_shell( 'contactPoint', OBJ, I );                        %\n" \
  "%   OUT = mex_shell( 'contactFrictionAvg', OBJ );                     %\n" \
  "%   OUT = mex_shell( 'contactFriction', OBJ, I );                     %\n" \
  "%   OUT = mex_shell( 'contactPointAffineAvg', OBJ );                  %\n" \
  "%   OUT = mex_shell( 'contactPointAffine', OBJ, I );                  %\n" \
  "%   OUT = mex_shell( 'setup', OBJ, ARGS );                            %\n" \
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
  mxArray    *&mx_id,
  enve::shell *ptr)
{
  mx_id = convertPtr2Mat<enve::shell>(ptr);
}

static inline enve::shell *
DATA_GET(
  mxArray const *&mx_id)
{
  return convertMat2Ptr<enve::shell>(mx_id);
}

static void
DATA_DELETE(
  mxArray const *&mx_id)
{
  destroyObject<enve::shell>(mx_id);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_new(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'new', [, args] ): "
  MEX_ASSERT(nrhs == 4 || nrhs == 5 || nrhs == 7, CMD "expected 4, 5 or 7 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  MEX_ASSERT(
    mxIsChar(arg_in_0),
    CMD << "first argument must be a string, found ``" << mxGetClassName(arg_in_0) << "''\n");

  enve::shell *ptr = nullptr;

  if (nrhs == 7)
  {
    int       size = getInt(arg_in_1, CMD "Error in reading N input value");
    real_type r_x  = getScalarValue(arg_in_2, CMD "Error in reading Rx input value");
    real_type m_x  = getScalarValue(arg_in_3, CMD "Error in reading Mx input value");
    real_type r_y  = getScalarValue(arg_in_4, CMD "Error in reading Ry input value");
    real_type m_y  = getScalarValue(arg_in_5, CMD "Error in reading My input value");
    real_type l_y  = getScalarValue(arg_in_6, CMD "Error in reading Ly input value");
    ptr            = new enve::shell(size, r_x, m_x, r_y, m_y, l_y);
  }
  else if (nrhs == 4)
  {
    int size = getInt(arg_in_1, CMD "Error in reading N input value");

    real_type const *matrixR_ptr;
    mwSize           rowsR, colsR;
    matrixR_ptr = getMatrixPointer(arg_in_2, rowsR, colsR, CMD "Error in first input matrix");
    MEX_ASSERT(rowsR > 0 || colsR == 1, CMD "expected rows > 0 and cols = 1 found, rows = " << rowsR << ", cols = " << colsR << '\n');

    acme::vecN dataR(rowsR);
    for (int i = 0; i < rowsR; ++i)
      for (int j = 0; j < colsR; ++j)
        dataR(i) = matrixR_ptr[i + j * colsR];

    real_type const *matrixY_ptr;
    mwSize           rowsY, colsY;
    matrixY_ptr = getMatrixPointer(arg_in_3, rowsY, colsY, CMD "Error in second input matrix");
    MEX_ASSERT(rowsY > 0 || colsR == 1, CMD "expected rows > 0 and cols = 1 found, rows = " << rowsY << ", cols = " << colsY << '\n');

    acme::vecN dataY(rowsY);
    for (int i = 0; i < rowsY; ++i)
      for (int j = 0; j < colsY; ++j)
        dataY(i) = matrixY_ptr[i + j * colsY];

    ptr = new enve::shell(size, dataR, dataY);
  }
  else if (nrhs == 5)
  {
    int size = getInt(arg_in_1, CMD "Error in reading N input value");

    real_type const *matrixR_ptr;
    mwSize           rowsR, colsR;
    matrixR_ptr = getMatrixPointer(arg_in_2, rowsR, colsR, CMD "Error in first input matrix");
    MEX_ASSERT(rowsR > 0 || colsR == 1, CMD "expected rows > 0 and cols = 1 found, rows = " << rowsR << ", cols = " << colsR << '\n');

    acme::vecN dataR(rowsR);
    for (int i = 0; i < rowsR; ++i)
      for (int j = 0; j < colsR; ++j)
        dataR(i) = matrixR_ptr[i + j * colsR];

    real_type const *matrixY_ptr;
    mwSize           rowsY, colsY;
    matrixY_ptr = getMatrixPointer(arg_in_3, rowsY, colsY, CMD "Error in second input matrix");
    MEX_ASSERT(rowsY > 0 || colsR == 1, CMD "expected rows > 0 and cols = 1 found, rows = " << rowsY << ", cols = " << colsY << '\n');

    acme::vecN dataY(rowsY);
    for (int i = 0; i < rowsY; ++i)
      for (int j = 0; j < colsY; ++j)
        dataY(i) = matrixY_ptr[i + j * colsY];

    int order = getInt(arg_in_4, CMD "Error in reading O input value");
    ptr       = new enve::shell(size, dataR, dataY, order);
  }

  DATA_NEW(arg_out_0, ptr);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_delete(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'delete', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  DATA_DELETE(arg_in_1);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_reset(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'reset', OBJ, N ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  int          size = getInt(arg_in_2, CMD "Error in reading input value");
  self->reset(size);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_size(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'size', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  setScalarInt(arg_out_0, self->size());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceMaxRadius(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceMaxRadius', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->surfaceMaxRadius());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceMaxWidth(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceMaxWidth', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->surfaceMaxWidth());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceWidthLowerBound(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceWidthLowerBound', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->surfaceWidthLowerBound());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceWidthUpperBound(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceWidthUpperBound', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->surfaceWidthUpperBound());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceWidth(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceWidth', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  setScalarValue(arg_out_0, self->surfaceWidth());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_checkWidthBound(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'checkWidthBound', OBJ, Y ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    y    = getScalarValue(arg_in_2, CMD "Error in reading y coordinate input value");
  setScalarValue(arg_out_0, self->checkWidthBound(y));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceRadius(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceRadius', OBJ, Y ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    y    = getScalarValue(arg_in_2, CMD "Error in reading y coordinate input value");
  setScalarValue(arg_out_0, self->surfaceRadius(y));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceDerivative(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceDerivative', OBJ, Y ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    y    = getScalarValue(arg_in_2, CMD "Error in reading y coordinate input value");
  setScalarValue(arg_out_0, self->surfaceDerivative(y));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceAngle(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceAngle', OBJ, Y ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    y    = getScalarValue(arg_in_2, CMD "Error in reading y coordinate input value");
  setScalarValue(arg_out_0, self->surfaceAngle(y));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_ribRadius(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'ribRadius', OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = getInt(arg_in_2, CMD "Error in reading input value");
  setScalarValue(arg_out_0, self->ribRadius(i - 1));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_ribCenter(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'ribCenter', OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = getInt(arg_in_2, CMD "Error in reading input value");
  acme::point *out  = new acme::point(self->ribCenter(i - 1));
  arg_out_0         = convertPtr2Mat<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_ribWidth(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'ribWidth', OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = getInt(arg_in_2, CMD "Error in reading input value");
  setScalarValue(arg_out_0, self->ribWidth(i));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_translate(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'translate', OBJ, VECTOR ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  enve::shell     *self = DATA_GET(arg_in_1);
  real_type const *matrix_ptr;
  mwSize           rows, cols;
  matrix_ptr = getMatrixPointer(arg_in_2, rows, cols, CMD "Error in first input matrix");
  MEX_ASSERT(rows == 3 || cols == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows << ", cols = " << cols << '\n');
  real_type x = matrix_ptr[0];
  real_type y = matrix_ptr[1];
  real_type z = matrix_ptr[2];
  self->translate(acme::vec3(x, y, z));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_translation(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'translation', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3   outvec(self->translation());
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_rotate(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'rotate', OBJ, ANGLE, AXIS ): "
  MEX_ASSERT(nrhs == 4, CMD "expected 4 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  enve::shell     *self  = DATA_GET(arg_in_1);
  real_type        angle = getScalarValue(arg_in_2, CMD "Error in reading second input value");
  real_type const *vector_ptr;
  mwSize           rows, cols;
  vector_ptr = getMatrixPointer(arg_in_3, rows, cols, CMD "Error in reading axis vector");
  MEX_ASSERT(rows == 3 || cols == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows << ", cols = " << cols << '\n');
  acme::vec3 vector(vector_ptr[0], vector_ptr[1], vector_ptr[2]);
  self->rotate(angle, vector);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_rotation(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'rotation', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 3, 3);
  acme::mat3   outmat(self->rotation());
  output[0] = outmat(0, 0);
  output[1] = outmat(0, 1);
  output[2] = outmat(0, 2);
  output[3] = outmat(1, 0);
  output[4] = outmat(1, 1);
  output[5] = outmat(1, 2);
  output[6] = outmat(2, 0);
  output[7] = outmat(2, 1);
  output[8] = outmat(2, 2);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_transform(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'transform', OBJ, MATRIX ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << '\n');

  enve::shell     *self = DATA_GET(arg_in_1);
  real_type const *matrix_ptr;
  mwSize           rows, cols;
  matrix_ptr = getMatrixPointer(arg_in_2, rows, cols, CMD "Error in reading affine transformation matrix");
  MEX_ASSERT(rows == 4 || cols == 4, CMD "expected rows = 4 and cols = 4 found, rows = " << rows << ", cols = " << cols << '\n');
  acme::affine matrix;
  matrix.matrix() << matrix_ptr[0], matrix_ptr[4], matrix_ptr[8], matrix_ptr[12],
    matrix_ptr[1], matrix_ptr[5], matrix_ptr[9], matrix_ptr[13],
    matrix_ptr[2], matrix_ptr[6], matrix_ptr[10], matrix_ptr[14],
    matrix_ptr[3], matrix_ptr[7], matrix_ptr[11], matrix_ptr[15];
  self->transform(matrix);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_transformation(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'transformation', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 4, 4);
  acme::mat4   outmat(self->transformation().matrix());
  output[0]  = outmat(0, 0);
  output[1]  = outmat(1, 0);
  output[2]  = outmat(2, 0);
  output[3]  = outmat(3, 0);
  output[4]  = outmat(0, 1);
  output[5]  = outmat(1, 1);
  output[6]  = outmat(2, 1);
  output[7]  = outmat(3, 1);
  output[8]  = outmat(0, 2);
  output[9]  = outmat(1, 2);
  output[10] = outmat(2, 2);
  output[11] = outmat(3, 2);
  output[12] = outmat(0, 3);
  output[13] = outmat(1, 3);
  output[14] = outmat(2, 3);
  output[15] = outmat(3, 3);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_x(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'x', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3   outvec(self->x());
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_y(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'y', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3   outvec(self->y());
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_z(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'z', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3   outvec(self->z());
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_eulerAngles(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'eulerAngles', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3   outvec;
  self->eulerAngles(outvec);
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_relativeAnglesAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'relativeAnglesAvg', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3   outvec;
  self->relativeAngles(outvec);
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_relativeAngles(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'relativeAngles', OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  int          i      = getInt(arg_in_2, CMD "Error in reading input value");
  real_type   *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3   outvec;
  self->relativeAngles(i - 1, outvec);
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactDepthRibAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactDepthRibAvg', OBJ, DEPTH_OLD, TIME_STEP ): "
  MEX_ASSERT(nrhs == 4, CMD "expected 4 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 2, CMD "expected 2 output, nlhs = " << nlhs << '\n');

  enve::shell *self      = DATA_GET(arg_in_1);
  real_type    depth_old = getScalarValue(arg_in_2, CMD "Error in reading second input value");
  real_type    time_step = getScalarValue(arg_in_3, CMD "Error in reading third input value");
  real_type    depth, depth_dot;
  self->contactDepthRib(depth, depth_dot, depth_old, time_step);
  setScalarValue(arg_out_0, depth);
  setScalarValue(arg_out_1, depth_dot);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactDepthRib(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactDepthRib',  OBJ, I, DEPTH_DOT, DEPTH_OLD, TIME_STEP ): "
  MEX_ASSERT(nrhs == 5, CMD "expected 5 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 2, CMD "expected 2 output, nlhs = " << nlhs << '\n');

  enve::shell *self      = DATA_GET(arg_in_1);
  int          i         = getInt(arg_in_2, CMD "Error in reading input value");
  real_type    depth_old = getScalarValue(arg_in_3, CMD "Error in reading second input value");
  real_type    time_step = getScalarValue(arg_in_4, CMD "Error in reading third input value");
  real_type    depth, depth_dot;
  self->contactDepthRib(i - 1, depth, depth_dot, depth_old, time_step);
  setScalarValue(arg_out_0, depth);
  setScalarValue(arg_out_1, depth_dot);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactDepthMeshAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactDepthMeshAvg', OBJ, DEPTH_OLD, TIME_STEP ): "
  MEX_ASSERT(nrhs == 4, CMD "expected 4 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 2, CMD "expected 2 output, nlhs = " << nlhs << '\n');

  enve::shell *self      = DATA_GET(arg_in_1);
  real_type    depth_old = getScalarValue(arg_in_2, CMD "Error in reading second input value");
  real_type    time_step = getScalarValue(arg_in_3, CMD "Error in reading third input value");
  real_type    depth, depth_dot;
  self->contactDepthMesh(depth, depth_dot, depth_old, time_step);
  setScalarValue(arg_out_0, depth);
  setScalarValue(arg_out_1, depth_dot);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactDepthMesh(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactDepthMesh',  OBJ, I, DEPTH_DOT, DEPTH_OLD, TIME_STEP ): "
  MEX_ASSERT(nrhs == 5, CMD "expected 5 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 2, CMD "expected 2 output, nlhs = " << nlhs << '\n');

  enve::shell *self      = DATA_GET(arg_in_1);
  int          i         = getInt(arg_in_2, CMD "Error in reading input value");
  real_type    depth_old = getScalarValue(arg_in_3, CMD "Error in reading second input value");
  real_type    time_step = getScalarValue(arg_in_4, CMD "Error in reading third input value");
  real_type    depth, depth_dot;
  self->contactDepthMesh(i - 1, depth, depth_dot, depth_old, time_step);
  setScalarValue(arg_out_0, depth);
  setScalarValue(arg_out_1, depth_dot);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactNormalAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactNormalAvg', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3   outvec;
  self->contactNormal(outvec);
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactNormal(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactNormal', OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  int          i      = getInt(arg_in_2, CMD "Error in reading input value");
  real_type   *output = createMatrixValue(arg_out_0, 3, 1);
  acme::vec3   outvec;
  self->contactNormal(i - 1, outvec);
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointRibAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointRibAvg', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  acme::point *out  = new acme::point();
  self->contactPointRib(*out);
  arg_out_0 = convertPtr2Mat<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointRib(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointRib', OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = getInt(arg_in_2, CMD "Error in reading input value");
  acme::point *out  = new acme::point();
  self->contactPointRib(i - 1, *out);
  arg_out_0 = convertPtr2Mat<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointMeshAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointMeshAvg', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  acme::point *out  = new acme::point();
  self->contactPointMesh(*out);
  arg_out_0 = convertPtr2Mat<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointMesh(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointMesh', OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = getInt(arg_in_2, CMD "Error in reading input value");
  acme::point *out  = new acme::point();
  self->contactPointMesh(i - 1, *out);
  arg_out_0 = convertPtr2Mat<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactFrictionAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactFrictionAvg', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    friction;
  self->contactFriction(friction);
  setScalarValue(arg_out_0, friction);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactFriction(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactFriction',  OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = getInt(arg_in_2, CMD "Error in reading input value");
  real_type    friction;
  self->contactFriction(i - 1, friction);
  setScalarValue(arg_out_0, friction);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointRibAffineAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointRibAffineAvg', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 4, 4);
  acme::affine outmat;
  self->contactPointRibAffine(outmat);
  output[0]  = outmat(0, 0);
  output[1]  = outmat(1, 0);
  output[2]  = outmat(2, 0);
  output[3]  = outmat(3, 0);
  output[4]  = outmat(0, 1);
  output[5]  = outmat(1, 1);
  output[6]  = outmat(2, 1);
  output[7]  = outmat(3, 1);
  output[8]  = outmat(0, 2);
  output[9]  = outmat(1, 2);
  output[10] = outmat(2, 2);
  output[11] = outmat(3, 2);
  output[12] = outmat(0, 3);
  output[13] = outmat(1, 3);
  output[14] = outmat(2, 3);
  output[15] = outmat(3, 3);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointRibAffine(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointRibAffine', OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  int          i      = getInt(arg_in_2, CMD "Error in reading input value");
  real_type   *output = createMatrixValue(arg_out_0, 4, 4);
  acme::affine outmat;
  self->contactPointRibAffine(i - 1, outmat);
  output[0]  = outmat(0, 0);
  output[1]  = outmat(1, 0);
  output[2]  = outmat(2, 0);
  output[3]  = outmat(3, 0);
  output[4]  = outmat(0, 1);
  output[5]  = outmat(1, 1);
  output[6]  = outmat(2, 1);
  output[7]  = outmat(3, 1);
  output[8]  = outmat(0, 2);
  output[9]  = outmat(1, 2);
  output[10] = outmat(2, 2);
  output[11] = outmat(3, 2);
  output[12] = outmat(0, 3);
  output[13] = outmat(1, 3);
  output[14] = outmat(2, 3);
  output[15] = outmat(3, 3);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointMeshAffineAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointMeshAffineAvg', OBJ ): "
  MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = createMatrixValue(arg_out_0, 4, 4);
  acme::affine outmat;
  self->contactPointMeshAffine(outmat);
  output[0]  = outmat(0, 0);
  output[1]  = outmat(1, 0);
  output[2]  = outmat(2, 0);
  output[3]  = outmat(3, 0);
  output[4]  = outmat(0, 1);
  output[5]  = outmat(1, 1);
  output[6]  = outmat(2, 1);
  output[7]  = outmat(3, 1);
  output[8]  = outmat(0, 2);
  output[9]  = outmat(1, 2);
  output[10] = outmat(2, 2);
  output[11] = outmat(3, 2);
  output[12] = outmat(0, 3);
  output[13] = outmat(1, 3);
  output[14] = outmat(2, 3);
  output[15] = outmat(3, 3);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointMeshAffine(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointMeshAffine', OBJ, I ): "
  MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self   = DATA_GET(arg_in_1);
  int          i      = getInt(arg_in_2, CMD "Error in reading input value");
  real_type   *output = createMatrixValue(arg_out_0, 4, 4);
  acme::affine outmat;
  self->contactPointMeshAffine(i - 1, outmat);
  output[0]  = outmat(0, 0);
  output[1]  = outmat(1, 0);
  output[2]  = outmat(2, 0);
  output[3]  = outmat(3, 0);
  output[4]  = outmat(0, 1);
  output[5]  = outmat(1, 1);
  output[6]  = outmat(2, 1);
  output[7]  = outmat(3, 1);
  output[8]  = outmat(0, 2);
  output[9]  = outmat(1, 2);
  output[10] = outmat(2, 2);
  output[11] = outmat(3, 2);
  output[12] = outmat(0, 3);
  output[13] = outmat(1, 3);
  output[14] = outmat(2, 3);
  output[15] = outmat(3, 3);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_setup(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'setup', OBJ, ARGS ): "
  MEX_ASSERT(nrhs == 4 || nrhs == 6, CMD "expected 4 or 6 inputs, nrhs = " << nrhs << '\n');
  MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << '\n');

  enve::shell *self     = DATA_GET(arg_in_1);
  bool         out_bool = false;

  if (nrhs == 4)
  {
    enve::ground::flat *ground_plane = convertMat2Ptr<enve::ground::flat>(arg_in_2);
    real_type const    *matrix_ptr;
    mwSize              rows, cols;
    matrix_ptr = getMatrixPointer(arg_in_3, rows, cols, CMD "Error in reading affine transformation matrix");
    MEX_ASSERT(rows == 4 || cols == 4, CMD "expected rows = 4 and cols = 4 found, rows = " << rows << ", cols = " << cols << '\n');
    acme::affine matrix;
    matrix.matrix() << matrix_ptr[0], matrix_ptr[4], matrix_ptr[8], matrix_ptr[12],
      matrix_ptr[1], matrix_ptr[5], matrix_ptr[9], matrix_ptr[13],
      matrix_ptr[2], matrix_ptr[6], matrix_ptr[10], matrix_ptr[14],
      matrix_ptr[3], matrix_ptr[7], matrix_ptr[11], matrix_ptr[15];
    out_bool = self->setup(*ground_plane, matrix);
  }
  else if (nrhs == 6)
  {
    enve::ground::mesh *ground_mesh = convertMat2Ptr<enve::ground::mesh>(arg_in_2);
    real_type const    *matrix_ptr;
    mwSize              rows, cols;
    matrix_ptr = getMatrixPointer(arg_in_3, rows, cols, CMD "Error in reading affine transformation matrix");
    MEX_ASSERT(rows == 4 || cols == 4, CMD "expected rows = 4 and cols = 4 found, rows = " << rows << ", cols = " << cols << '\n');
    acme::affine matrix;
    matrix.matrix() << matrix_ptr[0], matrix_ptr[4], matrix_ptr[8], matrix_ptr[12],
      matrix_ptr[1], matrix_ptr[5], matrix_ptr[9], matrix_ptr[13],
      matrix_ptr[2], matrix_ptr[6], matrix_ptr[10], matrix_ptr[14],
      matrix_ptr[3], matrix_ptr[7], matrix_ptr[11], matrix_ptr[15];
    int    threshold = getInt(arg_in_4, CMD "Error in reading input value");
    string method    = mxArrayToString(arg_in_5);
    out_bool         = self->setup(*ground_mesh, matrix, threshold, method);
  }

  setScalarBool(arg_out_0, out_bool);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef void (*DO_CMD)(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[]);

static map<string, DO_CMD> cmd_to_fun = {
  {"new", do_new},
  {"delete", do_delete},
  {"reset", do_reset},
  {"size", do_size},
  {"surfaceMaxRadius", do_surfaceMaxRadius},
  {"surfaceMaxWidth", do_surfaceMaxWidth},
  {"surfaceWidthLowerBound", do_surfaceWidthLowerBound},
  {"surfaceWidthUpperBound", do_surfaceWidthUpperBound},
  {"surfaceWidth", do_surfaceWidth},
  {"checkWidthBound", do_checkWidthBound},
  {"surfaceRadius", do_surfaceRadius},
  {"surfaceDerivative", do_surfaceDerivative},
  {"surfaceAngle", do_surfaceAngle},
  {"ribRadius", do_ribRadius},
  {"ribCenter", do_ribCenter},
  {"ribWidth", do_ribWidth},
  {"translate", do_translate},
  {"translation", do_translation},
  {"rotate", do_rotate},
  {"rotation", do_rotation},
  {"transform", do_transform},
  {"transformation", do_transformation},
  {"x", do_x},
  {"y", do_y},
  {"z", do_z},
  {"eulerAngles", do_eulerAngles},
  {"relativeAnglesAvg", do_relativeAnglesAvg},
  {"relativeAngles", do_relativeAngles},
  {"contactDepthRibAvg", do_contactDepthRibAvg},
  {"contactDepthRib", do_contactDepthRib},
  {"contactDepthMeshAvg", do_contactDepthMeshAvg},
  {"contactDepthMesh", do_contactDepthMesh},
  {"contactNormalAvg", do_contactNormalAvg},
  {"contactNormal", do_contactNormal},
  {"contactPointRibAvg", do_contactPointRibAvg},
  {"contactPointRib", do_contactPointRib},
  {"contactPointMeshAvg", do_contactPointMeshAvg},
  {"contactPointMesh", do_contactPointMesh},
  {"contactFrictionAvg", do_contactFrictionAvg},
  {"contactFriction", do_contactFriction},
  {"contactPointRibAffineAvg", do_contactPointRibAffineAvg},
  {"contactPointRibAffine", do_contactPointRibAffine},
  {"contactPointMeshAffineAvg", do_contactPointMeshAffineAvg},
  {"contactPointMeshAffine", do_contactPointMeshAffine},
  {"setup", do_setup}};

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
    mexErrMsgTxt((string("mex_shell Error: ") + e.what()).c_str());
  }
  catch (...)
  {
    mexErrMsgTxt("mex_shell failed\n");
  }
}
