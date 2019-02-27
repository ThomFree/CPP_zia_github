cmake_minimum_required(VERSION 3.9)

####################
#       EFSW       #
####################

# Build library
set(VERBOSE OFF CACHE BOOL "Verbose mode for efsw buidling" FORCE)
set(STATIC_LIB ON CACHE BOOL "Build static library of efsw" FORCE)
set(BUILD_TEST_APP OFF CACHE BOOL "Build efsw tests" FORCE)
add_subdirectory(efsw)

# Set library-specific variables
set(efsw_LIBS
	${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_STATIC_LIBRARY_PREFIX}efsw${CMAKE_STATIC_LIBRARY_SUFFIX}
	CACHE INTERNAL ""
	)
set(efsw_INCLUDE_DIRS
	${CMAKE_CURRENT_SOURCE_DIR}/efsw/include
	${CMAKE_CURRENT_SOURCE_DIR}/efsw/src
	CACHE INTERNAL ""
	)

####################
# THIRDPARTY  VARS #
####################

# Set zia external libs variables
set(ZIA_EXTERNAL_LIBS
	${yaml-cpp_LIBS}
	${efsw_LIBS}
	CACHE INTERNAL ""
	)
set(ZIA_EXTERNAL_INCLUDE_DIRS
	${yaml-cpp_INCLUDE_DIRS}
	${efsw_INCLUDE_DIRS}
	CACHE INTERNAL ""
	)
