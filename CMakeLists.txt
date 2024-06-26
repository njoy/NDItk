########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( NDItk
  VERSION 0.1.0
  LANGUAGES CXX
)

include( CTest )
include( CMakeDependentOption )
include( GNUInstallDirs )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

cmake_dependent_option(
  NDItk.tests
  "Build the NDItk unit tests and integrate with ctest" ON
  "BUILD_TESTING AND NOT ${subproject}" OFF
)
cmake_dependent_option(
  NDItk.python
  "Build NDItk python bindings" ON
  "NOT ${subproject}" OFF
)

########################################################################
# Dependencies
########################################################################

set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

message( STATUS "Using ${REPOSITORIES} repositories" )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "local" )
    include( cmake/local_dependencies.cmake )

endif()


########################################################################
# Project targets
########################################################################

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# NDItk : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( NDItk INTERFACE )
add_library( njoy::NDItk ALIAS NDItk )
target_include_directories( NDItk
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries( NDItk
  INTERFACE
    njoy::tools
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# NDItk : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( NDItk.python )

  FetchContent_MakeAvailable( pybind11 )

  pybind11_add_module( NDItk.python
      python/src/NDItk.python.cpp
      )

  target_link_libraries( NDItk.python PRIVATE NDItk )
  target_include_directories( NDItk.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( NDItk.python PRIVATE "-fvisibility=hidden" )
  set_target_properties( NDItk.python PROPERTIES OUTPUT_NAME NDItk )
  set_target_properties( NDItk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( NDItk.python PROPERTIES POSITION_INDEPENDENT_CODE ON )

  message( STATUS "Building NDItk's python API" )

  list( APPEND NDItk_PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR} )

  include( cmake/unit_testing_python.cmake )

endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  if( NDItk.tests )
    include( cmake/unit_testing.cmake )
  endif()
endif()
