/*
 * RollDisk.cpp
 * Base code for homework project #2, Math 155A, Fall 2017.
 *
 * Author: Sam Buss, sbuss@math.ucsd.edu.
 *
 * USAGE:   (Please keep these controls in your homework assignment.)
 *
 *    Press "s" to single step
 *
 *    Press "a" to start the animation running again
 *
 *    Press "R" key to make step size bigger (if moving too slowly)
 *    Press "r" key to make step size smaller (if moving too fast).
 *    "r" stands for Rate of motion.
 *
 *    Press "D" or "d" (for Dimensinn) to increase/descrease the size of
 *          rolling disk.
 *
 *    Press "p" to toggle the modelling potential energy to control 
 *         the rate of motion.
 *     First mode: disk moves always at a constant speed.
 *     Second mode: disk's speed varies with height.
 *
 *	  Press ESCAPE to exit.
 *
 */

#include <math.h>		// For math routines (such as sqrt & trig).
#include <stdio.h>		// For I/O routines, such as fprintf();
//#include <stdlib.h>	// For the "exit" function
#include <GL/glut.h>	// OpenGL Graphics Utility Library
#include "RollDisk.h"	// Function prototypes.

// These variables control the dynamics of the sliding rectangle.
// For the rolling disk, you most likely want to relace the "side length"
//    variables with variables for the radius.
float sideLength = 0.4f;		// Half the length of the diagonal.
const float maxSideLength = sqrtf(2.0f)/2.0f;
const float minSideLength = 0.05f;
// The next variables control the rate of motion.
// "current angle" measures in radians, the angle of the position
//     of the object, 0 is straight down, pi is all the way right,
//     -pi is all the way to the left.
float currentAngle = 0.0f;		// Current position
float currentStep = 0.001f;		// Step size in radians
const float maxStep = 0.01f;
const float minStep = 0.0001f;
// Toggle off/on letting velocity vary with height
// Initially the velocity is constant, independent of height.
bool usePotentialEnergy = false;


// Single step mode and animation mode
GLenum animateMode = GL_TRUE;
GLenum singleStep = GL_FALSE;


// glutKeyboardFunc is called below to set this function to handle
//		all "normal" key presses.
void myKeyboardFunc( unsigned char key, int x, int y )
{
	switch ( key ) {
	case 'D':	// Make bigger dimension
		sideLength = fminf(sideLength*1.1f, maxSideLength);
		glutPostRedisplay();
		break;
	case 'd':	// Make smaller dimension
		sideLength = fmaxf(sideLength/1.1f, minSideLength);
		glutPostRedisplay();
		break;
	
	case 'R':	// Increase the rate
		if (currentStep > 0.0f) {
			currentStep = fminf(currentStep*1.25f, maxStep);
		}
		else {
			currentStep = fmaxf(currentStep*1.25f, -maxStep);
		}
		glutPostRedisplay();
		break;
	case 'r':	// Decrease the rate
		if (currentStep > 0.0f) {
			currentStep = fmaxf(currentStep / 1.25f, minStep);
		}
		else {
			currentStep = fminf(currentStep / 1.25f, -minStep);
		}
		glutPostRedisplay();
		break;

	case 's':
		singleStep = GL_TRUE;
		animateMode = GL_TRUE;
		glutPostRedisplay();
		break;
	case 'a':
		animateMode = GL_TRUE;
		singleStep = GL_FALSE;
		glutPostRedisplay();
		glutPostRedisplay();
		break;

	case 'p':
		usePotentialEnergy = !usePotentialEnergy;
		break;

	case 27:	// Escape key
		exit(1);
	}
}

// glutSpecialFunc is called below to set this function to handle
//		all "special" key presses.  See glut.h for the names of
//		special keys.
void mySpecialKeyFunc( int key, int x, int y )
{
	return;	// No special keys are used.
}

/*
 * drawScene() handles the animation and the redrawing of the
 *		graphics window contents.
 */
void drawScene(void)
{
	// Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	// Rotate the image
	glMatrixMode( GL_MODELVIEW );			// Current matrix affects objects positions
	glLoadIdentity();						// Initialize to the identity

	// Draw the circular track
	myDrawTrellis();

	// Update the dynamics (position information) and draw the object
	if (animateMode) {
		myUpdateDynamics();
	}
	float effectiveRadius = sideLength*(sqrtf(2.0f) / 2.0f);
	myDrawMovingRectangle(currentAngle, effectiveRadius);

	// Flush the pipeline, swap the buffers
    glFlush();
    glutSwapBuffers();

	if (singleStep) {
		animateMode = GL_FALSE;
	}
	else {
		glutPostRedisplay();	// Keep animating
	}
}

