/*
 * Tetrahedra.cpp
 * Base code for homework project #1, Math 155A, Fall 2017.
 *
 * Author: Sam Buss, sbuss@math.ucsd.edu.
 *
 * USAGE:   (Please keep these controls in your homework assignment.)
 *
 *    Press arrow keys to control view position.
 *			left and right keys rotate the viewpoint left and right
 *	  Up and down keys rotate viewpoint up and down (up to 80 degrees).
 *
 *    Press "R" key to make step size bigger (if moving too slowly)
 *    Press "r" key to make step size smaller (if moving too fast).
 *
 *	  Press ESCAPE to exit.
 *
 *  PLUS ADD ONE NEW CONTROL:
 *    
 *    Press "c" to toggle culling of backfaces.
 *  
 */

#include <math.h>		// For math routines (such as sqrt & trig).
#include <stdio.h>		// For I/O routines, such as fprintf();
#include <stdlib.h>	// For the "exit" function

#include "GLUT/Common.h"
#include "GLUT/Window.h"
#include "GLUT/Constants.h"
#include "GLUT/ModernGL.h"
using namespace GLUT;

GLfloat topY    =  2.0 / 3.0 * sqrtf(2);
GLfloat bottomY = -1.0 / 3.0 * sqrtf(2);

GLfloat vertexT[] = { 0.0f,    topY, 0.0f };
GLfloat vertexF[] = { 0.0f, bottomY, 1.0f };
GLfloat vertexR[] = { sqrtf(3) / 2.0f, bottomY, -0.5f };
GLfloat vertexL[] = {-sqrtf(3) / 2.0f, bottomY, -0.5f };

void drawRight3Simplex() {
    glShadeModel(GL_FLAT);
    DrawBlock(GL_TRIANGLE_FAN, [](){
        color(Color::green);
        vertex(vertexT);
        vertex(vertexF);
        vertex(vertexR);
        color(Color::red);
        vertex(vertexL);
        color(Color::blue);
        vertex(vertexF);
    });
    
    DrawBlock(GL_TRIANGLES, [](){
        color(Color::darkGray);
        vertex(vertexF);
        vertex(vertexL);
        vertex(vertexR);
    });
}

void drawLeft3Simplex() {
    glShadeModel(GL_SMOOTH);
    DrawBlock(GL_TRIANGLE_STRIP, [](){
        color(Color::white);
        vertex(vertexT);
        color(Color::green);
        vertex(vertexF);
        color(Color::red);
        vertex(vertexR);
        color(Color::blue);
        vertex(vertexL);
        color(Color::white);
        vertex(vertexT);
        color(Color::green);
        vertex(vertexF);
    });
}

using namespace GLUT;
class TwoShapesWindow: public Window {
    // The next global variable controls the animation's state and speed.
    float rotateAngle = 0.0f;		// Angle in degrees of rotation around y-axis
    float azimuth = 0.0;			// Rotated up or down by this amount
    
    float angleStepSize = 3.0f;		// Step three degrees at a time
    const float angleStepMax = 10.0f;
    const float angleStepMin = 0.1f;
    
public:
    virtual void onKeyPress(unsigned char key, int x, int y) {
        switch (key) {
            case 'w':
                this->switchWireFrameOption();
                break;
                
            case 'c':
                this->switchCullFaceOption();
                break;
                
            case 'R':
                angleStepSize *= 1.5;
                if (angleStepSize > angleStepMax)
                    angleStepSize = angleStepMax;
                break;
        
            case 'r':
                angleStepSize /= 1.5;
                if (angleStepSize > angleStepMin)
                    angleStepSize = angleStepMin;
                break;
                
            case 27:
                exit(1);
        }
    }
    
    virtual void onSpecialKey(int key, int x, int y) {
        switch ( key ) {
            case GLUT_KEY_UP:
                azimuth += angleStepSize;
                if (azimuth > 80.0f)
                    azimuth = 80.0f;
                break;
                
            case GLUT_KEY_DOWN:
                azimuth -= angleStepSize;
                if (azimuth < -80.0f)
                    azimuth = -80.0f;
                break;
                
            case GLUT_KEY_LEFT:
                rotateAngle += angleStepSize;
                if (rotateAngle > 180.0f)
                    rotateAngle -= 360.0f;
                break;
                
            case GLUT_KEY_RIGHT:
                rotateAngle -= angleStepSize;
                if (rotateAngle < -180.0f)
                    rotateAngle += 360.0f;
                break;
        }
        
        this->postRedisplay();
    }
    
    virtual void draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Rotate the image
        glMatrixMode( GL_MODELVIEW );			// Current matrix affects objects positions
        glLoadIdentity();						// Initialize to the identity
        glTranslatef( -0.5, 0.0, -25.0 );				// Translate  from origin (in front of viewer)
        glRotatef( rotateAngle, 0.0, 1.0, 0.0 );		// Rotate around y-axis
        glRotatef( azimuth, 1.0, 0.0, 0.0 );			// Set Azimuth angle
        
        glPushMatrix();
        glTranslatef( 1.5, 0.0, 0.0 );
        drawRight3Simplex();
        glPopMatrix();
        glTranslatef( -1.5, 0.0, 0.0 );
        drawLeft3Simplex();
        
        this->flushAndSwapBuffers();
    }
    
    TwoShapesWindow(int argc, char **argv, const char *title)
    : Window(argc, argv, title) {
        this->setCullFace(true);
    }
};

int main(int argc, char **argv) {
    globalWindow = new TwoShapesWindow(argc, argv, "TwoShapes");
    
    fprintf(stdout, "Use the four arrow keys to change the viewpoint (this rotates the objects).\n");
	fprintf(stdout, "Press \"w\" to toggle wireframe mode.\n");
	fprintf(stdout, "Press \"R\" or \"r\" to increase or decrease rate of movement (respectively).\n");
	
    globalWindow->runLoop();
    
    return 0;
}
