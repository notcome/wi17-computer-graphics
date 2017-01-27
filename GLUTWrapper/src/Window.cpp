/* -------------------------------------------------------------------------- *
 * GLUT Wrapper :: Window.cpp
 *
 * This file implements GLUT :: Window
 *
 * Author: Minsheng Liu, Sam Buss.
 */

#include "GLUT/Common.h"
#include "GLUT/Window.h"

using namespace GLUT;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

Window *GLUT::globalWindow = nullptr;

void Window::onKeyPress(unsigned char key, int x, int y) {}
void Window::onSpecialKey(int, int, int) {}
void Window::draw() {}

void callOnKeyPress(unsigned char key, int x, int y) {
    globalWindow->onKeyPress(key, x, y);
}

void callOnSpecialKey(int key, int x, int y) {
    globalWindow->onSpecialKey(key, x, y);
}
void callDraw() {
    globalWindow->draw();
}

void Window::postRedisplay() {
    glutPostRedisplay();
}

void Window::flushAndSwapBuffers() {
    glFlush();
    glutSwapBuffers();
}

void Window::onResizeWindow(int width, int height) {
    if (height == 0)
        height = 1;
    if (width == 0)
        width = 1;
    
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    auto aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    gluPerspective(globalWindow->viewAngleY,
                   aspectRatio,
                   globalWindow->nearZ,
                   globalWindow->farZ);
    glMatrixMode(GL_MODELVIEW);
}

void callOnResizeWindow(int width, int height) {
    globalWindow->onResizeWindow(width, height);
}

void Window::setCullFace(bool enableCullFace) {
    if (enableCullFace == this->isCullFaceEnabled)
        return;
    this->isCullFaceEnabled = enableCullFace;
    if (enableCullFace)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
    this->postRedisplay();
}

void Window::switchCullFaceOption() {
    if (this->isCullFaceEnabled)
        this->setCullFace(false);
    else
        this->setCullFace(true);
}

void Window::setWireFrame(bool enableWireFrame) {
    if (enableWireFrame == this->isWireFrameEnabled)
        return;
    this->isWireFrameEnabled = enableWireFrame;
    if (enableWireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    this->postRedisplay();
}

void Window::switchWireFrameOption() {
    if (this->isWireFrameEnabled)
        this->setWireFrame(false);
    else
        this->setWireFrame(true);
}

Window::Window(int argc, char **argv, const char *title,
               int windowPositionX, int windowPositionY,
               int windowSizeWidth, int windowSizeHeight) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowPosition(windowPositionX, windowPositionY);
    glutInitWindowSize(windowSizeWidth, windowSizeHeight);
    glutCreateWindow(title);
    glutReshapeFunc(callOnResizeWindow);
    
    glShadeModel(GL_FLAT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    
    glutKeyboardFunc(&callOnKeyPress);
    glutSpecialFunc(&callOnSpecialKey);
    glutDisplayFunc(&callDraw);
}

void Window::runLoop() {
    glutMainLoop();
}

#pragma clang diagnostic pop
