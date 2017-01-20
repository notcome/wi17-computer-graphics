/*
 * Tetrahedra.h
 *
 * Author: Samuel R. Buss
 *
 * Bug reports: Sam Buss, sbuss@ucsd.edu.
 * 
 * Base code for homework project #1, Math 155A, Fall 2017
 */

// Function prototypes for Tetrahrdra.cpp

void myKeyboardFunc( unsigned char key, int x, int y );
void mySpecialKeyFunc( int key, int x, int y );

void drawScene(void);

void initRendering();
void resizeWindow(int w, int h);

void myDrawColorShape1();
void myDrawColorShape2();

