cmake_minimum_required(VERSION 3.9)
project(zia)

set(CMAKE_CXX_STANDARD 17)

# Compile needed libraries
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add all needed sources files
add_executable(${PROJECT_NAME}
  src/main.cpp)

# Compiler flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  # G++
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  # MSVC
  target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W2 /c)
endif()

# Include file directories
include_directories(sources)

# Find and link the project with needed libraries
find_package(Boost 1.67 COMPONENTS system REQUIRED)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

# Test executable
add_executable(zia_test
  tests/demo.cpp)
target_link_libraries(zia_test ${CONAN_LIBS})