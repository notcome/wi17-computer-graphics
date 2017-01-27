/* -------------------------------------------------------------------------- *
 * GLUT Wrapper :: ModernGL.h
 *
 * This file declares several wrappers for OpenGL operations using modern C++.
 *
 * Author: Minsheng Liu.
 */

#ifndef ModernGL_h
#define ModernGL_h

// Bypassing IDE's default indentation.

#define NameSpaceStart namespace GLUT {
#define NameSpaceEnd   }

#include <functional>
#include "Common.h"
#include "Constants.h"

//namespace GLUT {

NameSpaceStart

inline void vertex (float x, float y, float z) {
    glVertex3f(x, y, z);
}

inline void vertex (const float *xyz) {
    glVertex3fv(xyz);
}

inline void color (const float *rgb) {
    glColor3fv(rgb);
}

inline void color (float red, float green, float blue) {
    glColor3f(red, green, blue);
}

inline float radianToDegree (const float radian) {
    return radian * 180.0f / PI;
}

class DrawBlock {
public:
    DrawBlock(GLenum mode, std::function<void()> draw) {
        glBegin(mode);
        draw();
        glEnd();
    }
};

NameSpaceEnd

#undef NameSpaceStart
#undef NameSpaceEnd

#endif
