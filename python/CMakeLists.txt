if( NDItk.python )

    pybind11_add_module( NDItk.python
        ${CMAKE_CURRENT_SOURCE_DIR}/src/NDItk.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/NDItk.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/MultigroupTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DepletionTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DosimetryTable.python.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/MultigroupLibrary.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DepletionLibrary.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DosimetryLibrary.python.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/thermonuclear.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/thermonuclear/Temperatures.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/thermonuclear/InterpolationRegions.python.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/depletion.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/depletion/Multiplicities.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/depletion/Product.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/depletion/Target.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/depletion/IncidentParticle.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/depletion/Metadata.python.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/dosimetry.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dosimetry/Metadata.python.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/ReactionMultiplicityType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/Multiplicities.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/ReactionMultiplicities.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/FissionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/Metadata.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/CrossSection.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/DownScatteringLegendreMoment.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/DownScatteringMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/FluxWeights.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/EnergyGroupStructure.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/ReactionCrossSections.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/TotalCrossSection.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/AverageFissionEnergyRelease.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/FissionNeutronMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/FissionNeutronProduction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/FissionNeutronSpectrumVector.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/FissionNeutronSpectrumMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/Velocities.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/HeatingNumbers.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/Kerma.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/OutgoingParticleTypes.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/OutgoingParticleTransportData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/LegendreMoment.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/multigroup/ScatteringMatrix.python.cpp
    )

    target_link_libraries(NDItk.python PRIVATE njoy::NDItk)
    add_dependencies( NDItk.python njoy::tools.python)
    target_include_directories( NDItk.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )
    set_target_properties( NDItk.python PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties( NDItk.python PROPERTIES OUTPUT_NAME NDItk )
    set_target_properties( NDItk.python PROPERTIES LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR})
    set_target_properties( NDItk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
    set_target_properties( NDItk.python PROPERTIES POSITION_INDEPENDENT_CODE ON )
    # add all .so's that are installed with mcatk to the installed library rpath
    set_target_properties( NDItk.python PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
    # add all .so's that are linked to at build time to the installed library rpath
    set_target_properties( NDItk.python PROPERTIES INSTALL_RPATH_USE_LINK_PATH ON)

    set(PyVersion "${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}")
    set( py_library_install_prefix ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/python${PyVersion}/site-packages )

    if (NDItk.installation)
        install( TARGETS NDItk.python LIBRARY DESTINATION ${py_library_install_prefix} )
    endif()

    message( STATUS "Building NDItk's python API" )

    # Append potential installation and build paths for tools python module
    set(NDItk_PYTHONPATH "$<TARGET_FILE_DIR:NDItk.python>")
    set(tools_PYTHONPATH "$<TARGET_FILE_DIR:njoy::tools.python>")

    # Windows and unix have different delimiter for paths
    if (WIN32)
	    set(PATH_DELIM "\;")
    else()
	    set(PATH_DELIM ":")
    endif()

    if (tools_DIR)
	    set(tools_PYTHONPATH_PARTS ${tools_PYTHONPATH} "${tools_DIR}/../../../${CMAKE_INSTALL_LIBDIR}" )
	    string( JOIN "${PATH_DELIM}" tools_PYTHONPATH ${tools_PYTHONPATH_PARTS})
    endif()

    if( NDItk.tests )
        include( ${PROJECT_SOURCE_DIR}/cmake/unit_testing_python.cmake )
    endif()

    # generate python stubs if possible
    find_program(pybind11stubgen_exe pybind11-stubgen)

    set(PYTHONPATH_PARTS ${tools_PYTHONPATH} ${NDItk_PYTHONPATH} $ENV{PYTHONPATH})
    string( JOIN "${PATH_DELIM}" PYTHONPATH_VALUE ${PYTHONPATH_PARTS})

    set(stubdir "${CMAKE_CURRENT_SOURCE_DIR}/stubs/NDItk")
    if (pybind11stubgen_exe)
        # the following command executes the pybind11-stubgen executable found via find_program
        # and puts its terminal output into pybind11-stubgen.log in the build tree.
        # The stubs get generated in the source tree so users can determine what changes if any were made to the stubs.
        # The stubs are then copied into the build tree so developers get the stubs when using the build tree's python bindings.
        # If the stubs fail to generate then this command exits gracefully and allows the build to continue.
        add_custom_command(
            TARGET NDItk.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH_VALUE}" ${pybind11stubgen_exe} NDItk -o ${CMAKE_CURRENT_SOURCE_DIR}/stubs &> ${CMAKE_CURRENT_BINARY_DIR}/pybind11-stubgen.log || true
            COMMAND ${CMAKE_COMMAND} -E rename ${stubdir}/__init__.pyi ${stubdir}/NDItk.pyi &> /dev/null || true
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Building NDItk's python stub files via pybind11-stubgen. See pybind11-stubgen.log for details."
            VERBATIM
        )

    else()
        # copy stub files to build tree even if pybind11stubgen isn't available.
        add_custom_command(
            TARGET NDItk.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
        )
    endif()

    # install stubs so the installed binaries play nice with IDEs
    if (NDItk.installation)
        install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/stubs/NDItk/ DESTINATION ${py_library_install_prefix} )
    endif()

endif() # end NDItk.python check
