/* -------------------------------------------------------------------------- *
 * GLUT Wrapper :: Window.h
 *
 * This file wraps window-related GLUT operations.
 *
 * Author: Minsheng Liu, Sam Buss.
 */

#ifndef Window_h
#define Window_h

#include "Common.h"

namespace GLUT {
    class Window {
    private:
        // By default, GL_CULL is disabled.
        bool isCullFaceEnabled  = false;
        bool isWireFrameEnabled = false;
        
    protected:
        double viewAngleY = 15.0;
        double nearZ      = 15.0;
        double farZ       = 35.0;
        
        void setCullFace(bool);
        void setWireFrame(bool);
        
    public:
        virtual void onKeyPress(unsigned char, int, int);
        virtual void onSpecialKey(int, int, int);
        virtual void onResizeWindow(int width, int height);
        virtual void draw();
        
        
        void postRedisplay();
        void flushAndSwapBuffers();
        
        void switchCullFaceOption();
        void switchWireFrameOption();
        
        Window(int argc, char **argv, const char *title,
               int windowPositionX = 0, int windowPositionY = 0,
               int windowSizeWidth = 360, int windowSizeHeight = 360);
        
        void runLoop();
    };
    
    extern Window *globalWindow;
}

#endif
