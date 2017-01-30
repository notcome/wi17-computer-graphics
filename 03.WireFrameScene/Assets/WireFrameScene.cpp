/*
 * WireFrameScene.c
 *
 * Author: Samuel R. Buss
 *
 * Bug reports: Sam Buss, sbuss@ucsd.edu.
 * 
 * Base code for homework project #3, Math 155A, Winter 2012
 *
 * USAGE:   Please keep these controls in your project!!!
 *
 *    Press arrow keys to control view position.
 *	  left and right keys rotate the viewpoint left and right
 *	  Up and down keys rotate viewpoint up and down (up to 80 degrees).
 *
 *    Press "R" key to make step size bigger (if moving too slowly)
 *    Press "r" key to make step size smaller (if moving too fast).
 *
 *    Press "w" key to toggle wireframe mode on and off
 *    
 *    Press "M" , "m" to increase, decrease Mesh Resolution
 *         Should apply to all appropriate objects in the scene,
 *			including any glut objects (spheres, etc) and
 *			including especially the (sin x)/x surface.
 *
 *    Press "c" to toggle culling backfaces.
 *
 *    Press "a" to toggle animation off and on.
 *  
 *	  Press ESCAPE to exit.
 *
 */

#include <math.h>			// For math routines (such as sqrt & trig).
#include <stdio.h>
//#include <stdlib.h>		// For the "exit" function
#include <GL/glut.h>		// OpenGL Graphics Utility Library
#include "WireFrameScene.h"

// The next global variable controls the animation's state and speed.
float RotateAngle = 0.0f;		// Angle in degrees of rotation around y-axis
float Azimuth = 0.0;			// Rotated up or down by this amount
float AngleStepSize = 3.0f;		// Step three degrees at a time
const float AngleStepMax = 10.0f;
const float AngleStepMin = 0.1f;

// Some global state variables
int MeshCount = 6;				// The mesh resolution for the mushroom top
int WireFrameOn = 1;			// == 1 for wire frame mode
int CullBackFacesOn = 0;		// == 1 if culling back faces.
const int MeshCountMin = 3;

// Animation
// Your solution for Project #3 may use different animation controls if desired.
int animationOn = 1;
const float timeStep = 0.005f;  // Controls the speed of the animation of the "S"
float t = 0;

// glutKeyboardFunc is called below to set this function to handle
//		all "normal" key presses.
void myKeyboardFunc( unsigned char key, int x, int y )
{
	switch ( key ) {
	case 'a':
		animationOn = 1 - animationOn;
		break;
	case 'c':
		CullBackFacesOn = 1-CullBackFacesOn;
		if ( CullBackFacesOn ) {
			glEnable( GL_CULL_FACE );				// Enable culling of back faces
		}
		else {
			glDisable( GL_CULL_FACE );				// Show all faces (front and back)
		}
		glutPostRedisplay();
		break;
	case 'm':
		MeshCount = (MeshCount>MeshCountMin) ? MeshCount-1 : MeshCount;
		glutPostRedisplay();
		break;
	case 'M':
		MeshCount ++;
		glutPostRedisplay();
		break;
	case 'w':
		WireFrameOn = 1-WireFrameOn;
		if ( WireFrameOn ) {
			glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );		// Just show wireframes
		}
		else {
			glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );		// Show solid polygons
		}
		glutPostRedisplay();
		break;
	case 'R':
		AngleStepSize *= 1.5;
		if (AngleStepSize>AngleStepMax ) {
			AngleStepSize = AngleStepMax;
		}
		break;
	case 'r':
		AngleStepSize /= 1.5;
		if (AngleStepSize<AngleStepMin ) {
			AngleStepSize = AngleStepMin;
		}
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
	switch ( key ) {
	case GLUT_KEY_UP:	
		Azimuth += AngleStepSize;
		if ( Azimuth>80.0f ) {
			Azimuth = 80.0f;
		}
		break;
	case GLUT_KEY_DOWN:
		Azimuth -= AngleStepSize;
		if ( Azimuth < -80.0f ) {
			Azimuth = -80.0f;
		}
		break;
	case GLUT_KEY_LEFT:
		RotateAngle += AngleStepSize;
		if ( RotateAngle > 180.0f ) {
			RotateAngle -= 360.0f;
		}
		break;
	case GLUT_KEY_RIGHT:
		RotateAngle -= AngleStepSize;
		if ( RotateAngle < -180.0f ) {
			RotateAngle += 360.0f;
		}
		break;
	}
	glutPostRedisplay();

}

/*
 * drawScene() handles the animation and the redrawing of the
 *		graphics window contents.
 */
