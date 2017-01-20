add_executable(
  01-Tetrahedra
  Tetrahedra.cpp)

target_link_libraries(
  01-Tetrahedra
  ${MACOS_OPENGL_LIB}
  ${MACOS_GLUT_LIB}
  GLUTWrapper)
