/* -------------------------------------------------------------------------- *
 * GLUT Wrapper :: Common.h
 *
 * This header file import required GLUT files for different platforms.
 *
 * Author: Minsheng Liu.
 */

#ifndef Common_h
#define Common_h

#ifdef _WIN32
    #include <GL/glut.h>
#elif __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#endif

#endif
