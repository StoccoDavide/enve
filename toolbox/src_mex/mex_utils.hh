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
/// file: mex_utils.cc
///

#ifndef MEX_UTILS
#define MEX_UTILS

#include "mex.h"
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#define arg_in_0 prhs[0]
#define arg_in_1 prhs[1]
#define arg_in_2 prhs[2]
#define arg_in_3 prhs[3]
#define arg_in_4 prhs[4]
#define arg_in_5 prhs[5]
#define arg_in_6 prhs[6]
#define arg_in_7 prhs[7]
#define arg_in_8 prhs[8]
#define arg_in_9 prhs[9]
#define arg_in_10 prhs[10]
#define arg_in_11 prhs[11]

#define arg_out_0 plhs[0]
#define arg_out_1 plhs[1]
#define arg_out_2 plhs[2]
#define arg_out_3 plhs[3]
#define arg_out_4 plhs[4]
#define arg_out_5 plhs[5]
#define arg_out_6 plhs[6]
#define arg_out_7 plhs[7]
#define arg_out_8 plhs[8]
#define arg_out_9 plhs[9]

#define MEX_ASSERT(COND, MSG)            \
  if (!(COND))                           \
  {                                      \
    std::ostringstream ost;              \
    ost << "Mex Error: " << MSG << "\n"; \
    mexErrMsgTxt(ost.str().c_str());     \
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline bool
isScalar(mxArray const *arg, char const msg[])
{
  mwSize number_of_dimensions = mxGetNumberOfDimensions(arg);
  MEX_ASSERT(number_of_dimensions == 2, msg);
  mwSize const *dims = mxGetDimensions(arg);
  return dims[0] == 1 && dims[1] == 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline double
getScalarValue(mxArray const *arg, char const msg[])
{
  mwSize number_of_dimensions = mxGetNumberOfDimensions(arg);
  MEX_ASSERT(number_of_dimensions == 2, msg);
  mwSize const *dims = mxGetDimensions(arg);
  MEX_ASSERT(
      dims[0] == 1 && dims[1] == 1,
      msg << ", found " << dims[0] << " x " << dims[1] << " matrix\n");
  return mxGetScalar(arg);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline bool
getBool(mxArray const *arg, char const msg[])
{
  MEX_ASSERT(mxIsLogicalScalar(arg), msg);
  return mxIsLogicalScalarTrue(arg);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline int64_t
getInt(mxArray const *arg, char const msg[])
{
  mwSize number_of_dimensions = mxGetNumberOfDimensions(arg);
  MEX_ASSERT(number_of_dimensions == 2, msg);
  mwSize const *dims = mxGetDimensions(arg);
  MEX_ASSERT(
      dims[0] == 1 && dims[1] == 1,
      msg << ", found " << dims[0] << " x " << dims[1] << " matrix\n");
  mxClassID category = mxGetClassID(arg);
  int64_t res = 0;
  void *ptr = mxGetData(arg);
  switch (category)
  {
  case mxINT8_CLASS:
    res = *static_cast<uint8_t *>(ptr);
    break;
  case mxUINT8_CLASS:
    res = *static_cast<uint8_t *>(ptr);
    break;
  case mxINT16_CLASS:
    res = *static_cast<int16_t *>(ptr);
    break;
  case mxUINT16_CLASS:
    res = *static_cast<uint16_t *>(ptr);
    break;
  case mxINT32_CLASS:
    res = *static_cast<int32_t *>(ptr);
    break;
  case mxUINT32_CLASS:
    res = *static_cast<uint32_t *>(ptr);
    break;
  case mxINT64_CLASS:
    res = *static_cast<int64_t *>(ptr);
    break;
  case mxUINT64_CLASS:
    res = *static_cast<uint64_t *>(ptr);
    break;
  case mxDOUBLE_CLASS:
  {
    double tmp = *static_cast<double *>(ptr);
    MEX_ASSERT(
        tmp == std::floor(tmp),
        msg << " expected int, found " << tmp << "\n");
    res = static_cast<int64_t>(tmp);
  }
  break;
  case mxSINGLE_CLASS:
  {
    float tmp = *static_cast<float *>(ptr);
    MEX_ASSERT(
        tmp == std::floor(tmp),
        msg << " expected int, found " << tmp << "\n");
    res = static_cast<int64_t>(tmp);
  }
  break;
  default:
    MEX_ASSERT(false, msg << " bad type scalar");
    break;
  }
  return res;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline double const *
getVectorPointer(mxArray const *arg, mwSize &sz, char const msg[])
{
  mwSize number_of_dimensions = mxGetNumberOfDimensions(arg);
  MEX_ASSERT(number_of_dimensions == 2, msg);
  mwSize const *dims = mxGetDimensions(arg);
  MEX_ASSERT(
      dims[0] == 1 || dims[1] == 1,
      msg << "\nExpect (1 x n or n x 1) matrix, found " << dims[0] << " x " << dims[1] << "\n");
  sz = dims[0] * dims[1];
  return mxGetPr(arg);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline double const *
getMatrixPointer(mxArray const *arg, mwSize &nr, mwSize &nc, char const msg[])
{
  mwSize number_of_dimensions = mxGetNumberOfDimensions(arg);
  MEX_ASSERT(number_of_dimensions == 2, msg);
  mwSize const *dims = mxGetDimensions(arg);
  nr = dims[0];
  nc = dims[1];
  return mxGetPr(arg);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline void
setScalarValue(mxArray *&arg, double value)
{
  arg = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
  *mxGetPr(arg) = value;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline void
setScalarInt(mxArray *&arg, int32_t value)
{
  arg = mxCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
  *static_cast<int32_t *>(mxGetData(arg)) = value;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline void
setScalarBool(mxArray *&arg, bool value)
{
  arg = mxCreateLogicalScalar(value);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline int32_t *
createMatrixInt32(mxArray *&arg, mwSize nrow, mwSize ncol)
{
  arg = mxCreateNumericMatrix(nrow, ncol, mxINT32_CLASS, mxREAL);
  return static_cast<int32_t *>(mxGetData(arg));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline int64_t *
createMatrixInt64(mxArray *&arg, mwSize nrow, mwSize ncol)
{
  arg = mxCreateNumericMatrix(nrow, ncol, mxINT64_CLASS, mxREAL);
  return static_cast<int64_t *>(mxGetData(arg));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline double *
createMatrixValue(mxArray *&arg, mwSize nrow, mwSize ncol)
{
  arg = mxCreateNumericMatrix(nrow, ncol, mxDOUBLE_CLASS, mxREAL);
  return mxGetPr(arg);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

static inline double *
createArray(mxArray *&arg, mwSize ndim, mwSize const *dims)
{
  arg = mxCreateNumericArray(ndim, dims, mxDOUBLE_CLASS, mxREAL);
  return mxGetPr(arg);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Class Handle by Oliver Woodford
// https://it.mathworks.com/matlabcentral/fileexchange/38964-example-matlab-class-wrapper-for-a-c++-class

#ifndef MEX_CLASS_HANDLE
#define MEX_CLASS_HANDLE
#include "mex.h"
#include <cstring>
#include <stdint.h>
#include <string>
#include <typeinfo>

#define CLASS_HANDLE_SIGNATURE 0xFF00F0A5

template <typename base>
class class_handle
{
  uint32_t signature_m;
  base *ptr_m;
  std::string name_m;

  public:
  class_handle(base *ptr)
      : ptr_m(ptr), name_m(typeid(base).name())
  {
    signature_m = CLASS_HANDLE_SIGNATURE;
  }

  ~class_handle()
  {
    signature_m = 0;
    delete ptr_m;
  }

  bool isValid()
  {
    return ((signature_m == CLASS_HANDLE_SIGNATURE) &&
            !strcmp(name_m.c_str(), typeid(base).name()));
  }

  base *ptr() { return ptr_m; }
};

template <typename base>
inline mxArray *
convertPtr2Mat(base *ptr)
{
  mexLock();
  mxArray *out = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
  *((uint64_t *)mxGetData(out)) = reinterpret_cast<uint64_t>(new class_handle<base>(ptr));
  return out;
}

template <typename base>
inline class_handle<base> *
convertMat2HandlePtr(const mxArray *in)
{
  if (mxGetNumberOfElements(in) != 1 || mxGetClassID(in) != mxUINT64_CLASS || mxIsComplex(in))
    mexErrMsgTxt("Input must be an uint64 scalar.");
  class_handle<base> *ptr = reinterpret_cast<class_handle<base> *>(*((uint64_t *)mxGetData(in)));
  if (!ptr->isValid())
    mexErrMsgTxt("Handle not valid.");
  return ptr;
}

template <typename base>
inline base *
convertMat2Ptr(const mxArray *in)
{
  return convertMat2HandlePtr<base>(in)->ptr();
}

template <typename base>
inline void
destroyObject(const mxArray *in)
{
  if (in != nullptr)
    delete convertMat2HandlePtr<base>(in);
  in = nullptr;
  mexUnlock();
}

#endif

#endif

///
/// eof: mex_utils.cc
///
