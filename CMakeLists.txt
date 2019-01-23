cmake_minimum_required(VERSION 3.9)
project(zia_async)
set(VERSION "1.0.0")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BINARY_DIR build)  #[[Overwriting intelliJ IDEA default path and cie.]]

if (UNIX)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread -std=c++17 -fPIC -g3")
endif (UNIX)

include_directories("${PROJECT_SOURCE_DIR}/async/")

if (WIN32)
    include_directories(${Boost_INCLUDE_DIRS})
endif (WIN32)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#[[AUTOMATIC TARGET ADDER]]

file(GLOB ASYNC_SRC "async/*.cpp")
file(GLOB ASYNC_INC "async/*.hpp")

add_executable(
  zia_async
  main.cpp
  ${ASYNC_SRC}
  ${ASYNC_INC}
)

target_link_libraries (zia_async ${CMAKE_THREAD_LIBS_INIT} ${CONAN_LIBS})

add_custom_command(TARGET zia_async
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:zia_async> ${CMAKE_HOME_DIRECTORY}/.
)
