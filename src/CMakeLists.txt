
set(MPR_NAME mpr)
message(STATUS ${MPR_SOURCES})
message(STATUS ${MPR_INCLUDES})
file(GLOB MPR_SOURCE_FILES ${MPR_SOURCES}/*.cpp) 
include_directories(${MPR_INCLUDES})
include_directories(${Boost_INCLUDE_DIRS})
add_library(MPR STATIC ${MPR_SOURCE_FILES} ${MPR_INCLUDES})
set_target_properties(MPR PROPERTIES OUTPUT_NAME "${MPR_NAME}")

FIND_LIBRARY( GLEW_STATIC
		NAMES libGLEW.a GLEW
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		${GLEW_ROOT_DIR}/lib
		DOC "The GLEW library")

message (INFO
    ${GLEW_STATIC})
target_link_libraries(MPR ${GLEW_STATIC})