void drawScene(void)
{
	if (animationOn) {
		t += timeStep;
	}
	// Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Rotate the image
	glMatrixMode( GL_MODELVIEW );			// Current matrix affects objects positions
	glLoadIdentity();						// Initialize to the identity
	glTranslatef( 0.0, -2.5, -35.0 );				// Translate from origin (in front of viewer)
	glRotatef( Azimuth, 1.0, 0.0, 0.0 );			// Set Azimuth angle
	glRotatef( RotateAngle, 0.0, 1.0, 0.0 );		// Rotate around y-axis

	// Draw the base plane (white)
	glColor3f( 1.0, 1.0, 1.0 );
	glBegin( GL_QUADS );
	glVertex3f( -4.0, 0.0,  4.0 );
	glVertex3f(  4.0, 0.0,  4.0 );
	glVertex3f(  4.0, 0.0, -4.0 );
	glVertex3f( -4.0, 0.0, -4.0 );
	glEnd();

	// Draw the surface of rotation
	myDrawSurfaceOfRotation();			// You will need to write this function!

	// Draw the letter-based structure
	myDrawGeometry();					// You will need to write this function!

	// Flush the pipeline, swap the buffers
    glFlush();
    glutSwapBuffers();

	glutPostRedisplay();


}


void myDrawSurfaceOfRotation() 
{
	// For project #3 you need to write this routine.
	// See the homework instructions for information 
	//     on the shape and position of the sombrero.
	
	// Remove the next four lines of code!
	// Replace them with code that draws
	//     the (cos r)/(1+r*r) surface of revolution.
	glPushMatrix();

	glColor3f( 1.0f, 0.3f, 1.0f );
	glTranslatef( 1.0f, 1.2f, 1.0f );
	glutSolidSphere( 1.2f, MeshCount, MeshCount );

	glPopMatrix();

	return;

}

void myDrawGeometry() 
{
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
	glutSolidSphere( 1.0, MeshCount, MeshCount );
	glPopMatrix();
	glPushMatrix();
	glTranslatef( 0.5, 0.5, 0.0 );
	glRotatef( 45.0, 0.0, 0.0, 1.0 );
	glRotatef( 90.0, 0.0, 1.0, 0.0 );
	glScalef( 0.20f, 0.20f, 0.66f );
	glutSolidSphere( 1.0, MeshCount, MeshCount );
	glPopMatrix();
	glPushMatrix();
	glTranslatef( 0.0, 2.0, 0.0 );
	glRotatef( -45.0, 0.0, 0.0, 1.0 );
	glRotatef( 90.0, 0.0, 1.0, 0.0 );
	glScalef( 0.20f, 0.2f, 1.33f );
	glutSolidSphere ( 1.0, MeshCount, MeshCount );
	glPopMatrix();
	glPushMatrix();
	glTranslatef( -0.5, 3.5, 0.0 );
	glRotatef( 45.0, 0.0, 0.0, 1.0 );
	glRotatef( 90.0, 0.0, 1.0, 0.0 );
	glScalef( 0.20f, 0.20f, 0.66f );
	glutSolidSphere( 1.0, MeshCount, MeshCount );
	glPopMatrix();
	// Now do the animated ellipsoid
	glPushMatrix();
	if ( t>2.0*3.1415926535f ) {
		t -= 2.0*3.1415926535f;	// Clamp to between 0 and 2*pi
	}
	float a = -sinf(t);
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
	glutSolidSphere( 1.0, MeshCount, MeshCount );
	glPopMatrix();
	
	glPopMatrix();
	
	return;

}

// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable( GL_DEPTH_TEST );	// Depth testing must be turned on

	glCullFace( GL_BACK );		// These two commands will cause backfaces to not be drawn

	// Possibly turn on culling of back faces.
	if ( CullBackFacesOn ) {
		glEnable( GL_CULL_FACE );
	}

	// Possibly turn on wireframe mode.
	if ( WireFrameOn ) {
		glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );		// Just show wireframes
	}
}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
	double aspectRatio;

	// Define the portion of the window used for OpenGL rendering.
	glViewport( 0, 0, w, h );	// View port uses whole window

	// Set up the projection view matrix: perspective projection
	// Determine the min and max values for x and y that should appear in the window.
	// The complication is that the aspect ratio of the window may not match the
	//		aspect ratio of the scene we want to view.
	w = (w==0) ? 1 : w;
	h = (h==0) ? 1 : h;
	aspectRatio = (double)w / (double)h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 12.0, aspectRatio, 20.0, 50.0 );

}


// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
	glutInit(&argc, argv);

	// We're going to animate it, so double buffer 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// Window position (from top corner), and size (width% and hieght)
    glutInitWindowPosition( 10, 60 );
    glutInitWindowSize( 480, 360 );
    glutCreateWindow( "Wire Frame Scene Demo" );

	// Initialize OpenGL as we like it..
    initRendering();

	// Set up callback functions for key presses
	glutKeyboardFunc( myKeyboardFunc );			// Handles "normal" ascii symbols
	glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys

	// Set up the callback function for resizing windows
    glutReshapeFunc( resizeWindow );

	// Call this for background processing
	// glutIdleFunc( myIdleFunction );

	// call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

	fprintf(stdout, "Arrow keys control viewpoint.n");
	fprintf(stdout, "Press \"w\" to toggle wireframe mode.\n");
	fprintf(stdout, "Press \"c\" to toggle culling of back faces.\n");
	fprintf(stdout, "Press \"M\" or \"m\" to increase or decrease resolution of mushroom cap.\n");
	fprintf(stdout, "Press \"R\" or \"r\" to increase or decrease rate of movement (respectively).\n");
	fprintf(stdout, "Press \"a\" to toggle animation on and off.\n");

	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop(  );

    return(0);	// This line is never reached.
}
