CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/cmake-modules")
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Only do Release and Debug" FORCE )
MARK_AS_ADVANCED(CMAKE_CONFIGURATION_TYPES)

PROJECT(KDLCollada)      #must be after setting cmake_configuration_types

ADD_DEFINITIONS(-DCOLLADA_MODELS_PATH="${CMAKE_HOME_DIRECTORY}/examples/")

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

# search for libxml2
#FIND_PACKAGE(LibXml2)
#IF (LIBXML2_FOUND)
#  MESSAGE(STATUS "SUCCESSFUL: LibXml2 found")
#ELSE (LIBXML2_FOUND) #if xml2 not found building its local copy from ./Externals
#  MESSAGE("ERROR: LibXml2 not found")
#ENDIF (LIBXML2_FOUND)

#search for pcre
FIND_PACKAGE(PCRE)
IF (PCRE_FOUND)
	MESSAGE(STATUS "SUCCESSFUL: PCRE found")
ELSE (PCRE_FOUND) #if pcre not found building its local copy from ./Externals
	MESSAGE("ERROR: PCRE not found")
ENDIF (PCRE_FOUND)

#Create OpenCOLLADAFind.cmake instead
SET(OPENCOLLADA_DIR /usr/local/opencollada CACHE FILEPATH "OpenCollada Directory")
SET(OPENCOLLADA_LIB_DIR ${OPENCOLLADA_DIR}/lib)
SET(OPENCOLLADA_LIBRARIES 
	OpenCOLLADASaxFrameworkLoader	
	GeneratedSaxParser	
	OpenCOLLADAFramework	
	OpenCOLLADABaseUtils
	OpenCOLLADAStreamWriter
	MathMLSolver
        ${PCRE_LIBRARIES}
	${LIBXML2_LIBRARIES}
	UTF)
SET(OPENCOLLADA_INCLUDE_DIR
	${OPENCOLLADA_DIR}/COLLADAStreamWriter/include
	${OPENCOLLADA_DIR}/COLLADABaseUtils/include
	${OPENCOLLADA_DIR}/COLLADAFramework/include
	${OPENCOLLADA_DIR}/COLLADASaxFrameworkLoader/include
	${OPENCOLLADA_DIR}/GeneratedSaxParser/include
)

FIND_PACKAGE(PKGConfig)
FIND_PACKAGE(KDL)
IF (KDL_FOUND)
	MESSAGE(STATUS "SUCCESSFUL: KDL found")
ELSE (KDL_FOUND) 
	MESSAGE(STATUS "ERROR: KDL not found")
ENDIF (KDL_FOUND)

#include all CMakeList.txt files within this package
#each generates one library or application	
ADD_SUBDIRECTORY(src)     # sets ${libBRICS_include_dirs} in this scope

ADD_SUBDIRECTORY(examples)     # sets ${libBRICS_include_dirs} in this scope

