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
//#include <stdlib.h>	// For the "exit" function
#include <GL/glut.h>	// OpenGL Graphics Utility Library
#include "Tetrahedra.h"	// Function prototypes.

// The next global variable controls the animation's state and speed.
float RotateAngle = 0.0f;		// Angle in degrees of rotation around y-axis
float Azimuth = 0.0;			// Rotated up or down by this amount

float AngleStepSize = 3.0f;		// Step three degrees at a time
const float AngleStepMax = 10.0f;
const float AngleStepMin = 0.1f;

int WireFrameOn = 0;			// == 1 for wire frame mode

// glutKeyboardFunc is called below to set this function to handle
//		all "normal" key presses.
void myKeyboardFunc( unsigned char key, int x, int y )
{
	switch ( key ) {
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
	// Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	// Rotate the image
	glMatrixMode( GL_MODELVIEW );			// Current matrix affects objects positions
	glLoadIdentity();						// Initialize to the identity
	glTranslatef( -0.5, 0.0, -25.0 );				// Translate  from origin (in front of viewer)
	glRotatef( RotateAngle, 0.0, 1.0, 0.0 );		// Rotate around y-axis
	glRotatef( Azimuth, 1.0, 0.0, 0.0 );			// Set Azimuth angle

	glPushMatrix();
	glTranslatef( 1.5, 0.0, 0.0 );
	myDrawColorShape1();
	glPopMatrix();
	glTranslatef( -1.5, 0.0, 0.0 );
	myDrawColorShape2();

	// Flush the pipeline, swap the buffers
    glFlush();
    glutSwapBuffers();

}

void myDrawColorShape1() {
	// This is the flat shaded shape initially on the right side of window.
	// It draws the cube as six separate quads.
	// Replace this routine with your own code  
	// Use a triangle fan, plus one more triangle to form a tetrahedron.
    
	glShadeModel( GL_FLAT );	
	glBegin(GL_QUADS);
	
	glColor3f( 1.0, 0.0, 0.0 );   // Red
	glVertex3f( 0.0, 0.0, 1.0 );
	glVertex3f( 1.0, 0.0, 1.0 );
	glVertex3f( 1.0, 1.0, 1.0 );
	glVertex3f( 0.0, 1.0, 1.0 );

	glColor3f( 1.0, 1.0, 0.0 );		// Yellow
	glVertex3f( 1.0, 0.0, 1.0 );
	glVertex3f( 1.0, 0.0, 0.0 );
	glVertex3f( 1.0, 1.0, 0.0 );
	glVertex3f( 1.0, 1.0, 1.0 );

	glColor3f( 0.0, 1.0, 0.0 );		// Green
	glVertex3f( 1.0, 0.0, 0.0 );
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 0.0, 1.0, 0.0 );
	glVertex3f( 1.0, 1.0, 0.0 );

	glColor3f( 0.0, 0.0, 1.0 );		// Blue
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 0.0, 0.0, 1.0 );
	glVertex3f( 0.0, 1.0, 1.0 );
	glVertex3f( 0.0, 1.0, 0.0 );

	glColor3f( 0.8f, 0.8f, 0.8f );		// Light gray
	glVertex3f( 0.0, 1.0, 0.0 );
	glVertex3f( 0.0, 1.0, 1.0 );
	glVertex3f( 1.0, 1.0, 1.0 );
	glVertex3f( 1.0, 1.0, 0.0 );

	glColor3f( 0.2f, 0.2f, 0.2f );		// Dark gray
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 1.0, 0.0, 0.0 );
	glVertex3f( 1.0, 0.0, 1.0 );
	glVertex3f( 0.0, 0.0, 1.0 );

	glEnd();
}

void myDrawColorShape2() {
	// This is the smooth shaded shape initially on the left side.
	// It builds the cube as a quad strip plus two additional quads.
	// Replace this routine with your own code to draw a tetrahedron.
	// Use a single triangle strip to render the tetrahedron.
	
	glShadeModel( GL_SMOOTH );		// Turn smooth shading (the default) back on
	glBegin(GL_QUAD_STRIP);
	
	glColor3f( 1.0, 0.0, 0.0 );     // Red
	glVertex3f( 1.0, 1.0, 1.0 );
	glVertex3f( 1.0, 0.0, 1.0 );

	glColor3f( 1.0, 1.0, 0.0 );		// Yellow
	glVertex3f( 1.0, 1.0, 0.0 );
	glVertex3f( 1.0, 0.0, 0.0 );

	glColor3f( 0.0, 1.0, 0.0 );		// Green
	glVertex3f( 0.0, 1.0, 0.0 );
	glVertex3f( 0.0, 0.0, 0.0 );

	glColor3f( 0.0, 0.0, 1.0 );		// Blue
	glVertex3f( 0.0, 1.0, 1.0 );
	glVertex3f( 0.0, 0.0, 1.0 );

	glColor3f( 1.0, 0.0, 0.0 );     // Red
	glVertex3f( 1.0, 1.0, 1.0 );
	glVertex3f( 1.0, 0.0, 1.0 );

	glEnd();

	
	glBegin( GL_QUADS);

	glColor3f( 0.8f, 0.8f, 0.8f );		// Light gray
	glVertex3f( 0.0, 1.0, 0.0 );
	glVertex3f( 0.0, 1.0, 1.0 );
	glVertex3f( 1.0, 1.0, 1.0 );
	glVertex3f( 1.0, 1.0, 0.0 );

	glColor3f( 0.2f, 0.2f, 0.2f );		// Dark gray
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 1.0, 0.0, 0.0 );
	glVertex3f( 1.0, 0.0, 1.0 );
	glVertex3f( 0.0, 0.0, 1.0 );

	glEnd();

}


// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable( GL_DEPTH_TEST );	// Depth testing must be turned on

	// The next two commands will cause backfaces to not be drawn
	glCullFace( GL_BACK );		// Optional here, since it is the default setting.
	glEnable( GL_CULL_FACE );	// However, culling is not enabled by default.
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
	//		aspect ratio of the scene we want to view, and the code here does not
	//      handle this very well.  (For instance, resize the window to be tall and skinny.)
	w = (w==0) ? 1 : w;
	h = (h==0) ? 1 : h;
	aspectRatio = (double)w / (double)h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 15.0, aspectRatio, 15.0, 35.0 );

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
    glutInitWindowSize( 360, 360 );
    glutCreateWindow( "TwoShapes" );

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

	fprintf(stdout, "Use the four arrow keys to change the viewpoint (this rotates the objects).\n");
	fprintf(stdout, "Press \"w\" to toggle wireframe mode.\n");
	fprintf(stdout, "Press \"R\" or \"r\" to increase or decrease rate of movement (respectively).\n");
	
	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop(  );

    return(0);	// This line is never reached.
}
