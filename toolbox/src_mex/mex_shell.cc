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
/// file: mex_shell.cc
///

#include "mex_utils.hh"
#include "acme.hh"
#include "enve.hh"

#define ASSERT(COND, MSG)                \
  if (!(COND))                           \
  {                                      \
    std::ostringstream ost;              \
    ost << "mex_shell: " << MSG << "\n"; \
    mexErrMsgTxt(ost.str().c_str());     \
  }

#define MEX_ERROR_MESSAGE                                                     \
  "%=====================================================================%\n" \
  "% mex_shell: Mex wrapper for ENVE shell object.                       %\n" \
  "%                                                                     %\n" \
  "% CONSTRUCTORS:                                                       %\n" \
  "%   OUT = mex_shell( 'new',                                           %\n" \
  "%                    N,  : Number of ribs                             %\n" \
  "%                    Rx, : Shell radius on x axis (m)                 %\n" \
  "%                    Mx, : Shell curve degree for x axis              %\n" \
  "%                    Ry, : Shell radius on y axis (m)                 %\n" \
  "%                    My, : Shell curve degree for y axis              %\n" \
  "%                    Ly  : Shell surface half width on y axis (m)     %\n" \
  "%                  );                                                 %\n" \
  "%                                                                     %\n" \
  "% DESTRUCTOR:                                                         %\n" \
  "%   mex_shell( 'delete', OBJ );                                       %\n" \
  "%                                                                     %\n" \
  "% USAGE:                                                              %\n" \
  "%         mex_shell( 'resize', OBJ, N );                              %\n" \
  "%   OUT = mex_shell( 'size', OBJ );                                   %\n" \
  "%                                                                     %\n" \
  "%   OUT = mex_shell( 'surfaceMaxRadius', OBJ );                       %\n" \
  "%   OUT = mex_shell( 'surfaceMaxWidth', OBJ );                        %\n" \
  "%   OUT = mex_shell( 'surfaceWidth', OBJ );                           %\n" \
  "%   OUT = mex_shell( 'checkWidthBound', OBJ, Y );                     %\n" \
  "%   OUT = mex_shell( 'surfaceRadius', OBJ , Y );                      %\n" \
  "%   OUT = mex_shell( 'surfaceDerivative', OBJ, Y );                   %\n" \
  "%   OUT = mex_shell( 'surfaceAngle', OBJ, Y );                        %\n" \
  "%   OUT = mex_shell( 'ribRadius', OBJ, I );                           %\n" \
  "%   OUT = mex_shell( 'ribCenter', OBJ, I );                           %\n" \
  "%   OUT = mex_shell( 'ribWidth', OBJ, I );                            %\n" \
  "%   OUT = mex_shell( 'ribAngle', OBJ, I );                            %\n" \
  "%                                                                     %\n" \
  "%         mex_shell( 'translate', OBJ, VECTOR );                      %\n" \
  "%   OUT = mex_shell( 'translation', OBJ );                            %\n" \
  "%         mex_shell( 'rotate', OBJ, ANGLE, AXIS );                    %\n" \
  "%   OUT = mex_shell( 'rotation', OBJ );                               %\n" \
  "%         mex_shell( 'transform', OBJ, MATRIX );                      %\n" \
  "%   OUT = mex_shell( 'transformation', OBJ );                         %\n" \
  "%   OUT = mex_shell( 'checkTransformation', OBJ );                    %\n" \
  "%   OUT = mex_shell( 'x', OBJ );                                      %\n" \
  "%   OUT = mex_shell( 'y', OBJ );                                      %\n" \
  "%   OUT = mex_shell( 'z', OBJ );                                      %\n" \
  "%   OUT = mex_shell( 'eulerAngles', OBJ );                            %\n" \
  "%                                                                     %\n" \
  "%   OUT = mex_shell( 'setupFlat', OBJ, GROUND, AFFINE, METHOD );      %\n" \
  "%   OUT = mex_shell( 'setupMesh', OBJ, GROUND, AFFINE, METHOD );      %\n" \
  "%                                                                     %\n" \
  "%   OUT = mex_shell( 'contactPointAvg', OBJ );                        %\n" \
  "%   OUT = mex_shell( 'contactPointRib', OBJ, I );                     %\n" \
  "%   OUT = mex_shell( 'contactNormalAvg', OBJ );                       %\n" \
  "%   OUT = mex_shell( 'contactNormalRib', OBJ, I );                    %\n" \
  "%   OUT = mex_shell( 'contactDepthAvg', OBJ );                        %\n" \
  "%   OUT = mex_shell( 'contactDepthRib', OBJ, I );                     %\n" \
  "%   OUT = mex_shell( 'contactFrictionAvg', OBJ );                     %\n" \
  "%   OUT = mex_shell( 'contactFrictionRib', OBJ, I );                  %\n" \
  "%   OUT = mex_shell( 'contactAreaAvg', OBJ );                         %\n" \
  "%   OUT = mex_shell( 'contactAreaRib', OBJ, I );                      %\n" \
  "%   OUT = mex_shell( 'contactVolumeAvg', OBJ );                       %\n" \
  "%   OUT = mex_shell( 'contactVolumeRib', OBJ, I );                    %\n" \
  "%   OUT = mex_shell( 'relativeAnglesAvg', OBJ );                      %\n" \
  "%   OUT = mex_shell( 'relativeAnglesRib', OBJ, I );                   %\n" \
  "%   OUT = mex_shell( 'contactPointAffineAvg', OBJ );                  %\n" \
  "%   OUT = mex_shell( 'contactPointAffineRib', OBJ, I );               %\n" \
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
  mxArray    *&mx_id,
  enve::shell *ptr)
{
  mx_id = utils::mex_convert_ptr_to_mx<enve::shell>(ptr);
}

