# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                     #
# The ACME project                                                    #
#                                                                     #
# Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            #
#                                                                     #
# The ACME project and its components are supplied under the terms of #
# the open source BSD 2-Clause License. The contents of the ACME      #
# project and its components may not be copied or disclosed except in #
# accordance with the terms of the BSD 2-Clause License.              #
#                                                                     #
# URL: https://opensource.org/licenses/BSD-2-Clause                   #
#                                                                     #
#    Davide Stocco                                                    #
#    Department of Industrial Engineering                             #
#    University of Trento                                             #
#    e-mail: davide.stocco@unitn.it                                   #
#                                                                     #
#    Enrico Bertolazzi                                                #
#    Department of Industrial Engineering                             #
#    University of Trento                                             #
#    e-mail: enrico.bertolazzi@unitn.it                               #
#                                                                     #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

cmake_minimum_required( VERSION 3.14 )

project( acme )

include(./cmake_utils/CMakeLists-common.txt)

project( ${PROJECT_NAME} VERSION ${UTILS_PROJECT_VERSION} )

if ( NOT DEFINED CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release )
endif()

find_package( Matlab REQUIRED )

message( STATUS "PROJECT_NAME        = ${PROJECT_NAME}" )
message( STATUS "Matlab_ROOT_DIR     = ${Matlab_ROOT_DIR}" )
message( STATUS "Matlab_INCLUDE_DIRS = ${Matlab_INCLUDE_DIRS}" )

if ( (UNIX OR LINUX) AND NOT APPLE )
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc -Wl,--no-undefined")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++ -static-libgcc -Wl,--no-undefined")
endif()

include(./cmake_utils/CMakeLists-cflags.txt)
include(./cmake_utils/CMakeLists-utilities.txt)

# Evaluating the suffix to append to target built by this CMake file
utils_artifacts_suffix(ARTIFACTS_STATIC_SUFFIX TRUE)
if( UTILS_BUILD_SHARED )
  utils_artifacts_suffix(ARTIFACTS_DYNAMIC_SUFFIX FALSE)
endif()

message( STATUS "Compiler used: ${CMAKE_CXX_COMPILER_ID}" )
message( STATUS "BASE SUFFIXES = ${ARTIFACTS_STATIC_SUFFIX} ${ARTIFACTS_DYNAMIC_SUFFIX}" )

#   ____                                _     _ _
#  |  _ \ _ __ ___ _ __ ___  __ _ _   _(_)___(_) |_ ___
#  | |_) | '__/ _ \ '__/ _ \/ _` | | | | / __| | __/ _ \
#  |  __/| | |  __/ | |  __/ (_| | |_| | \__ \ | ||  __/
#  |_|   |_|  \___|_|  \___|\__, |\__,_|_|___/_|\__\___|
#                              |_|

# MUST be executed before the build of the header list

#   ____
#  / ___|  ___  _   _ _ __ ___ ___  ___
#  \___ \ / _ \| | | | '__/ __/ _ \/ __|
#   ___) | (_) | |_| | | | (_|  __/\__ \
#  |____/ \___/ \__,_|_|  \___\___||___/
#

set( SOURCES )
file(
  GLOB_RECURSE S
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src_mex/*.cc
)
foreach(F ${S})
  # build relative path respect to source directory
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND SOURCES ${RF} )
endforeach(F ${S})

#   _   _                _
#  | | | | ___  __ _  __| | ___ _ __ ___
#  | |_| |/ _ \/ _` |/ _` |/ _ \ '__/ __|
#  |  _  |  __/ (_| | (_| |  __/ |  \__ \
#  |_| |_|\___|\__,_|\__,_|\___|_|  |___/
#

set( PUBLIC_HEADERS )
file(
  GLOB_RECURSE S
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h*
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.h*
)
foreach (F ${S})
  # build relative path respect to source directory
  file( RELATIVE_PATH RF "${CMAKE_CURRENT_SOURCE_DIR}" "${F}" )
  list( APPEND PUBLIC_HEADERS ${RF} )
endforeach(F ${S})

list(FILTER PUBLIC_HEADERS EXCLUDE REGEX "\.DS")

# extra include directory for compilation
include_directories( src src/Utils ${Matlab_INCLUDE_DIRS} )

message( STATUS "SOURCES = ${SOURCES}" )

#   _____                    _
#  |_   _|_ _ _ __ __ _  ___| |_ ___
#    | |/ _` | '__/ _` |/ _ \ __/ __|
#    | | (_| | | | (_| |  __/ |_\__ \
#    |_|\__,_|_|  \__, |\___|\__|___/
#                 |___/

utils_final_messages()

add_library( acme STATIC ${SOURCES} )

set(
  MEX_LIST
  mex_flat
  mex_mesh
  mex_shell
  mex_triangleground
)

message( STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
if ( CMAKE_BUILD_TYPE MATCHES Debug )
  message( STATUS "DEBUG MODE\n\n")
  add_compile_definitions(DEBUG)
  add_compile_definitions(ENVE_DEBUG)
endif()

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/bin")

foreach( MEX ${MEX_LIST} )
  matlab_add_mex(
    NAME ${MEX}
    SRC src_mex/${MEX}.cc
    LINK_TO acme
    OUTPUT_NAME ${MEX}
  )
  add_custom_command(
    TARGET ${MEX}
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:${MEX}>"
    "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )
endforeach()
