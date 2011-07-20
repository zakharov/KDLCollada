CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/cmake-modules")
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Only do Release and Debug" FORCE )
MARK_AS_ADVANCED(CMAKE_CONFIGURATION_TYPES)

PROJECT(KDLCollada)      #must be after setting cmake_configuration_types

#defines where static libraries are stored
SET(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib)

#defines where the executables are stored
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)
    
#defines where dynamic libraries (plugins) are stored
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
    
IF(NOT WIN32)
  set(CMAKE_CXX_FLAGS "-Wall")
ENDIF(NOT WIN32)

#defines the core sources of BRICS_MM
SET(KDLCOLLADA_CORE_SRC ${CMAKE_HOME_DIRECTORY}/src)

# find required and optional dependencies via Find<name>.cmake modules

#SET(Boost_USE_STATIC_LIBS ON)
#SET(Boost_ADDITIONAL_VERSIONS "1.39" "1.39.0" "1.40" "1.40.0" "1.41" "1.41.0"  "1.42" "1.42.0")
#FIND_PACKAGE(Boost COMPONENTS thread)
#IF (Boost_FOUND)
#	MESSAGE(STATUS "SUCCESSFUL: Boost found")
#ELSE (Boost_FOUND) 
#	MESSAGE(STATUS "ERROR: Boost not found")
#ENDIF (Boost_FOUND)
FIND_PACKAGE(PkgConfig)
FIND_PACKAGE(KDL)
IF (KDL_FOUND)
	MESSAGE(STATUS "SUCCESSFUL: KDL found")
ELSE (KDL_FOUND) 
	MESSAGE(STATUS "ERROR: KDL not found")
ENDIF (KDL_FOUND)

#include all CMakeList.txt files within this package
#each generates one library or application	
ADD_SUBDIRECTORY(src)     # sets ${libBRICS_include_dirs} in this scope

#ADD_SUBDIRECTORY(examples)     # sets ${libBRICS_include_dirs} in this scope

