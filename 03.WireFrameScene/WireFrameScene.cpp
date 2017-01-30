/* -------------------------------------------------------------------------- *
 * 02-RollDisk :: WireFrameScene.cpp
 *
 * Project 3, Math 155A, Fall 2017.
 *
 * Author: Minsheng Liu.
 * Based on the code provided by professor Sam Buss, which is in "Assets/" of
 *   the folder where this files is located.
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

#include "GLUT/Common.h"
#include "GLUT/Window.h"
#include "GLUT/ModernGL.h"

using namespace std;
using namespace GLUT;

class WireFrameSceneWindow: public Window {
private:
    const int minMeshCount = 3;
    int meshCount = 6;
    
    float angleStep = 3.0f;
    const float maxAngleStep = 10.0f;
    const float minAngleStep = 0.1f;
    
    float time = 0.0f;
    const float timeStep = 0.005f;
    
    void drawGeometry();
    void drawRotatingSurface();
    
    // Rotation of x,y-plane.
    float azimuth;
    // Rotation around y axis.
    float rotation;
    
    bool isAnimated = true;
    
public:
    WireFrameSceneWindow(int argc, char **argv)
    : Window(argc, argv, "Wire Frame Scene Demo", 10, 60, 480, 360) {
        this->setWireFrame(true);
        this->setCullFace(true);
        
        this->viewAngleY = 12.0;
        this->nearZ = 20.0;
        this->farZ = 50.0;
    }
    
    virtual void onKeyPress(unsigned char key, int x, int y) {
        if (key == 'c')
            return this->switchCullFaceOption();
        if (key == 'w')
            return this->switchWireFrameOption();
        if (key == 'a')
            this->isAnimated = ! this->isAnimated;
        if (key == 27)
            exit(1);
        
        if (key == 'r')
            this->angleStep = max<float>(angleStep / 1.5, this->minAngleStep);
        else if (key == 'R')
            this->angleStep = min<float>(angleStep * 1.5, this->maxAngleStep);
        
        if (key == 'm' || key == 'M') {
            if (key == 'm')
                this->meshCount = max(meshCount - 1, this->minMeshCount);
            else
                this->meshCount ++;
            this->postRedisplay();
        }
    }
    
    virtual void onSpecialKey(int key, int x, int y) {
        if (key == GLUT_KEY_UP)
            this->azimuth = min(this->azimuth + this->angleStep, 80.0f);
        else if (key == GLUT_KEY_DOWN)
            this->azimuth = max(this->azimuth - this->angleStep, -80.0f);
        else if (key == GLUT_KEY_LEFT) {
            this->rotation += this->angleStep;
            if (this->rotation > 180.0f)
                this->rotation -= 360.0f;
        } else if (key == GLUT_KEY_RIGHT) {
            this->rotation -= this->angleStep;
            if (this->rotation < -180.0f)
                this->rotation += 360.0f;
        } else
            return;
        
        this->postRedisplay();
    }
    
    virtual void draw() {
        if (this->isAnimated) {
            this->time += this->timeStep;
            
            if (this->time > 2.0 * PI)
                time -= 2.0 * PI;
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0, -2.5, -35.0);
        glRotatef(this->azimuth, 1.0, 0.0, 0.0);
        glRotatef(this->rotation, 0.0, 1.0, 0.0);
        
        
        DrawBlock(GL_QUADS, []() {
            color(Color::white);
            vertex(-4.0, 0.0,  4.0);
            vertex( 4.0, 0.0,  4.0);
            vertex( 4.0, 0.0, -4.0);
            vertex(-4.0, 0.0, -4.0);
        });
        
        this->drawRotatingSurface();
        this->drawGeometry();
        
        this->flushAndSwapBuffers();
        this->postRedisplay();
    }
};


int main(int argc, char **argv) {
    globalWindow = new WireFrameSceneWindow(argc, argv);
    
    printf("Arrow keys control viewpoint.n");
    printf("Press \"w\" to toggle wireframe mode.\n");
    printf("Press \"c\" to toggle culling of back faces.\n");
    printf("Press \"M\" or \"m\" to increase or decrease resolution of mushroom cap.\n");
    printf("Press \"R\" or \"r\" to increase or decrease rate of movement (respectively).\n");
    printf("Press \"a\" to toggle animation on and off.\n");
    
    globalWindow->runLoop();
    return 0;
}

void WireFrameSceneWindow::drawGeometry() {
    // You will need to rewrite this routine for Project #3.
    // In the supplied executable, I draw a "S" based on elongated
    //	ellipsoids.  These were formed using glutSolidSphere()'s,
    //  reoriented and scaled to turn the spheres into ellipsoids.
    // You should do something comparable -- about as complicated as
    //  my example.   You are encouraged to include a larger variety
    //  of shapes than just ellipses, and to make the end result
    //  artistically interesting in some aspect.
    // Your scene must include some animation.
    
    glColor3f( 0.0, 1.0, 0.5 );		// The color of the "S" shape.
    glPushMatrix();
    glTranslatef( -2.0, 0.0, -2.0);	// Move leftward and away from the viewer a little
    glPushMatrix();
    glTranslatef( -0.5, 0.5, 0.0 );
    glRotatef( -45.0, 0.0, 0.0, 1.0 );
    glRotatef( 90.0, 0.0, 1.0, 0.0 );
    glScalef( 0.20f, 0.20f, 0.66f );
    glutSolidSphere( 1.0, this->meshCount, this->meshCount );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 0.5, 0.5, 0.0 );
    glRotatef( 45.0, 0.0, 0.0, 1.0 );
    glRotatef( 90.0, 0.0, 1.0, 0.0 );
    glScalef( 0.20f, 0.20f, 0.66f );
    glutSolidSphere( 1.0, this->meshCount, this->meshCount );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 0.0, 2.0, 0.0 );
    glRotatef( -45.0, 0.0, 0.0, 1.0 );
    glRotatef( 90.0, 0.0, 1.0, 0.0 );
    glScalef( 0.20f, 0.2f, 1.33f );
    glutSolidSphere ( 1.0, this->meshCount, this->meshCount );
    glPopMatrix();
    glPushMatrix();
    glTranslatef( -0.5, 3.5, 0.0 );
    glRotatef( 45.0, 0.0, 0.0, 1.0 );
    glRotatef( 90.0, 0.0, 1.0, 0.0 );
    glScalef( 0.20f, 0.20f, 0.66f );
    glutSolidSphere( 1.0, this->meshCount, this->meshCount );
    glPopMatrix();
    // Now do the animated ellipsoid
    glPushMatrix();
    
    float a = -sinf(time);
    a = (a<0.0f)? 0.0f : a;
    float thetaMin = 45.0;
    float bloatMin = 1.0;
    float lenMin = 1.0;
    float thetaMax = 0.0;
    float bloatMax = 1.2f;
    float lenMax = 1.2f;
    float len = (1.0f-a)*lenMin + a*lenMax;
    float bloat = (1.0f-a)*bloatMin + a*bloatMax;
    float theta = (1.0f-a)*thetaMin + a*thetaMax;
    float thetaRadians = theta*3.1415926535f/180.0f;
    glTranslatef( len*cosf(thetaRadians)/sqrtf(2.0), 4.0f-len*sinf(thetaRadians)/sqrtf(2.0), 0.0 );
    glRotatef( -theta, 0.0, 0.0, 1.0 );
    glRotatef( 90.0, 0.0, 1.0, 0.0 );
    glScalef( 0.20f*len*bloat, 0.20f*len*bloat, 0.66f*len );
    glutSolidSphere( 1.0, this->meshCount, this->meshCount );
    glPopMatrix();
    
    glPopMatrix();
}

void WireFrameSceneWindow::drawRotatingSurface() {
    // For project #3 you need to write this routine.
    // See the homework instructions for information
    //     on the shape and position of the sombrero.
    
    // Remove the next four lines of code!
    // Replace them with code that draws
    //     the (cos r)/(1+r*r) surface of revolution.
    glPushMatrix();
    
    glColor3f( 1.0f, 0.3f, 1.0f );
    glTranslatef( 1.0f, 1.2f, 1.0f );
    glutSolidSphere(1.2f, this->meshCount, this->meshCount);
    
    glPopMatrix();
}
