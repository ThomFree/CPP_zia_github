cmake_minimum_required(VERSION 3.9)
project(zia)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BINARY_DIR build)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")
endif (UNIX)

include_directories("${PROJECT_SOURCE_DIR}/src/" "${PROJECT_SOURCE_DIR}")

if (WIN32)
    include_directories(${Boost_INCLUDE_DIRS})
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W2 /c)
endif (WIN32)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/MiniMediator.cpp
  src/MiniWebsite.cpp

  src/http/MapContainer.cpp

  src/net/TCPSocket.cpp

  mods/HelloModule.cpp
  mods/RequestParser.cpp
)

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${CONAN_LIBS})
