cmake_minimum_required(VERSION 3.10)
project(tp2 VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_gl_LIBRARY: ${OPENGL_gl_LIBRARY}")
find_package(GLUT REQUIRED)

add_executable(robot robot.c)
target_include_directories(robot PUBLIC ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
target_link_libraries(robot PUBLIC ${OPENGL_opengl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES})
#target_link_libraries(helloteapot OpenGL::OpenGL OpenGL::GLU GLUT::GLUT)

add_executable(subdivision subdivision.c)
target_include_directories(subdivision PUBLIC ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
target_link_libraries(subdivision PUBLIC ${OPENGL_opengl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES})
#target_link_libraries(moreteapots OpenGL::OpenGL OpenGL::GLU GLUT::GLUT)