#######################################################################
# Setup
#######################################################################

enable_testing()

function( add_python_test name source )

  set(PYTHONPATH_PARTS ${tools_PYTHONPATH} ${NDItk_PYTHONPATH} $ENV{PYTHONPATH})
  string( JOIN "${PATH_DELIM}" PYTHONPATH_VALUE ${PYTHONPATH_PARTS})

  set( test_name "NDItk.python.${name}.test" )
  add_test( NAME ${test_name}
            COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/${source}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
  set_tests_properties( ${test_name}
                        PROPERTIES ENVIRONMENT
                        "PYTHONPATH=${PYTHONPATH_VALUE}")

endfunction()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding NDItk Python unit testing" )

add_python_test( thermonuclear.Temperatures               thermonuclear/Test_NDItk_thermonuclear_Temperatures.py )
add_python_test( thermonuclear.InterpolationRegions       thermonuclear/Test_NDItk_thermonuclear_InterpolationRegions.py )

add_python_test( depletion.Multiplicities                 depletion/Test_NDItk_depletion_Multiplicities.py )
add_python_test( depletion.Product                        depletion/Test_NDItk_depletion_Product.py )
add_python_test( depletion.Target                         depletion/Test_NDItk_depletion_Target.py )
add_python_test( depletion.IncidentParticle               depletion/Test_NDItk_depletion_IncidentParticle.py )
add_python_test( depletion.Metadata                       depletion/Test_NDItk_depletion_Metadata.py )

add_python_test( multigroup.Multiplicities                multigroup/Test_NDItk_multigroup_Multiplicities.py )
add_python_test( multigroup.ReactionMultiplicities        multigroup/Test_NDItk_multigroup_ReactionMultiplicities.py )
add_python_test( multigroup.Metadata                      multigroup/Test_NDItk_multigroup_Metadata.py )
add_python_test( multigroup.CrossSection                  multigroup/Test_NDItk_multigroup_CrossSection.py )
add_python_test( multigroup.DownScatteringLegendreMoment  multigroup/Test_NDItk_multigroup_DownScatteringLegendreMoment.py )
add_python_test( multigroup.DownScatteringMatrix          multigroup/Test_NDItk_multigroup_DownScatteringMatrix.py )
add_python_test( multigroup.FluxWeights                   multigroup/Test_NDItk_multigroup_FluxWeights.py )
add_python_test( multigroup.EnergyGroupStructure          multigroup/Test_NDItk_multigroup_EnergyGroupStructure.py )
add_python_test( multigroup.ReactionCrossSections         multigroup/Test_NDItk_multigroup_ReactionCrossSections.py )
add_python_test( multigroup.TotalCrossSection             multigroup/Test_NDItk_multigroup_TotalCrossSection.py )
add_python_test( multigroup.AverageFissionEnergyRelease   multigroup/Test_NDItk_multigroup_AverageFissionEnergyRelease.py )
add_python_test( multigroup.FissionNeutronMultiplicity    multigroup/Test_NDItk_multigroup_FissionNeutronMultiplicity.py )
add_python_test( multigroup.FissionNeutronProduction      multigroup/Test_NDItk_multigroup_FissionNeutronProduction.py )
add_python_test( multigroup.FissionNeutronSpectrumMatrix  multigroup/Test_NDItk_multigroup_FissionNeutronSpectrumMatrix.py )
add_python_test( multigroup.FissionNeutronSpectrumVector  multigroup/Test_NDItk_multigroup_FissionNeutronSpectrumVector.py )
add_python_test( multigroup.Velocities                    multigroup/Test_NDItk_multigroup_Velocities.py )
add_python_test( multigroup.HeatingNumbers                multigroup/Test_NDItk_multigroup_HeatingNumbers.py )
add_python_test( multigroup.Kerma                         multigroup/Test_NDItk_multigroup_Kerma.py )
add_python_test( multigroup.OutgoingParticleTypes         multigroup/Test_NDItk_multigroup_OutgoingParticleTypes.py )
add_python_test( multigroup.OutgoingParticleTransportData multigroup/Test_NDItk_multigroup_OutgoingParticleTransportData.py )
add_python_test( multigroup.LegendreMoment                multigroup/Test_NDItk_multigroup_LegendreMoment.py )
add_python_test( multigroup.ScatteringMatrix              multigroup/Test_NDItk_multigroup_ScatteringMatrix.py )

add_python_test( dosimetry.Metadata                       dosimetry/Test_NDItk_dosimetry_Metadata.py )

add_python_test( MultigroupTable   Test_NDItk_MultigroupTable.py )
add_python_test( DepletionTable    Test_NDItk_DepletionTable.py )
add_python_test( DosimetryTable    Test_NDItk_DosimetryTable.py )

add_python_test( MultigroupLibrary Test_NDItk_MultigroupLibrary.py )
add_python_test( DepletionLibrary  Test_NDItk_DepletionLibrary.py )
