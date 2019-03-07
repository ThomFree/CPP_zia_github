cmake_minimum_required(VERSION 3.9)
project(mod_guiLogger)

# Add sources
add_library(${PROJECT_NAME} SHARED
	src/guiLoggerModule.cpp
	src/HandlerFilePath.cpp
	)

# Add includes directories
target_include_directories(${PROJECT_NAME} PUBLIC
	./src
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/api
	${ZIA_EXTERNAL_INCLUDE_DIRS}
	)

# Link the project with needed libraries
target_link_libraries(${PROJECT_NAME}
	-lstdc++fs
	)

# Compiler flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	# G++
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	# MSVC
	target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W2 /c)
endif()