include(GoogleTest)
include(CTest)

# Collect all cpp files
file(GLOB_RECURSE MY_TESTS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    # header don't need to be included but this might be necessary for some IDEs
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Create make target
add_executable(Test ${MY_TESTS})

# Link libs
target_link_libraries(Test gtest_main lib::Sim spdlog::spdlog)

# Require C++20
target_compile_features(Test PUBLIC cxx_std_20)

# Activate all compiler warnings
target_compile_options(Test PUBLIC -W -Wall -Wextra -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wpedantic -Wconversion -Werror -Wdouble-promotion -Wshadow -Wno-reorder)

gtest_discover_tests(Test)