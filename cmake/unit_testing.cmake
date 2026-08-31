#######################################################################
# Setup
#######################################################################

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

message( STATUS "Adding NDItk C++ unit testing" )

add_cpp_test( base.Keyword base/Keyword.test.cpp )
add_cpp_test( base.InformationRecord base/InformationRecord.test.cpp )
add_cpp_test( base.IntegerListRecord base/IntegerListRecord.test.cpp )
add_cpp_test( base.RealListRecord base/RealListRecord.test.cpp )
add_cpp_test( base.SingleIntegerRecord base/SingleIntegerRecord.test.cpp )
add_cpp_test( base.SingleRealRecord base/SingleRealRecord.test.cpp )
add_cpp_test( base.SingleStringRecord base/SingleStringRecord.test.cpp )
add_cpp_test( base.StringListRecord base/StringListRecord.test.cpp )
add_cpp_test( base.ColumnData base/ColumnData.test.cpp )

add_cpp_test( depletion.IncidentParticle depletion/IncidentParticle.test.cpp )
add_cpp_test( depletion.Metadata depletion/Metadata.test.cpp )
add_cpp_test( depletion.Multiplicities depletion/Multiplicities.test.cpp )
add_cpp_test( depletion.Product depletion/Product.test.cpp )
add_cpp_test( depletion.Target depletion/Target.test.cpp )

add_cpp_test( multigroup.AverageFissionEnergyRelease multigroup/AverageFissionEnergyRelease.test.cpp )
add_cpp_test( multigroup.CrossSection multigroup/CrossSection.test.cpp )
add_cpp_test( multigroup.DownScatteringLegendreMoment multigroup/DownScatteringLegendreMoment.test.cpp )
add_cpp_test( multigroup.DownScatteringMatrix multigroup/DownScatteringMatrix.test.cpp )

add_cpp_test( multigroup.EnergyGroupStructure multigroup/EnergyGroupStructure.test.cpp )
add_cpp_test( multigroup.FissionNeutronMultiplicity multigroup/FissionNeutronMultiplicity.test.cpp )
add_cpp_test( multigroup.FissionNeutronProduction multigroup/FissionNeutronProduction.test.cpp )
add_cpp_test( multigroup.FissionNeutronSpectrumMatrix multigroup/FissionNeutronSpectrumMatrix.test.cpp )
add_cpp_test( multigroup.FissionNeutronSpectrumVector multigroup/FissionNeutronSpectrumVector.test.cpp )
add_cpp_test( multigroup.FluxWeights multigroup/FluxWeights.test.cpp )
add_cpp_test( multigroup.HeatingNumbers multigroup/HeatingNumbers.test.cpp )
add_cpp_test( multigroup.Kerma multigroup/Kerma.test.cpp )
add_cpp_test( multigroup.LegendreMoment multigroup/LegendreMoment.test.cpp )
add_cpp_test( multigroup.Metadata multigroup/Metadata.test.cpp )
add_cpp_test( multigroup.Multiplicities multigroup/Multiplicities.test.cpp )
add_cpp_test( multigroup.OutgoingParticleTransportData multigroup/OutgoingParticleTransportData.test.cpp )
add_cpp_test( multigroup.OutgoingParticleTypes multigroup/OutgoingParticleTypes.test.cpp )
add_cpp_test( multigroup.ReactionCrossSections multigroup/ReactionCrossSections.test.cpp )
add_cpp_test( multigroup.ReactionMultiplicities multigroup/ReactionMultiplicities.test.cpp )
add_cpp_test( multigroup.ScatteringMatrix multigroup/ScatteringMatrix.test.cpp )
add_cpp_test( multigroup.TotalCrossSection multigroup/TotalCrossSection.test.cpp )
add_cpp_test( multigroup.Velocities multigroup/Velocities.test.cpp )

add_cpp_test( thermonuclear.InterpolationRegions thermonuclear/InterpolationRegions.test.cpp )
add_cpp_test( thermonuclear.Temperatures thermonuclear/Temperatures.test.cpp )

add_cpp_test( dosimetry.Metadata dosimetry/Metadata.test.cpp )

add_cpp_test( CommentBlock CommentBlock.test.cpp )

add_cpp_test( DepletionTable DepletionTable.test.cpp )
add_cpp_test( MultigroupTable MultigroupTable.test.cpp )
add_cpp_test( DosimetryTable DosimetryTable.test.cpp )

add_cpp_test( DepletionLibrary DepletionLibrary.test.cpp )
add_cpp_test( MultigroupLibrary MultigroupLibrary.test.cpp )
