#######################################################################
# Setup
#######################################################################

enable_testing()

function( add_python_test name source )

  set( test_name "NDItk.python.${name}.test" )
  add_test( NAME ${test_name}
            COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/${source}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
  set_tests_properties( ${test_name}
                        PROPERTIES ENVIRONMENT
                        PYTHONPATH=${tools_PYTHONPATH}:${NDItk_PYTHONPATH}:$ENV{PYTHONPATH})

endfunction()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding NDItk Python unit testing" )

add_python_test( depletion.Multiplicities         depletion/Test_NDItk_depletion_Multiplicities.py )
add_python_test( depletion.ReactionMultiplicities depletion/Test_NDItk_depletion_ReactionMultiplicities.py )

add_python_test( multigroup.Metadata                      multigroup/Test_NDItk_multigroup_Metadata.py )
add_python_test( multigroup.CrossSection                  multigroup/Test_NDItk_multigroup_CrossSection.py )
add_python_test( multigroup.FluxWeights                   multigroup/Test_NDItk_multigroup_FluxWeights.py )
add_python_test( multigroup.EnergyGroupStructure          multigroup/Test_NDItk_multigroup_EnergyGroupStructure.py )
add_python_test( multigroup.ReactionCrossSections         multigroup/Test_NDItk_multigroup_ReactionCrossSections.py )
add_python_test( multigroup.TotalCrossSection             multigroup/Test_NDItk_multigroup_TotalCrossSection.py )
add_python_test( multigroup.AverageFissionEnergyRelease   multigroup/Test_NDItk_multigroup_AverageFissionEnergyRelease.py )
add_python_test( multigroup.Velocities                    multigroup/Test_NDItk_multigroup_Velocities.py )
add_python_test( multigroup.HeatingNumbers                multigroup/Test_NDItk_multigroup_HeatingNumbers.py )
add_python_test( multigroup.Kerma                         multigroup/Test_NDItk_multigroup_Kerma.py )
add_python_test( multigroup.OutgoingParticleTypes         multigroup/Test_NDItk_multigroup_OutgoingParticleTypes.py )
add_python_test( multigroup.OutgoingParticleTransportData multigroup/Test_NDItk_multigroup_OutgoingParticleTransportData.py )
add_python_test( multigroup.LegendreMoment                multigroup/Test_NDItk_multigroup_LegendreMoment.py )
add_python_test( multigroup.ScatteringMatrix              multigroup/Test_NDItk_multigroup_ScatteringMatrix.py )

add_python_test( MultigroupTable   Test_NDItk_MultigroupTable.py )
