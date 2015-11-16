set(PROJECT_TEST_NAME MPR_test)  
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

include(ExternalProject)

include_directories(${MPR_INCLUDES})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

message(INFO ${Boost_INCLUDE_DIRS})

file(GLOB TEST_SOURCES ${MPR_SOURCE_DIR}/tests/*.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SOURCES})
target_link_libraries(${PROJECT_TEST_NAME} MPR)

set(DEPS
    googletest
    pthread)

add_dependencies(${PROJECT_TEST_NAME} ${DEPS})

if(MSVC)
    set(Suffix ".lib")
else()
    set(Suffix ".a")
    set(Pthread "-pthread")
endif()

target_link_libraries(${PROJECT_TEST_NAME}
    debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
)

target_link_libraries(${PROJECT_TEST_NAME}
    debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${Suffix}
    optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${Suffix}
    ${Pthread}
)      
