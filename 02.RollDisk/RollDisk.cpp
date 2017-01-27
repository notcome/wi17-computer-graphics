/* -------------------------------------------------------------------------- *
 * 02-RollDisk :: RollDisk.cpp
 *
 * Project 2, Math 155A, Fall 2017.
 *
 * Author: Minsheng Liu.
 * Based on the code provided by professor Sam Buss, which is in "Assets/" of
 *   the folder where this files is located.
 */

#include "GLUT/Common.h"
#include "GLUT/Window.h"
#include "GLUT/Constants.h"
#include "GLUT/ModernGL.h"
using namespace GLUT;

#include <cmath>
#include <iostream>
#include <cstdlib>
using namespace std;

class RollDiskWindow: public Window {
    const float trellisRadius = 1.0f;
    const float maxDiskRadius = trellisRadius / 2.0f;
    const float minDiskRadius = 0.05f;
    float diskRadius = 0.2f * sqrt(2.0f);
    
    const float maxStep = 0.1f;
    const float minStep = 0.0001f;
    float currentStep   = 0.01f;
    float currentAngle  = 0.0f;
    
    bool isPontentialEnergyEnabled = false;
    bool isAnimated = true;
    
public:
    virtual void onKeyPress (unsigned char key, int x, int y) {
        if (key == 'p') {
            this->isPontentialEnergyEnabled = !this->isPontentialEnergyEnabled;
        } else if (key == 27) {
            exit(1);
        } else {
            if (key == 'D')
                this->diskRadius = fmin(this->diskRadius * 1.1, maxDiskRadius);
            else if (key == 'd')
                this->diskRadius = fmax(this->diskRadius / 1.1, minDiskRadius);
            else if (key == 'R')
                currentStep > 0.0f
                ? currentStep = fminf(currentStep * 1.25f, maxStep)
                : currentStep = fmaxf(currentStep * 1.25f, -maxStep);
            else if (key == 'r')
                currentStep > 0.0f
                ? currentStep = fmaxf(currentStep / 1.25f, minStep)
                : currentStep = fminf(currentStep / 1.25f, -minStep);
            else if (key == 's') {
                this->isAnimated = false;
                this->updateDynamics();
            }
            else if (key == 'a')
                this->isAnimated = true;
            else
                return;
            
            this->postRedisplay();
        }
    }
    
    struct Bound {
        double minX, maxX, minY, maxY;
    };
    
    virtual void onResizeWindow (int width, int height) {
        width = (width == 0) ? 1 : width;
        height = (height == 0) ? 1 : height;
        glViewport(0, 0, width, height);
        
        const Bound scene  = Bound { -1.05, 1.05, -1.05, 0.6 };
        double widthScale  = (scene.maxX - scene.minX) / height;
        double heightScale = (scene.maxY - scene.minY) / height;
        
        double scale, center;
        Bound window;
        
        if (widthScale < heightScale) {
            scale = heightScale / widthScale;
            center = (scene.maxX + scene.minX) / 2;
            window = Bound {
                center - (center - scene.minX) * scale,
                center + (scene.maxX - center) * scale,
                scene.minY,
                scene.maxY
            };
        } else {
            scale = widthScale / heightScale;
            center = (scene.maxY + scene.minY) / 2;
            window = Bound {
                scene.minX,
                scene.maxX,
                center - (center - scene.minY) * scale,
                center + (scene.maxY - center) * scale
            };
        }
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(window.minX, window.maxX, window.minY, window.maxY, -1, 1);
    }
    
    void updateDynamics () {
        const float angleDiff
            = this->isPontentialEnergyEnabled
            ? this->currentStep * sqrtf(cosf(this->currentAngle))
            : this->currentStep;

        const float TAU = PI / 2.0f;
        
        this->currentAngle += angleDiff;
        if (this->currentAngle >= TAU) {
            this->currentAngle = TAU;
            this->currentStep = -this->currentStep;
        }
        if (this->currentAngle <= -TAU) {
            this->currentAngle = -TAU;
            this->currentStep = -this->currentStep;
        }
    }
    
    void drawRollingDisk (float trellisRadian) {
        const float GPB[] = {0.0f, 1.0f, 1.0f};
        color(GPB);
        
        glPushMatrix();
        glRotatef(radianToDegree(trellisRadian), 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, -trellisRadius + diskRadius, 0.0f);
        
        auto diskRadian = -trellisRadian * (trellisRadius / diskRadius);
        glRotatef(-radianToDegree(trellisRadian), 0.0f, 0.0f, 1.0f);
        glRotatef(radianToDegree(diskRadian), 0.0f, 0.0f, 1.0f);
        
        DrawBlock(GL_TRIANGLE_FAN, [=]() {
            vertex(0.0, 0.0, 0.0);
            for (int i = 0; i <= 18; i ++) {
                float degree = 2 * PI / 18. * static_cast<float>(i);
                vertex(cosf(degree) * diskRadius, sinf(degree) * diskRadius, 0);
            }
        });
        
        const float *colors[3];
        colors[0] = Color::green;
        colors[1] = Color::blue;
        colors[2] = Color::red;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        for (int i = 0; i < 6; i ++) {
            float d1 = 2 * PI / 18. * static_cast<float>(i * 3);
            float d2 = 2 * PI / 18. * static_cast<float>(i * 3 + 1);
            DrawBlock(GL_TRIANGLES, [=](){
                color(colors[i % 3]);
                vertex(0.0, 0.0, 0.0);
                vertex(cosf(d1) * diskRadius, sinf(d1) * diskRadius, 0);
                vertex(cosf(d2) * diskRadius, sinf(d2) * diskRadius, 0);
            });
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glPopMatrix();
    }
    
    void drawTrellis () {
        const int numberOfColumns = 60;
        
        color(1.0, 0.5, 1.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        DrawBlock(GL_QUAD_STRIP, [=]() {
            for (int i = 0; i <= numberOfColumns; i ++) {
                float x = (static_cast<float>(i) / numberOfColumns) * 2. - 1.;
                float y = -sqrtf(1.0f - x * x);
                x *= trellisRadius;
                y *= trellisRadius;
                vertex(x, y, 0.0f);
                vertex(x, -trellisRadius, 0.f);
            }
        });
    }
    
    virtual void draw () {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        this->drawTrellis();
        
        if (this->isAnimated)
            this->updateDynamics();
        this->drawRollingDisk(this->currentAngle);
        
        this->flushAndSwapBuffers();
        
        if (this->isAnimated)
            this->postRedisplay();
    }
    
    RollDiskWindow (int argc, char **argv)
    : Window(argc, argv, "Roll Disk Demo", 10, 60, 720, 720)
    { }
};

int main (int argc, char **argv) {
    globalWindow = new RollDiskWindow(argc, argv);
    
    cout << "Press \"s\" for single stepping. Press \"a\" for continuing animation.\n";
    cout << "Press \"R\" or \"r\" to increase or decrease rate of movement (respectively).\n";
    cout << "Press \"D\" or \"d\" to increase or decrease the size (the dimensions).\n";
    cout << "Press \"p\" to toggle the constant velocity versus variable velocity.\n";

    globalWindow->runLoop();
    
    return 0;
}
