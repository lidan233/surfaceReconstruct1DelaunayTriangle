cmake_minimum_required(VERSION 3.1)
project(module)

add_executable(module Delaunay.cpp edge.cpp )
target_link_libraries(${PROJECT_NAME}_bin igl::core igl::opengl igl::opengl_glfw igl::opengl_glfw_imgui tutorials)
