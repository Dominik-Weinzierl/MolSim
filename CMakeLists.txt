cmake_minimum_required(VERSION 3.11)

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

# -OFast for Release
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

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

option(BUILD_TESTS "Build tests of project" OFF)

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

# Add spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.x
)

FetchContent_GetProperties(spdlog)

if (NOT spdlog_POPULATED)
  FetchContent_Populate(spdlog)
  add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif ()

# log levels
option(WITH_SPD_LOG_OFF "Disable logger" ON)
option(WITH_SPD_LOG_TRACE "Log level: Trace" OFF)
option(WITH_SPD_LOG_DEBUG "Log level: Debug" OFF)
option(WITH_SPD_LOG_INFO "Log level: Info" OFF)
option(WITH_SPD_LOG_WARN "Log level: Warn" OFF)
option(WITH_SPD_LOG_ERROR "Log level: Error" OFF)
option(WITH_SPD_LOG_CRITICAL "Log level: Critical" OFF)

if (WITH_SPD_LOG_OFF)
  MESSAGE(STATUS "Disable logger")
  add_definitions(-DUSE_SPD_LOG_OFF)
elseif (WITH_SPD_LOG_TRACE)
  MESSAGE(STATUS "Log level: Trace")
  add_definitions(-DUSE_SPD_LOG_TRACE)
elseif (WITH_SPD_LOG_DEBUG)
  MESSAGE(STATUS "Log level: Debug")
  add_definitions(-DUSE_SPD_LOG_DEBUG)
elseif (WITH_SPD_LOG_INFO)
  MESSAGE(STATUS "Log level: Info")
  add_definitions(-DUSE_SPD_LOG_INFO)
elseif (WITH_SPD_LOG_WARN)
  MESSAGE(STATUS "Log level: Warn")
  add_definitions(-DUSE_SPD_LOG_WARN)
elseif (WITH_SPD_LOG_ERROR)
  MESSAGE(STATUS "Log level: Error")
  add_definitions(-DUSE_SPD_LOG_ERROR)
elseif (WITH_SPD_LOG_CRITICAL)
  MESSAGE(STATUS "Log level: Critical")
  add_definitions(-DUSE_SPD_LOG_CRITICAL)
endif ()

# Add src folder
add_subdirectory(src MolSim)
