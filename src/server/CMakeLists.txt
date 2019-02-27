cmake_minimum_required(VERSION 3.9)
project(zia)

# Add all needed sources files
set(SOURCES
	main.cpp
	WebsiteManager.cpp

	utils/ParseArgs.cpp
	)

# Add executable
add_executable(${PROJECT_NAME}
	${SOURCES}
	)

# Add includes directories
target_include_directories(${PROJECT_NAME} PUBLIC
	${ZIA_EXTERNAL_INCLUDE_DIRS}
	)

# Link the project with needed libraries
target_link_libraries(${PROJECT_NAME}
	${CONAN_LIBS}
	${ZIA_EXTERNAL_LIBS}
	)

# Compiler flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	# G++
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	# MSVC
	target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W2 /c)
endif()