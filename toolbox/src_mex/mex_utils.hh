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
/// file: mex_utils.hh
///

#ifndef MEX_UTILS
#define MEX_UTILS

#include "mex.h"
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <typeinfo>

#define CLASS_HANDLE_SIGNATURE 0xFF00F0A5

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
#define arg_in_12 prhs[12]
#define arg_in_13 prhs[13]
#define arg_in_14 prhs[14]
#define arg_in_15 prhs[15]
#define arg_in_16 prhs[16]
#define arg_in_17 prhs[17]
#define arg_in_18 prhs[18]
#define arg_in_19 prhs[19]

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
#define arg_out_10 plhs[10]
#define arg_out_11 plhs[11]
#define arg_out_12 plhs[12]
#define arg_out_13 plhs[13]
#define arg_out_14 plhs[14]
#define arg_out_15 plhs[14]
#define arg_out_16 plhs[16]
#define arg_out_17 plhs[17]
#define arg_out_18 plhs[18]
#define arg_out_19 plhs[19]

#define UTILS_MEX_ASSERT(COND, MSG)      \
  if (!(COND))                           \
  {                                      \
    std::ostringstream ost;              \
    ost << "Mex Error: " << MSG << '\n'; \
    mexErrMsgTxt(ost.str().c_str());     \
  }

