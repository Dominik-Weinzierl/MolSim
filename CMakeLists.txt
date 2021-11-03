cmake_minimum_required(VERSION 3.10)

# define project name, version
project(PSEMolDyn_GroupA)

# prevent in-source builds
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  message(FATAL_ERROR "In-source builds are not allowed. Please create a separate build directory.")
endif()

# let ccmake and cmake-gui offer the default build type options
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel")

# set Release as the default build type if it is not yet set.
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

# collect all cpp files
file(GLOB_RECURSE MY_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    # header don't need to be included but this might be necessary for some IDEs
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

# create make target
add_executable(MolSim ${MY_SRC})

# set cxx standard. You may raise this if you want.
target_compile_features(MolSim PUBLIC cxx_std_20)

target_include_directories(MolSim SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/libxsd)
target_include_directories(MolSim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(MolSim PUBLIC xerces-c)

# activate all compiler warnings
target_compile_options(MolSim PRIVATE -W -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wpedantic -Wconversion -Werror -Wdouble-promotion)

# Clean additional output files as part of 'make clean'
set_property(
    TARGET MolSim
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/output
)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

include(doxygen)