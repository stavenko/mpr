include_directories(${MPR_INCLUDES})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIR})
add_executable(Example1 example1.cpp)
message(INFO, ${Boost_LIBRARIES})
set(all_libs
    ${OPENGL_LIBRARY}
    glfw
    ${GLFW_LIBRARIES}
    ${Boost_LIBRARIES}
    )
target_link_libraries(Example1 MPR)
target_link_libraries(Example1 ${all_libs})

