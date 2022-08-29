# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                     #
# The ENVE project                                                    #
#                                                                     #
# Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            #
#                                                                     #
# The ENVE project can not be copied and/or distributed without the   #
# express permission of Davide Stocco and Enrico Bertolazzi.          #
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

cmake_minimum_required(VERSION 3.2.0)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
# set(CMAKE_INSTALL_MESSAGE NEVER)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(ENABLE_CTEST)
  enable_testing()
endif()

# Get version from the git tag
execute_process(
  COMMAND git describe --tags --abbrev=0 OUTPUT_VARIABLE VERSION
)
string(REGEX REPLACE "\n$" "" VERSION "${VERSION}")

project(
  enve 
  VERSION ${VERSION}
  HOMEPAGE_URL "https://stoccodavide.github.io/enve"
)

# NOTE: Predictable target name
set(STATIC_PROJECT "${PROJECT_NAME}Static")
set(DYNAMIC_PROJECT "${PROJECT_NAME}")

include( ./CMakeLists-cflags.txt )
include( ./CMakeUtilities.txt )

if ( NOT BITS )
  set( BITS "x64" )
endif()

# Evaluating the suffix to append to target built by this CMake file
ebertolazzi_artifacts_suffix(ARTIFACTS_STATIC_SUFFIX TRUE)
if(BUILD_SHARED)
  ebertolazzi_artifacts_suffix(ARTIFACTS_DYNAMIC_SUFFIX FALSE)
endif()

message( STATUS "Compiler used: ${CMAKE_CXX_COMPILER_ID}")

set( CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} )
set( CMAKE_C_FLAGS_DEBUG   ${CMAKE_CXX_FLAGS_DEBUG} )

