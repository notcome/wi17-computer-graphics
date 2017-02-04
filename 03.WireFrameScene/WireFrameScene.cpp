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
#include <array>

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
    const float timeStep = 0.05f;
    
    void drawGeometry();
    void drawRotatingSurface();
    
    // Rotation of x,y-plane.
    float azimuth = 15.0f;
    // Rotation around y axis.
    float rotation = 0.0f;
    
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
            this->isAnimated = !this->isAnimated;
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
    const float hypotenuse = 4.0f;
    const float inclination = 15.0f;
    const float height = cosf(degreeToRadian(inclination)) * hypotenuse;
    const float halfWidth = sinf(degreeToRadian(inclination)) * hypotenuse;
    const float elliXZRadius = 0.5f / 2;
    const auto drawSphere = bind(drawSolidSphereAtNorthPole, meshCount);
    
    glPushMatrix();
    glTranslatef(-2, 0, -2);
    glRotatef(45, 0, 1, 0);
    {
        color(0.0f, 1.0f, 0.5f);
        
        glPushMatrix();
        glTranslatef(-halfWidth, height, 0.0f);
        glRotatef(-inclination, 0, 0, 1);
        withScale(elliXZRadius, hypotenuse / 2, elliXZRadius, drawSphere);
        glRotatef(inclination * 2, 0, 0, 1);
        withScale(elliXZRadius, hypotenuse / 2, elliXZRadius, drawSphere);
        glPopMatrix();
        
        glPushMatrix();
        const float rightLegRotation = (this->time <= PI ? time : 2 * PI - time) / PI * 45.0f;
        glRotatef(-rightLegRotation, 0, 1, 0);
        glTranslatef(halfWidth, height, 0.0f);
        glRotatef(inclination, 0, 0, 1);
        withScale(elliXZRadius, hypotenuse / 2, elliXZRadius, drawSphere);
        glRotatef(-inclination * 2, 0, 0, 1);
        withScale(elliXZRadius, hypotenuse / 2, elliXZRadius, drawSphere);
        glPopMatrix();
    }
    glPopMatrix();
}

inline float meshToAngle(int meshCount, int i) {
    return static_cast<float>(i % meshCount) / meshCount * 2 * PI;
}

inline array<float, 3> parameterize(float theta, float radius) {
    array<float, 3> coord{ {
        cosf(theta) * radius * 1,
        cosf(radius) / (5 + radius * radius),
        -sinf(theta) * radius * 1
    } };
    return coord;
}

void WireFrameSceneWindow::drawRotatingSurface() {
    const float radiusStep = 1.0f / meshCount * 3 * PI;
    
    glPushMatrix();
    glTranslatef(1.2f, 0.6f, 1.2f);
    glScalef(0.8 / PI, 8, 0.8 / PI);
    color(1.0f, 0.3f, 1.0f);
    
    DrawBlock(GL_TRIANGLE_FAN, [=](){
        vertex(0.0f, 0.2f, 0.0f);
        for (int i = 0; i <= meshCount; i ++) {
            float theta = meshToAngle(meshCount, i);
            vertex(parameterize(theta, radiusStep).data());
        }
    });
    
    // We compute using polar coordinates and convert them to Cartessian coordinates.
    for (int i = 0; i < meshCount; i ++) {
        float theta1 = meshToAngle(meshCount, i);
        float theta2 = meshToAngle(meshCount, i + 1);
        
        DrawBlock(GL_QUAD_STRIP, [=]{
            float radius = radiusStep;
            vertex(parameterize(theta2, radius).data());
            vertex(parameterize(theta1, radius).data());
            for (int j = 2; j <= meshCount; j ++) {
                radius += radiusStep;
                vertex(parameterize(theta2, radius).data());
                vertex(parameterize(theta1, radius).data());
            }
        });
    }
    
    glPopMatrix();
}
