
#include <stdlib.h>
#include <stdio.h>

// for mac osx
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
// only for windows
#ifdef _WIN32
#include <windows.h>
#endif
// for windows and linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <math.h>

// Global variables to animate the robotic arm
int Angle1 = 0;
int Angle2 = 0;

// Global variables to rotate the arm as a whole
int RobotAngleX = 0;
int RobotAngleY = 0;



//*************************************************************************
// Function that draws a reference system
//*************************************************************************
void DrawReferenceSystem()
{
	//**********************************
	// set the line width to 3.0
	//**********************************

	//**********************************
	// Draw three lines along the x, y, z axis to represent the reference system
	// Use red for the x-axis, green for the y-axis and blue for the z-axis
	//**********************************




	//**********************************
	// reset the drawing color to white
	//**********************************

	//**********************************
	// reset the line width to 1.0
	//**********************************

}


//*************************************************************************
// Function that draws a single joint of the robotic arm
//*************************************************************************
void DrawJoint()
{
	// first draw the reference system
	DrawReferenceSystem();

	// Draw the joint as a parallepiped (a cube scaled on the y-axis)
	// the bottom face of the cube must be on the xy axis



	//**********************************
	// draw the parallepiped
	//**********************************




}

// Function that draws the robot as three parallelepipeds
void DrawRobot()
{
	//**********************************
	// It's better to work on a local reference system...
	//**********************************

	// draw the first joint
	DrawJoint();

	// Draw the other joints
	// every joint must be placed on top of the previous one
	// and rotated according to the relevant Angle
	//**********************************
	// the second joint
	//**********************************



	//**********************************
	// the third joint
	//**********************************



	//**********************************
	// "Release" the copy of the current MODELVIEW matrix
	//**********************************

}


//*************************************************************************
// display callback
//*************************************************************************
void display(void)
{
	// clear the window
	glClear (GL_COLOR_BUFFER_BIT);

	// working with the GL_MODELVIEW Matrix
	glMatrixMode(GL_MODELVIEW);

	//**********************************
	// we work on a copy of the current MODELVIEW matrix, hence we need to...
	//**********************************


	//**********************************
	// Rotate the robot around the x-axis and y-axis according to the relevant angles
	//**********************************



	// draw the robot
	DrawRobot();

	//**********************************
	// not anymore on a local reference system
	//**********************************

	// flush drawing routines to the window
	glutSwapBuffers();
}

//*************************************************************************
// Special keys callback
//*************************************************************************
void arrows (int key, int x, int y)
{
		//**********************************
		// Manage the update of RobotAngleX and RobotAngleY with the arrow keys
		//**********************************




		glutPostRedisplay ();
}

//*************************************************************************
// Keyboard callback
//*************************************************************************
void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q':
		case 27:
			exit(0);
		break;
		//**********************************
		// Manage the update of Angle1 with the key 'a' and 'z'
		//**********************************







		//**********************************
		// Manage the update of Angle2 with the key 'e' and 'r'
		//**********************************








		default:
        break;
	}
	glutPostRedisplay ();
}



void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, 1.0, 1.0, 100.0);

	glShadeModel (GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Place the camera
	gluLookAt(-6,5,-6,0,0,2,0,1,0);
}


//*************************************************************************
// Function called every time the main window is resized
//*************************************************************************
void reshape ( int width, int height )
{

    // define the viewport transformation;
    glViewport(0,0,width,height);
    if (width < height)
        glViewport(0,(height-width)/2,width,width);
    else
        glViewport((width-height)/2,0,height,height);
}


//*************************************************************************
// Prints out how to use the keyboard
//*************************************************************************
void usage()
{
	printf ("\n*******\n");
	printf ("Arrows key: rotate the whole robot\n");
	printf ("[a][z] : move the second joint of the arm\n");
	printf ("[e][r] : move the third joint of the arm\n");
	printf ("[esc]  : terminate\n");
	printf ("*******\n");
}

//////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow(argv[0]);
   init ();
   glutDisplayFunc(display);

   glutReshapeFunc(reshape);
    //**********************************
   // Register the keyboard function
   //**********************************

   //**********************************
   // Register the special key function
   //**********************************

   // just print the help
   usage();

   glutMainLoop();

   return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////
