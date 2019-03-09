cmake_minimum_required(VERSION 3.9)
project(net)

# Add all needed sources files
set(SOURCES
	SSLSocket.cpp
	TCPAcceptor.cpp
	TCPSocket.cpp
	testnet.cpp
  )
# Add executable
add_executable(${PROJECT_NAME}
	${SOURCES}
	)

# Add includes directories
target_include_directories(${PROJECT_NAME} PUBLIC
  ./src/server/net
	${CMAKE_SOURCE_DIR}/api
	${CMAKE_SOURCE_DIR}/src/server
	${ZIA_EXTERNAL_INCLUDE_DIRS}
	)

# Link the project with needed libraries
target_link_libraries(${PROJECT_NAME}
	${CONAN_LIBS}
	${ZIA_EXTERNAL_LIBS}
	-lstdc++fs
	-lssl
	-lcrypto
	-ldl
	)

# Compiler flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	# G++
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -g3)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	# MSVC
	target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W2 /c)
endif()
