cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

<<<<<<< HEAD
include_directories("${PROJECT_SOURCE_DIR}/src/")

if (WIN32)
    include_directories(${Boost_INCLUDE_DIRS})
endif (WIN32)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB NET_SRC "src/*.cpp")

add_executable(
  httpd
  src/main.cpp
  ${NET_SRC}
)

target_link_libraries (httpd ${CMAKE_THREAD_LIBS_INIT} ${CONAN_LIBS})

add_custom_command(TARGET httpd
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:httpd> ${CMAKE_HOME_DIRECTORY}/.
)
=======
# Compile needed libraries
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
add_subdirectory(lib)
add_subdirectory(src/server)
add_subdirectory(src/tests)
>>>>>>> b529686384a61b7f65c3374cb6873cc2454b4132