namespace utils {

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  void
  mex_error_message( std::string msg ) {
    mexErrMsgTxt( msg.c_str() );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  bool
  mex_is_scalar( mxArray const * arg, char const msg[] ){
    mwSize number_of_dimensions = mxGetNumberOfDimensions(arg);
    UTILS_MEX_ASSERT(
      number_of_dimensions == 2,
      msg
      );
    mwSize const * dims = mxGetDimensions(arg);
    return dims[0] == 1 && dims[1] == 1;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  bool
  mex_is_scalar( mxArray const * arg, std::string msg ) {
    return mex_is_scalar( arg, msg.c_str() );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  double
  mex_get_scalar_value( mxArray const * arg, char const msg[] ) {
    mwSize number_of_dimensions = mxGetNumberOfDimensions(arg);
    UTILS_MEX_ASSERT(
      number_of_dimensions == 2,
      msg
      );
    mwSize const * dims = mxGetDimensions(arg);
    UTILS_MEX_ASSERT(
      dims[0] == 1 && dims[1] == 1,
      msg << ", found " << dims[0] << " x " << dims[1] << " matrix\n"
      );
    return mxGetScalar(arg);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  double
  mex_get_scalar_value( mxArray const * arg, std::string msg ) {
    return mex_get_scalar_value( arg, msg.c_str() );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  bool
  mex_get_bool( mxArray const * arg, char const msg[] ) {
    UTILS_MEX_ASSERT(
      mxIsLogicalScalar(arg),
      msg
      );
    return mxIsLogicalScalarTrue(arg);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  bool
  mex_get_bool( mxArray const * arg, std::string msg ) {
    return mex_get_bool( arg, msg.c_str() );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  int64_t
  mex_get_int64( mxArray const * arg, char const msg[] ) {
    mwSize number_of_dimensions = mxGetNumberOfDimensions(arg);
    UTILS_MEX_ASSERT(
      number_of_dimensions == 2,
      msg
      );
    mwSize const * dims = mxGetDimensions(arg);
    UTILS_MEX_ASSERT(
      dims[0] == 1 && dims[1] == 1,
      msg << ", found " << dims[0] << " x " << dims[1] << " matrix\n"
      );
    mxClassID category = mxGetClassID(arg);
    int64_t res = 0;
    void *ptr = mxGetData(arg);
    switch (category)  {
      case mxINT8_CLASS:   res = *static_cast<uint8_t*>(ptr); break;
      case mxUINT8_CLASS:  res = *static_cast<uint8_t*>(ptr);  break;
      case mxINT16_CLASS:  res = *static_cast<int16_t*>(ptr);  break;
      case mxUINT16_CLASS: res = *static_cast<uint16_t*>(ptr); break;
      case mxINT32_CLASS:  res = *static_cast<int32_t*>(ptr);  break;
      case mxUINT32_CLASS: res = *static_cast<uint32_t*>(ptr); break;
      case mxINT64_CLASS:  res = *static_cast<int64_t*>(ptr);  break;
      case mxUINT64_CLASS: res = *static_cast<uint64_t*>(ptr); break;
      case mxDOUBLE_CLASS:
        { double tmp = *static_cast<double*>(ptr);
          UTILS_MEX_ASSERT(
            tmp == std::floor(tmp),
            msg << " expected int, found " << tmp << "\n"
            );
          res = static_cast<int64_t>(tmp);
        }
        break;
      case mxSINGLE_CLASS:
        { float tmp = *static_cast<float*>(ptr);
          UTILS_MEX_ASSERT(
            tmp == std::floor(tmp),
            msg << " expected int, found " << tmp << "\n"
            );
          res = static_cast<int64_t>(tmp);
        }
        break;
      default:
        UTILS_MEX_ASSERT(
          false,
          msg << " bad type scalar\n"
          );
      break;
    }
    return res;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  int64_t
  mex_get_int64( mxArray const * arg, std::string msg ) {
    return mex_get_int64( arg, msg.c_str() );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  double const *
  mex_vector_pointer(
    mxArray const * arg,
    mwSize        & sz,
    char const      msg[]
  ) {
    mwSize number_of_dimensions = mxGetNumberOfDimensions(arg);
    UTILS_MEX_ASSERT( number_of_dimensions == 2, msg );
    mwSize const * dims = mxGetDimensions(arg);
    UTILS_MEX_ASSERT(
      dims[0] == 1 || dims[1] == 1 || dims[0]*dims[1] == 0,
      msg << " expected (1 x n or n x 1 or empty) matrix, found "
          << dims[0] << " x " << dims[1] << "\n"
      );
    sz = dims[0]*dims[1];
    return mxGetPr(arg);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  double const *
  mex_vector_pointer(
    mxArray const * arg,
    mwSize        & sz,
    std::string     msg
  ) {
    return mex_vector_pointer( arg, sz, msg.c_str() );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  double const *
  mex_matrix_pointer(
    mxArray const * arg,
    mwSize        & nr,
    mwSize        & nc,
    char const    msg[]
  ) {
    mwSize number_of_dimensions = mxGetNumberOfDimensions(arg);
    UTILS_MEX_ASSERT(
      number_of_dimensions == 2,
      msg
      );
    mwSize const * dims = mxGetDimensions(arg);
    nr = dims[0];
    nc = dims[1];
    return mxGetPr(arg);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  double const *
  mex_matrix_pointer(
    mxArray const * arg,
    mwSize        & nr,
    mwSize        & nc,
    std::string     msg
  ) {
    return mex_matrix_pointer( arg, nr, nc, msg.c_str() );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  void
  mex_set_scalar_value( mxArray * & arg, double value ) {
    arg = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
    *mxGetPr(arg) = value;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  void
  mex_set_scalar_int32( mxArray * & arg, int32_t value ) {
    arg = mxCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
    *static_cast<int32_t*>(mxGetData(arg)) = value;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  void
  mex_set_scalar_int64( mxArray * & arg, int64_t value ) {
    arg = mxCreateNumericMatrix(1, 1, mxINT64_CLASS, mxREAL);
    *static_cast<int64_t*>(mxGetData(arg)) = value;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  void
  mex_set_scalar_bool( mxArray * & arg, bool value ) {
    arg = mxCreateLogicalScalar( value );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  int32_t *
  mex_create_matrix_int32( mxArray * & arg, mwSize nrow, mwSize ncol ) {
    arg = mxCreateNumericMatrix( nrow, ncol, mxINT32_CLASS, mxREAL );
    return static_cast<int32_t*>(mxGetData(arg));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  int64_t *
  mex_create_matrix_int64( mxArray * & arg, mwSize nrow, mwSize ncol ) {
    arg = mxCreateNumericMatrix( nrow, ncol, mxINT64_CLASS, mxREAL );
    return static_cast<int64_t*>(mxGetData(arg));
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  inline
  double *
  mex_create_matrix_value( mxArray * & arg, mwSize nrow, mwSize ncol ) {
    arg = mxCreateNumericMatrix( nrow, ncol, mxDOUBLE_CLASS, mxREAL );
    return mxGetPr(arg);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*
  Class Handle by Oliver Woodford
  https://it.mathworks.com/matlabcentral/fileexchange/38964-example-matlab-class-wrapper-for-a-c++-class
  */

  template <typename base>
  class mex_class_handle {
    uint32_t    m_signature;
    base *      m_ptr;
    std::string m_name;

  public:

    mex_class_handle<base> const & operator = ( mex_class_handle<base> const & ) = delete;
    mex_class_handle() = delete;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    explicit
    mex_class_handle( base * ptr )
    : m_signature(CLASS_HANDLE_SIGNATURE)
    , m_ptr(ptr)
    , m_name(typeid(base).name())
    {}

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    ~mex_class_handle()
    { m_signature = 0; delete m_ptr; m_ptr = nullptr; }

    bool is_valid()
    { return ((m_signature == CLASS_HANDLE_SIGNATURE) &&
              !strcmp(m_name.c_str(), typeid(base).name())); }

    base * ptr() { return m_ptr; }
  };

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  template <typename base>
  inline
  mxArray *
  mex_convert_ptr_to_mx( base * ptr ) {
    mexLock();
    mxArray *out = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    *((uint64_t *)mxGetData(out)) = reinterpret_cast<uint64_t>(
      new mex_class_handle<base>(ptr)
    );
    return out;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  template <typename base>
  inline
  mex_class_handle<base> *
  mex_convert_mx_to_handle_ptr( mxArray const * in ) {
    if ( mxGetNumberOfElements(in) != 1 ||
         mxGetClassID(in) != mxUINT64_CLASS ||
         mxIsComplex(in) )
      mexErrMsgTxt( "Input must be an uint64 scalar." );
    mex_class_handle<base> * ptr = reinterpret_cast<mex_class_handle<base> *>(
      *((uint64_t *)mxGetData(in))
    );
    if ( !ptr->is_valid() ) mexErrMsgTxt( "Handle not valid." );
    return ptr;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  template <typename base>
  inline
  base *
  mex_convert_mx_to_ptr( mxArray const * in ) {
    return mex_convert_mx_to_handle_ptr<base>(in)->ptr();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  template <typename base>
  inline
  void
  mex_destroy_object( mxArray const * & in ) {
    if ( in != nullptr ) delete mex_convert_mx_to_handle_ptr<base>(in);
    in = nullptr;
    mexUnlock();
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

#endif

///
/// eof: mex_utils.hh
///
