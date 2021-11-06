# Works with 3.11 and tested through 3.21
cmake_minimum_required(VERSION 3.11...3.21)

# Set cxx standard.
set(CMAKE_CXX_STANDARD 20)

# Define project name, version
project(PSEMolDyn_GroupA
    VERSION 0.1
    DESCRIPTION "Molecular simulation"
    LANGUAGES CXX)

# Prevent in-source builds
if ("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  message(FATAL_ERROR "In-source builds are not allowed. Please create a separate build directory.")
endif ()

# Let ccmake and cmake-gui offer the default build type options
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel")

# Set Release as the default build type if it is not yet set.
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

# Let's nicely support folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add our cmake modules under cmake/modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

# Include doxygen
include(doxygen)

# Include FetchContent
include(FetchContent)

option(BUILD_TESTS "Build tests of project" ON)

if (BUILD_TESTS)
  # Setup googletest
  FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
  )
  FetchContent_MakeAvailable(googletest)

  # Enable testing
  enable_testing()

  # Add test folder
  add_subdirectory(tests Test)
endif (BUILD_TESTS)

# Add scr folder
add_subdirectory(src MolSim)
