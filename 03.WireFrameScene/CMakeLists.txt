add_executable(
  03-WireFrameScene
  WireFrameScene.cpp)

target_link_libraries(
  03-WireFrameScene
  ${MACOS_OPENGL_LIB}
  ${MACOS_GLUT_LIB}
  GLUTWrapper)
