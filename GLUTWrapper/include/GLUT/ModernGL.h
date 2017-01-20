/* -------------------------------------------------------------------------- *
 * GLUT Wrapper :: ModernGL.h
 *
 * This file declares several wrappers for OpenGL operations using modern C++.
 *
 * Author: Minsheng Liu.
 */

#ifndef ModernGL_h
#define ModernGL_h

#include <functional>
#include "Common.h"

namespace GLUT {
    inline void vertex(float x, float y, float z) {
        glVertex3f(x, y, z);
    }
    
    inline void vertex(const float *xyz) {
        glVertex3fv(xyz);
    }
    
    inline void color(const float *rgb) {
        glColor3fv(rgb);
    }
}

class DrawBlock {
public:
    DrawBlock(GLenum mode, std::function<void()> draw) {
        glBegin(mode);
        draw();
        glEnd();
    }
};

#endif
