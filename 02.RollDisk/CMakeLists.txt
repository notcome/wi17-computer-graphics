add_executable(
  02-RollDisk
  RollDisk.cpp)

target_link_libraries(
  02-RollDisk
  ${MACOS_OPENGL_LIB}
  ${MACOS_GLUT_LIB}
  GLUTWrapper)
