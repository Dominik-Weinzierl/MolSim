# make doc_doxygen optional if someone does not have / like doxygen

option(BUILD_DOCUMENTATION "Build documentation of project" OFF)

# check if Doxygen is installed
find_package(Doxygen)

if (BUILD_DOCUMENTATION)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxyfile)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        # note the option ALL which allows to build the docs together with the application
        add_custom_target(doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

        # option to remove documentation
        add_custom_target(clean_doxygen
                COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/doxys_documentation)
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif (BUILD_DOCUMENTATION)