
set(MPR_NAME mpr)
message(STATUS ${MPR_SOURCES})
message(STATUS ${MPR_INCLUDES})
file(GLOB MPR_SOURCE_FILES ${MPR_SOURCES}/*.cpp) 
include_directories(${MPR_INCLUDES})
add_library(MPR STATIC ${MPR_SOURCE_FILES} ${MPR_INCLUDES})
set_target_properties(MPR PROPERTIES OUTPUT_NAME "${MPR_NAME}")
# set_target_properties(MPR PROPERTIES LINKER_LANGUAGE CXX)