static inline enve::shell *
DATA_GET(
  mxArray const *&mx_id)
{
  return utils::mex_convert_mx_to_ptr<enve::shell>(mx_id);
}

static void
DATA_DELETE(
  mxArray const *&mx_id)
{
  utils::mex_destroy_object<enve::shell>(mx_id);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_new(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'new', [, args] ): "
  UTILS_MEX_ASSERT(nrhs == 7, CMD "expected 7 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  UTILS_MEX_ASSERT(
    mxIsChar(arg_in_0),
    CMD "first argument must be a string, found " << mxGetClassName(arg_in_0) << "\n");

  enve::shell *ptr = nullptr;

  if (nrhs == 7)
  {
    int       size = utils::mex_get_int64(arg_in_1, CMD "error in reading ribs number input value");
    real_type r_x  = utils::mex_get_scalar_value(arg_in_2, CMD "error in reading Rx input value");
    real_type m_x  = utils::mex_get_scalar_value(arg_in_3, CMD "error in reading Mx input value");
    real_type r_y  = utils::mex_get_scalar_value(arg_in_4, CMD "error in reading Ry input value");
    real_type m_y  = utils::mex_get_scalar_value(arg_in_5, CMD "error in reading My input value");
    real_type l_y  = utils::mex_get_scalar_value(arg_in_6, CMD "error in reading Ly input value");
    ptr            = new enve::shell(size, r_x, m_x, r_y, m_y, l_y);
  }
  DATA_NEW(arg_out_0, ptr);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_delete(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'delete', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

  DATA_DELETE(arg_in_1);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_resize(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'resize', OBJ, N ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  int          size = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  self->resize(size);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_size(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'size', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  utils::mex_set_scalar_int64(arg_out_0, self->size());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceMaxRadius(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceMaxRadius', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  utils::mex_set_scalar_value(arg_out_0, self->surfaceMaxRadius());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceMaxWidth(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceMaxWidth', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  utils::mex_set_scalar_value(arg_out_0, self->surfaceMaxWidth());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceWidth(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceWidth', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  utils::mex_set_scalar_value(arg_out_0, self->surfaceWidth());
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_checkWidthBound(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'checkWidthBound', OBJ, Y ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    y    = utils::mex_get_scalar_value(arg_in_2, CMD "error in reading y coordinate input value");
  utils::mex_set_scalar_value(arg_out_0, self->checkWidthBound(y));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceRadius(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceRadius', OBJ, Y ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    y    = utils::mex_get_scalar_value(arg_in_2, CMD "error in reading y coordinate input value");
  utils::mex_set_scalar_value(arg_out_0, self->surfaceRadius(y));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceDerivative(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceDerivative', OBJ, Y ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    y    = utils::mex_get_scalar_value(arg_in_2, CMD "error in reading y coordinate input value");
  utils::mex_set_scalar_value(arg_out_0, self->surfaceDerivative(y));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_surfaceAngle(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'surfaceAngle', OBJ, Y ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    y    = utils::mex_get_scalar_value(arg_in_2, CMD "error in reading y coordinate input value");
  utils::mex_set_scalar_value(arg_out_0, self->surfaceAngle(y));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_ribRadius(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'ribRadius', OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  utils::mex_set_scalar_value(arg_out_0, self->ribRadius(i - 1));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_ribCenter(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'ribCenter', OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  acme::point *out  = new acme::point(self->ribCenter(i - 1));
  arg_out_0         = utils::mex_convert_ptr_to_mx<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_ribWidth(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'ribWidth', OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  utils::mex_set_scalar_value(arg_out_0, self->ribWidth(i - 1));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_ribAngle(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'ribAngle', OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  utils::mex_set_scalar_value(arg_out_0, self->ribAngle(i - 1));
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_translate(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'translate', OBJ, VECTOR ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

  enve::shell     *self = DATA_GET(arg_in_1);
  real_type const *matrix_ptr;
  mwSize           rows, cols;
  matrix_ptr = utils::mex_matrix_pointer(arg_in_2, rows, cols, CMD "error in first input matrix");
  UTILS_MEX_ASSERT(rows == 3 || cols == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows << ", cols = " << cols << "\n");
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
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 3, 1);
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
  UTILS_MEX_ASSERT(nrhs == 4, CMD "expected 4 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

  enve::shell     *self  = DATA_GET(arg_in_1);
  real_type        angle = utils::mex_get_scalar_value(arg_in_2, CMD "error in reading second input value");
  real_type const *vector_ptr;
  mwSize           rows, cols;
  vector_ptr = utils::mex_matrix_pointer(arg_in_3, rows, cols, CMD "error in reading axis vector");
  UTILS_MEX_ASSERT(rows == 3 || cols == 1, CMD "expected rows = 3 and cols = 1 found, rows = " << rows << ", cols = " << cols << "\n");
  acme::vec3 vector(vector_ptr[0], vector_ptr[1], vector_ptr[2]);
  self->rotate(angle, vector);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_rotation(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'rotation', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 3, 3);
  acme::mat3   outmat(self->rotation());
  output[0] = outmat(0,0);
  output[1] = outmat(0,1);
  output[2] = outmat(0,2);
  output[3] = outmat(1,0);
  output[4] = outmat(1,1);
  output[5] = outmat(1,2);
  output[6] = outmat(2,0);
  output[7] = outmat(2,1);
  output[8] = outmat(2,2);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_transform(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'transform', OBJ, MATRIX ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 0, CMD "expected 0 output, nlhs = " << nlhs << "\n");

  enve::shell     *self = DATA_GET(arg_in_1);
  real_type const *matrix_ptr;
  mwSize           rows, cols;
  matrix_ptr = utils::mex_matrix_pointer(arg_in_2, rows, cols, CMD "error in reading affine transformation matrix");
  UTILS_MEX_ASSERT(rows == 4 || cols == 4, CMD "expected rows = 4 and cols = 4 found, rows = " << rows << ", cols = " << cols << "\n");
  acme::affine matrix;
  matrix.matrix() << matrix_ptr[0], matrix_ptr[4], matrix_ptr[8],  matrix_ptr[12],
                     matrix_ptr[1], matrix_ptr[5], matrix_ptr[9],  matrix_ptr[13],
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
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 4, 4);
  acme::mat4   outmat(self->transformation().matrix());
  output[0]  = outmat(0,0);
  output[1]  = outmat(1,0);
  output[2]  = outmat(2,0);
  output[3]  = outmat(3,0);
  output[4]  = outmat(0,1);
  output[5]  = outmat(1,1);
  output[6]  = outmat(2,1);
  output[7]  = outmat(3,1);
  output[8]  = outmat(0,2);
  output[9]  = outmat(1,2);
  output[10] = outmat(2,2);
  output[11] = outmat(3,2);
  output[12] = outmat(0,3);
  output[13] = outmat(1,3);
  output[14] = outmat(2,3);
  output[15] = outmat(3,3);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_checkTransformation(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'checkTransformation', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type const *matrix_ptr;
  mwSize           rows, cols;
  matrix_ptr = utils::mex_matrix_pointer(arg_in_2, rows, cols, CMD "error in reading affine transformation matrix");
  UTILS_MEX_ASSERT(rows == 4 || cols == 4, CMD "expected rows = 4 and cols = 4 found, rows = " << rows << ", cols = " << cols << "\n");
  acme::affine matrix;
  matrix.matrix() << matrix_ptr[0], matrix_ptr[4], matrix_ptr[8],  matrix_ptr[12],
                     matrix_ptr[1], matrix_ptr[5], matrix_ptr[9],  matrix_ptr[13],
                     matrix_ptr[2], matrix_ptr[6], matrix_ptr[10], matrix_ptr[14],
                     matrix_ptr[3], matrix_ptr[7], matrix_ptr[11], matrix_ptr[15];
  bool out = self->checkTransformation(matrix);
  utils::mex_set_scalar_bool(arg_out_0, out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_x(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'x', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 3, 1);
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
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 3, 1);
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
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 3, 1);
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
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 3, 1);
  acme::vec3   outvec;
  self->eulerAngles(outvec);
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_setupFlat(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'setupFlat', OBJ, GROUND, AFFINE, METHOD ): "
  UTILS_MEX_ASSERT(nrhs == 5, CMD "expected 5 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell        *self   = DATA_GET(arg_in_1);
  enve::ground::flat *ground = utils::mex_convert_mx_to_ptr<enve::ground::flat>(arg_in_2);
  real_type const    *matrix_ptr;
  mwSize              rows, cols;
  matrix_ptr = utils::mex_matrix_pointer(arg_in_3, rows, cols, CMD "error in reading affine transformation matrix");
  UTILS_MEX_ASSERT(rows == 4 || cols == 4, CMD "expected rows = 4 and cols = 4 found, rows = " << rows << ", cols = " << cols << "\n");
  acme::affine matrix;
  matrix.matrix() << matrix_ptr[0], matrix_ptr[4], matrix_ptr[8],  matrix_ptr[12],
                     matrix_ptr[1], matrix_ptr[5], matrix_ptr[9],  matrix_ptr[13],
                     matrix_ptr[2], matrix_ptr[6], matrix_ptr[10], matrix_ptr[14],
                     matrix_ptr[3], matrix_ptr[7], matrix_ptr[11], matrix_ptr[15];
  string method = mxArrayToString(arg_in_4);
  bool   out    = self->setup(*ground, matrix, method);
  utils::mex_set_scalar_bool(arg_out_0, out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_setupMesh(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'setupMesh', OBJ, GROUND, AFFINE, METHOD  ): "
  UTILS_MEX_ASSERT(nrhs == 5, CMD "expected 5 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell        *self   = DATA_GET(arg_in_1);
  enve::ground::mesh *ground = utils::mex_convert_mx_to_ptr<enve::ground::mesh>(arg_in_2);
  real_type const    *matrix_ptr;
  mwSize              rows, cols;
  matrix_ptr = utils::mex_matrix_pointer(arg_in_3, rows, cols, CMD "error in reading affine transformation matrix");
  UTILS_MEX_ASSERT(rows == 4 || cols == 4, CMD "expected rows = 4 and cols = 4 found, rows = " << rows << ", cols = " << cols << "\n");
  acme::affine matrix;
  matrix.matrix() << matrix_ptr[0], matrix_ptr[4], matrix_ptr[8],  matrix_ptr[12],
                     matrix_ptr[1], matrix_ptr[5], matrix_ptr[9],  matrix_ptr[13],
                     matrix_ptr[2], matrix_ptr[6], matrix_ptr[10], matrix_ptr[14],
                     matrix_ptr[3], matrix_ptr[7], matrix_ptr[11], matrix_ptr[15];
  string method = mxArrayToString(arg_in_4);
  bool   out    = self->setup(*ground, matrix, method);
  utils::mex_set_scalar_bool(arg_out_0, out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointAvg', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  acme::point *out  = new acme::point();
  self->contactPoint(*out);
  arg_out_0 = utils::mex_convert_ptr_to_mx<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointRib(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointRib', OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  acme::point *out  = new acme::point();
  self->contactPoint(i - 1, *out);
  arg_out_0 = utils::mex_convert_ptr_to_mx<acme::point>(out);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactNormalAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactNormalAvg', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 3, 1);
  acme::vec3   outvec;
  self->contactNormal(outvec);
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactNormalRib(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactNormalRib', OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  int          i      = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 3, 1);
  vec3         outvec;
  self->contactNormal(i - 1, outvec);
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactDepthAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactDepthAvg', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self  = DATA_GET(arg_in_1);
  real_type    depth;
  self->contactDepth(depth);
  utils::mex_set_scalar_value(arg_out_0, depth);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactDepthRib(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactDepthRib',  OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self  = DATA_GET(arg_in_1);
  int          i     = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  real_type    depth;
  self->contactDepth(i - 1, depth);
  utils::mex_set_scalar_value(arg_out_0, depth);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactFrictionAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactFrictionAvg', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    friction;
  self->contactFriction(friction);
  utils::mex_set_scalar_value(arg_out_0, friction);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactFrictionRib(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactFrictionRib',  OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  real_type    friction;
  self->contactFriction(i - 1, friction);
  utils::mex_set_scalar_value(arg_out_0, friction);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactAreaAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactAreaAvg', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    area;
  self->contactArea(area);
  utils::mex_set_scalar_value(arg_out_0, area);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactAreaRib(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactAreaRib',  OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  real_type    area;
  self->contactArea(i - 1, area);
  utils::mex_set_scalar_value(arg_out_0, area);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactVolumeAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactVolumeAvg', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  real_type    volume;
  self->contactVolume(volume);
  utils::mex_set_scalar_value(arg_out_0, volume);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactVolumeRib(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactVolumeRib',  OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self = DATA_GET(arg_in_1);
  int          i    = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  real_type    volume;
  self->contactVolume(i - 1, volume);
  utils::mex_set_scalar_value(arg_out_0, volume);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointAffineAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointAffineAvg', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 4, 4);
  acme::affine outmat;
  self->contactPointAffine(outmat);
  output[0]  = outmat(0,0);
  output[1]  = outmat(1,0);
  output[2]  = outmat(2,0);
  output[3]  = outmat(3,0);
  output[4]  = outmat(0,1);
  output[5]  = outmat(1,1);
  output[6]  = outmat(2,1);
  output[7]  = outmat(3,1);
  output[8]  = outmat(0,2);
  output[9]  = outmat(1,2);
  output[10] = outmat(2,2);
  output[11] = outmat(3,2);
  output[12] = outmat(0,3);
  output[13] = outmat(1,3);
  output[14] = outmat(2,3);
  output[15] = outmat(3,3);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_contactPointAffineRib(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'contactPointAffineRib', OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  int          i      = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 4, 4);
  acme::affine outmat;
  self->contactPointAffine(i - 1, outmat);
  output[0]  = outmat(0,0);
  output[1]  = outmat(1,0);
  output[2]  = outmat(2,0);
  output[3]  = outmat(3,0);
  output[4]  = outmat(0,1);
  output[5]  = outmat(1,1);
  output[6]  = outmat(2,1);
  output[7]  = outmat(3,1);
  output[8]  = outmat(0,2);
  output[9]  = outmat(1,2);
  output[10] = outmat(2,2);
  output[11] = outmat(3,2);
  output[12] = outmat(0,3);
  output[13] = outmat(1,3);
  output[14] = outmat(2,3);
  output[15] = outmat(3,3);
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_relativeAnglesAvg(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'relativeAnglesAvg', OBJ ): "
  UTILS_MEX_ASSERT(nrhs == 2, CMD "expected 2 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 3, 1);
  acme::vec3   outvec;
  self->relativeAngles(outvec);
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static void
do_relativeAnglesRib(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[])
{
#define CMD "mex_shell( 'relativeAnglesRib', OBJ, I ): "
  UTILS_MEX_ASSERT(nrhs == 3, CMD "expected 3 inputs, nrhs = " << nrhs << "\n");
  UTILS_MEX_ASSERT(nlhs == 1, CMD "expected 1 output, nlhs = " << nlhs << "\n");

  enve::shell *self   = DATA_GET(arg_in_1);
  int          i      = utils::mex_get_int64(arg_in_2, CMD "error in reading input value");
  real_type   *output = utils::mex_create_matrix_value(arg_out_0, 3, 1);
  acme::vec3   outvec;
  self->relativeAngles(i - 1, outvec);
  output[0] = outvec.x();
  output[1] = outvec.y();
  output[2] = outvec.z();
#undef CMD
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef void (*DO_CMD)(int nlhs, mxArray *plhs[], int nrhs, mxArray const *prhs[]);

static map<string, DO_CMD> cmd_to_fun = {
  {"new",    do_new},
  {"delete", do_delete},
  {"resize", do_resize},
  {"size",   do_size},
  // Shape
  {"surfaceMaxRadius",  do_surfaceMaxRadius},
  {"surfaceMaxWidth",   do_surfaceMaxWidth},
  {"surfaceWidth",      do_surfaceWidth},
  {"checkWidthBound",   do_checkWidthBound},
  {"surfaceRadius",     do_surfaceRadius},
  {"surfaceDerivative", do_surfaceDerivative},
  {"surfaceAngle",      do_surfaceAngle},
  {"ribRadius",         do_ribRadius},
  {"ribCenter",         do_ribCenter},
  {"ribWidth",          do_ribWidth},
  {"ribAngle",          do_ribAngle},
  // Affine
  {"translate",           do_translate},
  {"translation",         do_translation},
  {"rotate",              do_rotate},
  {"rotation",            do_rotation},
  {"transform",           do_transform},
  {"transformation",      do_transformation},
  {"checkTransformation", do_checkTransformation},
  {"x",                   do_x},
  {"y",                   do_y},
  {"z",                   do_z},
  {"eulerAngles",         do_eulerAngles},
  // Setup
  {"setupFlat", do_setupFlat},
  {"setupMesh", do_setupMesh},
  // Contact
  {"contactPointAvg",       do_contactPointAvg},
  {"contactPointRib",       do_contactPointRib},
  {"contactNormalAvg",      do_contactNormalAvg},
  {"contactNormalRib",      do_contactNormalRib},
  {"contactDepthAvg",       do_contactDepthAvg},
  {"contactDepthRib",       do_contactDepthRib},
  {"contactFrictionAvg",    do_contactFrictionAvg},
  {"contactFrictionRib",    do_contactFrictionRib},
  {"contactAreaAvg",        do_contactAreaAvg},
  {"contactAreaRib",        do_contactAreaRib},
  {"contactVolumeAvg",      do_contactVolumeAvg},
  {"contactVolumeRib",      do_contactVolumeRib},
  {"contactPointAffineAvg", do_contactPointAffineAvg},
  {"contactPointAffineRib", do_contactPointAffineRib},
  {"relativeAnglesAvg",     do_relativeAnglesAvg},
  {"relativeAnglesRib",     do_relativeAnglesRib}};

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
    UTILS_MEX_ASSERT(mxIsChar(arg_in_0), "first argument must be a string\n");
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

///
/// eof: mex_shell.cc
///
