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

inline float degreeToRadian (const float degree) {
    return degree / 180.0f * PI;
}

class DrawBlock {
public:
    DrawBlock(GLenum mode, std::function<void()> draw) {
        glBegin(mode);
        draw();
        glEnd();
    }
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
// This function draws the unit sphere with its south pole at (0, 0, 0).
inline void drawSolidSphereAtNorthPole(int meshCount) {
    glTranslatef(0.0, -1.0, 0.0);
    glutSolidSphere(1.0, meshCount, meshCount);
}

inline void drawSolidSphereAtSouthPole(int meshCount) {
    glTranslatef(0.0, 1.0, 0.0);
    glutSolidSphere(1.0, meshCount, meshCount);
}
#pragma clang diagnostic pop

inline void withMode(GLenum mode, std::function<void()> draw) {
    glBegin(mode);
    draw();
    glEnd();
}

inline void withScale(float x, float y, float z, std::function<void()> draw) {
    glPushMatrix();
    glScalef(x, y, z);
    draw();
    glPopMatrix();
}

NameSpaceEnd

#undef NameSpaceStart
#undef NameSpaceEnd

#endif