void myDrawTrellis() {
	// This is the circular trellis, which the object rolls or slides along.
	// The given codes slides a rectangle along.
	// You should modify to the have a rolling disk, which rolls without slipping..

	const int TrellisN = 60;	// Number of quads in the circular trellis
	glColor3f(1.0, 0.5, 1.0);   // Pright purplish
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Draw the trellis in wireframe mode
	glBegin(GL_QUAD_STRIP);

	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	for (int i = 1; i < TrellisN; i++) {
		float x = ((float)i / (float)TrellisN)*2.0f - 1.0f;
		float y = -sqrtf(1.0f - x*x);
		glVertex3f(x, y, 0.0f);
		glVertex3f(x, -1.0f, 0.0f);
	}
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}

void myDrawMovingRectangle(float theta, float radius )
{
	// This code draws a square rectangle the slides along the circular track.
	// You will replace this with a disk that *rolls* along the track without slipping.
	// The paramater theta is in radians 
	//  Radius is the distance from the center to the a vertex of the square
	glColor3f(0.0f, 1.0f, 1.0f);	// Yellow (= Green plus Blue)
	const float rad = radius*sqrtf(2.0f)/2.0f;
	glPushMatrix();
	// Move the rectangle along the track
	glRotatef(theta*180.0f/3.14159f, 0.0f, 0.0f, 1.0f);
	// Move the rectangle down to touch the circular track. (Harder for rectangle than for disk!).
	glTranslatef(0.0f, -(sqrtf(1.0f-rad*rad)-rad), 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(rad, rad, 0.0f);
	glVertex3f(-rad, rad, 0.0f);
	glVertex3f(-rad, -rad, 0.0f);
	glVertex3f(rad, -rad, 0.0f);
	glEnd();
	glPopMatrix();
}

void myUpdateDynamics()
{
	float deltaAngle;
	if (!usePotentialEnergy) {
		deltaAngle = currentStep;
	}
	else {
		// For the disk use the actual radius for the effective radius
		// "h" measures how far down the center is from its maximum height.
		float effectiveRadius = sideLength*sqrtf(2.0f) / 2.0f;
		float hMax = effectiveRadius;
		float h = effectiveRadius*cosf(currentAngle);	// This height contributes to reduced potential energy.
		deltaAngle = currentStep * sqrtf(h / hMax);		// Velocity proportional to sqrt(h).
	}
	const float piHalves = 3.14159f / 2.0f;
	// Constant velocity back-and-forth
	currentAngle += deltaAngle;
	if (currentAngle >= piHalves) {
		currentAngle = piHalves;		// Do not allow to overshoot end
		currentStep = -currentStep;		// Reverse direction of motion
	}
	else if (currentAngle <= -piHalves) {
		currentAngle = -piHalves;		// Do not allow to overshoot end
		currentStep = -currentStep;		// Reverse direction of motion
	}

}

// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable( GL_DEPTH_TEST );	// Depth testing must be turned on (not really used here, since it is essentially 2D).
	glShadeModel(GL_FLAT);
}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
double Xmin = -1.05, Xmax = 1.05;
double Ymin = -1.05, Ymax = 0.6;
void resizeWindow(int w, int h)
{
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	// Define the portion of the window used for OpenGL rendering.
	glViewport(0, 0, w, h);	// View port uses whole window

	// Set up the projection view matrix: orthographic projection
	// Determine the min and max values for x and y that should appear in the window.
	// The complication is that the aspect ratio of the window may not match the
	//		aspect ratio of the scene we want to view.
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;
	if ((Xmax - Xmin) / w < (Ymax - Ymin) / h) {
		scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
		center = (Xmax + Xmin) / 2;
		windowXmin = center - (center - Xmin)*scale;
		windowXmax = center + (Xmax - center)*scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
		center = (Ymax + Ymin) / 2;
		windowYmin = center - (center - Ymin)*scale;
		windowYmax = center + (Ymax - center)*scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}

	// Now that we know the max & min values for x & y that should be visible in the window,
	//		we set up the orthographic projection.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);
}


// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
	glutInit(&argc, argv);

	// We're going to animate it, so double buffer 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// Window position (from top corner), and size (width and hieght).
	//    Position and size are specified in terms of pixels.
    glutInitWindowPosition( 10, 60 );
    glutInitWindowSize( 720, 720 );
    glutCreateWindow( "Roll Disk Demo" );

	// Initialize OpenGL as we like it..
    initRendering();

	// Set up callback functions for key presses
	glutKeyboardFunc( myKeyboardFunc );			// Handles "normal" ascii symbols
	glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys

	// Set up the callback function for resizing windows
    glutReshapeFunc( resizeWindow );

	// Call this for background processing
	// Commented out, since the scene only changes in response to keystrokes or 
	//       when the window is resized.
	// glutIdleFunc( myIdleFunction );

	// call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

	fprintf(stdout, "Press \"s\" for single stepping. Press \"a\" for continuing animation.\n");
	fprintf(stdout, "Press \"R\" or \"r\" to increase or decrease rate of movement (respectively).\n");
	fprintf(stdout, "Press \"D\" or \"d\" to increase or decrease the size (the dimensions).\n");
	fprintf(stdout, "Press \"p\" to toggle the constant velocity versus variable velocity.\n");

	
	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop(  );

    return(0);	// This line is never reached.
}
