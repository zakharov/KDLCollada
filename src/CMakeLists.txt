PROJECT(libKDLCollada)

SET(libKDLCollada_include_dirs 
	${CMAKE_HOME_DIRECTORY}/include
	${KDL_INCLUDE_PATH}
	${OPENCOLLADA_INCLUDE_DIR}
)

SET(libKDLCollada_libs
	${OPENCOLLADA_LIBRARIES}
	${KDL_LIBRARIES} 
)

file(GLOB_RECURSE libKDLCollada_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

INCLUDE_DIRECTORIES(${libKDLCollada_include_dirs})

LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH} ${OPENCOLLADA_LIB_DIR})

ADD_LIBRARY(kdl-collada ${libKDLCollada_FILES} ${libKDLCollada_EXTERNAL_FILES})

TARGET_LINK_LIBRARIES(kdl-collada ${libKDLCollada_libs}
)
