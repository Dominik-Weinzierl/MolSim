set(LIBRARY_NAME Sim)

# Collect all cpp files
file(GLOB_RECURSE SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    # Header don't need to be included but this might be necessary for some IDEs
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Remove main
list(REMOVE_ITEM SRC "main/Main.h")
list(REMOVE_ITEM SRC "main/Main.cpp")

# Build the module library
add_library(${LIBRARY_NAME} ${SRC})
add_library(lib::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_include_directories(${LIBRARY_NAME} SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/libs/libxsd)

# Require C++20
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_20)

set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Create make target
add_executable(MolSim ${CMAKE_CURRENT_SOURCE_DIR}/main/Main.cpp)
target_link_libraries(MolSim PUBLIC xerces-c PRIVATE lib::Sim)

# Activate all compiler warnings
target_compile_options(MolSim PRIVATE -W -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wpedantic -Wconversion -Werror -Wdouble-promotion)
target_compile_options(${LIBRARY_NAME} PRIVATE -W -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wpedantic -Wconversion -Werror -Wdouble-promotion)

# Clean additional output files as part of 'make clean'
set_property(
    TARGET MolSim
    APPEND
    PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/output
)
