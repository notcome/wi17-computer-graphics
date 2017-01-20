cmake_minimum_required(VERSION 3.1.0)

project(Math155A)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
  find_library(MACOS_OPENGL_LIB OpenGL)
  find_library(MACOS_GLUT_LIB GLUT)
else()
  set(MACOS_OPENGL_LIB "")
  set(MACOS_GLUT_LIB "")
endif()

include_directories("GLUTWrapper/include")

add_subdirectory(GLUTWrapper)
add_subdirectory(01.Tetrahedra)
