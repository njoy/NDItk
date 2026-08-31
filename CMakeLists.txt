########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.27 )

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
  "Build the NDItk unit tests and integrate with ctest" OFF
  "BUILD_TESTING AND NOT ${subproject}" OFF
)

cmake_dependent_option(
  NDItk.python
  "Build NDItk python bindings" ON
  "NOT ${subproject} OR DEFINED require.NDItk.python " OFF
)

if ( NDItk.python )
  set( require.tools.python CACHE BOOL ON )
endif()

option( NDItk.installation "Install NDItk" ON )

########################################################################
# Dependencies
########################################################################

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( cmake/dependencies.cmake )

########################################################################
# Project targets
########################################################################

string( CONCAT prefix
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# NDItk : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( NDItk INTERFACE )
add_library( njoy::NDItk ALIAS NDItk )

target_include_directories( NDItk INTERFACE ${prefix} )

target_link_libraries( NDItk
  INTERFACE
    njoy::tools
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# NDItk : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if (NDItk.python AND NOT TARGET njoy::tools.python)
  message(WARNING "njoy::tools was not built with python enabled.  Disabling build of NDItk's python API.")
  set(NDItk.python OFF)
endif()

if ( NDItk.python )
  add_subdirectory( python )
endif()

if( NDItk.tests )
  add_subdirectory( test )
endif()

#######################################################################
# Installation
#######################################################################

if(NDItk.installation)
    include(CMakePackageConfigHelpers)

    install(TARGETS NDItk EXPORT NDItk-targets
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    install(EXPORT NDItk-targets
      FILE "NDItk-targets.cmake"
      NAMESPACE njoy::
      DESTINATION share/cmake/NDItk
    )

    install(DIRECTORY src/
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      FILES_MATCHING PATTERN "*.hpp"
      PATTERN "*test*" EXCLUDE
    )

    string(TOLOWER NDItk lowercasePackageName)

    write_basic_package_version_file("${lowercasePackageName}-config-version.cmake"
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion)

    configure_package_config_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${lowercasePackageName}-config.cmake.in
      ${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake
      INSTALL_DESTINATION share/cmake/NDItk
    )

    install(FILES
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake"
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config-version.cmake"
      DESTINATION share/cmake/NDItk
    )

    if(NOT subproject)
      set(CPACK_PACKAGE_VENDOR "Los Alamos National Laboratory")
      set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
      include(CPack)
    endif()
endif()

########################################################################
# Windows-specific setup
########################################################################

# enable Edit and Continue in Visual Studio (for debugging)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  if(MSVC)
    target_compile_options(${PROJECT_NAME}  INTERFACE "/ZI")
    target_link_options(${PROJECT_NAME} INTERFACE "/INCREMENTAL")
  endif()
endif()
