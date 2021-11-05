option(BUILD_TESTS "Build tests of project" ON)

if (BUILD_TESTS)
  include(FetchContent)
  FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
  )
  FetchContent_MakeAvailable(googletest)

  enable_testing()

  # collect all cpp files
  file(GLOB_RECURSE MY_TESTS
      "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
      # header don't need to be included but this might be necessary for some IDEs
      "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h")

  # create make target
  add_executable(Tests ${MY_TESTS})

  target_link_libraries(Tests gtest_main)

  include(GoogleTest)
  gtest_discover_tests(Tests)
endif (BUILD_TESTS)