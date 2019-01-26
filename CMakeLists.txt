cmake_minimum_required(VERSION 3.10)
project(zia)

set(CMAKE_CXX_STANDARD 17)

if (UNIX)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")

  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
endif (UNIX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(zia
  src/main.cpp)
target_link_libraries(zia ${CONAN_LIBS})

add_executable(zia_test
  tests/demo.cpp)
target_link_libraries(zia_test ${CONAN_LIBS})