set( SOURCES )
file( GLOB S ./src/*.cc )
foreach (F ${S})
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND SOURCES ${RF} )
endforeach (F ${S})

set( HEADERS )
file( GLOB S ./include/*.hh )
foreach (F ${S})
  file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
  list( APPEND HEADERS ${RF} )
endforeach (F ${S})

if(SIMULATOR_SHELLS_NUMBER EQUAL 1)

  # Include S-Function directories
  include_directories( ./sfun/Simulator1/include_sfun ./sfun/Simulator1/src_sfun )

  # Include S-Function sources
  file( GLOB S ./sfun/Simulator1/src_sfun/*.cc )
  foreach (F ${S})
    file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
    list( APPEND SOURCES ${RF} )
  endforeach (F ${S})

  # Include S-Function headers
  file( GLOB S ./sfun/Simulator1/include_sfun/* )
  foreach (F ${S})
    file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
    list( APPEND HEADERS ${RF} )
  endforeach (F ${S})

elseif(SIMULATOR_SHELLS_NUMBER EQUAL 4)

  # Include S-Function directories
  include_directories( ./sfun/Simulator4/include_sfun ./sfun/Simulator4/src_sfun )

  # Include S-Function sources
  file( GLOB S ./sfun/Simulator4/src_sfun/*.cc )
  foreach (F ${S})
    file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
    list( APPEND SOURCES ${RF} )
  endforeach (F ${S})

  # Include S-Function headers
  file( GLOB S ./sfun/Simulator4/include_sfun/* )
  foreach (F ${S})
    file( RELATIVE_PATH RF ${CMAKE_CURRENT_SOURCE_DIR} "${F}" )
    list( APPEND HEADERS ${RF} )
  endforeach (F ${S})

endif()

# Dependencies (try to use already complied submodule on large project)
set(UPDIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(DEPEND_TARGETS)

find_library(
  UTILS Utils${ARTIFACTS_STATIC_SUFFIX}
  HINTS ${UPDIR}/Utils/lib/lib
  NO_DEFAULT_PATH
)
if( UTILS )
  include_directories(${UPDIR}Utils/lib/include)
  message( STATUS "Found library UTILS = ${UTILS}")
else()
  add_subdirectory(submodules/acme/submodules/Utils)
  set( UTILS ebertolazzi_Utils_Static )
  set( DEPEND_TARGETS ${DEPEND_TARGETS} ${UTILS} )
  message( STATUS "Include submodules UTILS = ${UTILS}")
endif()

find_library(
  ACME acme${ARTIFACTS_STATIC_SUFFIX}
  HINTS ${UPDIR}/acme/lib/lib
  NO_DEFAULT_PATH
)
if( ACME )
  include_directories(${UPDIR}/acme/lib/include)
  message( STATUS "Found library ACME = ${ACME}")
else()
  add_subdirectory(submodules/acme)
  set( ACME acmeStatic )
  set( DEPEND_TARGETS ${DEPEND_TARGETS} acmeStatic )
  message( STATUS "Include submodules ACME = ${ACME}")
endif()

include_directories( include src lib3rd/include lib3rd/include )

set( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lib )

add_library( ${STATIC_PROJECT} STATIC ${SOURCES} )

set_target_properties(
  ${STATIC_PROJECT} PROPERTIES
  OUTPUT_NAME "${PROJECT_NAME}${ARTIFACTS_STATIC_SUFFIX}"
  # FIXME: I'm not sure if this is required for OSX Framework
  PUBLIC_HEADER "${HEADERS}"
  POSITION_INDEPENDENT_CODE ON
)

if ( NOT ( "${DEPEND_TARGETS}" STREQUAL "" ) )
  add_dependencies( ${STATIC_PROJECT} ${DEPEND_TARGETS} )
endif()

if(BUILD_SHARED)
  add_library(${DYNAMIC_PROJECT} SHARED ${SOURCES})
  set_target_properties(
    ${DYNAMIC_PROJECT} PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}${ARTIFACTS_DYNAMIC_SUFFIX}"
    # FIXME: I'm not sure if this is required for OSX Framework
    PUBLIC_HEADER "${HEADERS}"
    POSITION_INDEPENDENT_CODE ON
  )
  target_link_libraries( ${DYNAMIC_PROJECT} PUBLIC ${ACME} ${UTILS} )
  if(WIN32)
    set_target_properties(
      ${DYNAMIC_PROJECT} PROPERTIES
      WINDOWS_EXPORT_ALL_SYMBOLS TRUE
    )
  endif()
endif()

if(BUILD_EXECUTABLE OR ENABLE_CTEST)
  enable_testing()
  set(TEST_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  file( GLOB S ./tests/*.cc )
  foreach( EXE_SRC ${S} )
    cmake_path(GET EXE_SRC FILENAME SRC_BASE)
    cmake_path(GET SRC_BASE STEM EXE)
    add_executable(${EXE} tests/${EXE}.cc)
    target_link_libraries(${EXE} PRIVATE ${STATIC_PROJECT} ${ACME} ${UTILS} ${CMAKE_DL_LIBS})
    set_target_properties(
      ${EXE} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${TEST_OUTPUT_PATH}"
    )
    add_test(${EXE} "${CMAKE_CURRENT_SOURCE_DIR}/bin/${EXE}")
  endforeach()
endif()

# Install targets
set(INSTALL_TARGETS ${STATIC_PROJECT})
if(BUILD_SHARED)
  set(INSTALL_TARGETS ${INSTALL_TARGETS} ${DYNAMIC_PROJECT})
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/CMakeInstall.txt")

message(STATUS "Using ${SSE_FLAGS} extensions")
message(STATUS "C compiler                  = ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER}")
message(STATUS "C++ compiler                = ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE     = ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CMAKE_CXX_FLAGS             = ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_C_FLAGS_RELEASE       = ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "CMAKE_C_FLAGS               = ${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_SYSTEM_NAME           = ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR      = ${CMAKE_SYSTEM_PROCESSOR}")
if(APPLE)
  message(STATUS "CMAKE_OSX_SYSROOT           = ${CMAKE_OSX_SYSROOT}")
  message(STATUS "CMAKE_OSX_ARCHITECTURES     = ${CMAKE_OSX_ARCHITECTURES}")
  message(STATUS "CMAKE_OSX_DEPLOYMENT_TARGET = ${CMAKE_OSX_DEPLOYMENT_TARGET}")
endif()
message(STATUS "BUILD_EXECUTABLE            = ${BUILD_EXECUTABLE}")
message(STATUS "SOURCES = ${SOURCES}")
message(STATUS "HEADERS = ${HEADERS}")
