#######################################################################
# Setup
#######################################################################

message( STATUS "Adding NDItk unit testing" )
enable_testing()

FetchContent_MakeAvailable( Catch2 )

function( add_cpp_test name source )

  set( test_name "NDItk.${name}.test" )
  add_executable( ${test_name} ${source} )
  add_test( NAME ${test_name} COMMAND ${test_name} )
  target_link_libraries( ${test_name} PRIVATE NDItk )
  target_link_libraries( ${test_name} PRIVATE Catch2::Catch2WithMain )

  file( GLOB resources "resources/*" )
  foreach( resource ${resources} )
    file( COPY "${resource}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
  endforeach()

endfunction()

#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/NDItk/base/Keyword/test )
add_subdirectory( src/NDItk/base/SingleIntegerRecord/test )
add_subdirectory( src/NDItk/base/SingleRealRecord/test )
add_subdirectory( src/NDItk/base/SingleStringRecord/test )
add_subdirectory( src/NDItk/base/IntegerListRecord/test )
add_subdirectory( src/NDItk/base/RealListRecord/test )
add_subdirectory( src/NDItk/base/StringListRecord/test )
add_subdirectory( src/NDItk/base/InformationRecord/test )

add_subdirectory( src/NDItk/depletion/Multiplicities/test )
add_subdirectory( src/NDItk/depletion/ReactionMultiplicities/test )

add_subdirectory( src/NDItk/multigroup/Metadata/test )
add_subdirectory( src/NDItk/multigroup/EnergyGroupStructure/test )
add_subdirectory( src/NDItk/multigroup/FluxWeights/test )
add_subdirectory( src/NDItk/multigroup/CrossSection/test )
add_subdirectory( src/NDItk/multigroup/ReactionCrossSections/test )
add_subdirectory( src/NDItk/multigroup/TotalCrossSection/test )
add_subdirectory( src/NDItk/multigroup/AverageFissionEnergyRelease/test )
add_subdirectory( src/NDItk/multigroup/Velocities/test )
add_subdirectory( src/NDItk/multigroup/HeatingNumbers/test )
add_subdirectory( src/NDItk/multigroup/Kerma/test )
add_subdirectory( src/NDItk/multigroup/OutgoingParticleTypes/test )
add_subdirectory( src/NDItk/multigroup/OutgoingParticleTransportData/test )
add_subdirectory( src/NDItk/multigroup/LegendreMoment/test )
add_subdirectory( src/NDItk/multigroup/ScatteringMatrix/test )

add_subdirectory( src/NDItk/MultigroupTable/test )
