cmake_minimum_required(VERSION 3.14)
project(LidanDelaunay)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)

add_subdirectory(/Users/lidan/CLionProjects/LidanDelaunay/libigl/external/glad)
find_package(Eigen3)
find_package(glfw3)


find_package(LIBIGL REQUIRED QUIET)





include_directories(/usr/local/include )
include_directories(/Users/lidan/CLionProjects/LidanDelaunay/module)
include_directories(/Users/lidan/CLionProjects/LidanDelaunay/util)


link_directories(/usr/local/lib /usr/local/)
link_libraries(glfw3 GLEW  )


add_executable(LidanDelaunay main.cpp module/Delaunay.cpp module/edge.cpp module/QuadEdge.cpp test/testCCW.cpp util/Vec.h util/Vec.cpp)
target_link_libraries(LidanDelaunay glfw3 igl::core igl::opengl igl::opengl_glfw )