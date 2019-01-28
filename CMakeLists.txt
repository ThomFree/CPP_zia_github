cmake_minimum_required(VERSION 3.9)
project(httpd)
set(VERSION "1.0.0")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BINARY_DIR build)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread -std=c++17 -fPIC -g3")
endif (UNIX)

include_directories("${PROJECT_SOURCE_DIR}/include/")

if (WIN32)
    include_directories(${Boost_INCLUDE_DIRS})
endif (WIN32)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB NET_SRC "sources/net/*.cpp")

add_executable(
  httpd
  sources/main.cpp
  ${NET_SRC}
)

target_link_libraries (httpd ${CMAKE_THREAD_LIBS_INIT} ${CONAN_LIBS})

add_custom_command(TARGET httpd
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:httpd> ${CMAKE_HOME_DIRECTORY}/.
)
