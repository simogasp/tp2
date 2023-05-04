
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

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


// Global variables to animate the robotic arm
int Angle1 = 0;
int Angle2 = 0;

// Global variables to rotate the arm as a whole
int RobotAngleX = 0;
int RobotAngleY = 0;

//<!!
// how open are the pincers [0,1]
#define START 0.125f
#define END 0.5f
float open = 1.0f;
//>!!

/**
 * Function that draws the reference system (three lines along the x, y, z axis)
 */
void DrawReferenceSystem()
{
    //**********************************
    // set the line width to 3.0
    //**********************************
    glLineWidth (3.f);
    //**********************************
    // Draw three lines along the x, y, z axis to represent the reference system
    // Use red for the x-axis, green for the y-axis and blue for the z-axis
    //**********************************
//<!!
    glBegin (GL_LINES);
    //**********************************
    // Set the color red for the x-axis
    //**********************************
    glColor3f ( 1.f, 0.f, 0.f);
    //**********************************
    // Set TWO ending points for the line representing the x-axis
    //**********************************
    glVertex3f (0.f, 0.f, 0.f);
    glVertex3f (1.f, 0.f, 0.f);
    //**********************************
    // Set the color green for the y-axis
    //**********************************
    glColor3f (0.f, 1.f, 0.f);
    //**********************************
    // Set TWO ending points for the line representing the y-axis
    //**********************************
    glVertex3f (0.f, 0.f, 0.f);
    glVertex3f (0.f, 1.f, 0.f);
    //**********************************
    // Set the color blue for the z-axis
    //**********************************
    glColor3f (0.f, 0.f, 1.f);
    //**********************************
    // Set TWO ending points for the line representing the z-axis
    //**********************************
    glVertex3f (0.f, 0.f, 0.f);
    glVertex3f (0.f, 0.f, 1.f);
    //**********************************
    // End the drawing
    //**********************************
    glEnd();
//>!!
    //**********************************
    // reset the drawing color to white
    //**********************************
    glColor3f (1.f,1.f, 1.f);  //!!
    //**********************************
    // reset the line width to 1.0
    //**********************************
    glLineWidth (1.f);  //!!
}


/**
 * Function that draws a single joint of the robotic arm
 */
void DrawJoint()
{
    // first draw the reference system
    DrawReferenceSystem();

    // Draw the joint as a parallelepiped (a cube scaled on the y-axis)
    //**********************************
    // Bring the cube "up" so that the bottom face is on the xz plane
    //**********************************
    glTranslatef (0.f, 1.f,0.f ); //!!

    //**********************************
    // draw the scaled cube. Remember that the scaling has to be only
    // on the local reference system, hence we need to get a local copy
    // of the modelview matrix...
    //**********************************
//<!!
    glPushMatrix();
    glScalef(1.f,2.f,1.f);
    glutWireCube(1.f);
    glPopMatrix();
//>!!
}

/**
 * Function that draws the robot as three parallelepipeds
 */
void DrawRobot()
{
    //**********************************
    // we work on a copy of the current MODELVIEW matrix, hence we need to...
    //**********************************
    glPushMatrix();  //!!

    // draw the first joint
    DrawJoint();
    glTranslatef (0.f, 1.f,0.f );  //!!

    // Draw the other joints
    // every joint must be placed on top of the previous one
    // and rotated according to the relevant Angle
    //**********************************
    // the second joint
    //**********************************
    glRotatef (Angle1, 1.f, 0.f, 0.f);  //!!
    DrawJoint();                        //!!
    //**********************************
    // the third joint
    //**********************************
//<!!
    glTranslatef (0.f, 1.f,0.f );
    glRotatef (Angle2, 1.f, 0.f, 0.f);
    DrawJoint();

    // Draw the Pincers
    // First the base
    glTranslatef (0.f, 1.125f,0.f );
    glPushMatrix();
    glScalef(1.f,0.25f,0.25f);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef (0.f, 0.45f,0.f );
    // The the fork
    glPushMatrix();
    glTranslatef (-START + open*(START-END), 0.f,0.f );
    glScalef(0.25f,0.65f,0.25f);
    glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef (START + open*(END-START), 0.0f,0.f );
    glScalef(0.25f,0.65f,0.25f);
    glutWireCube(1);
    glPopMatrix();
//>!!
    //**********************************
    // "Release" the copy of the current MODELVIEW matrix
    //**********************************
    glPopMatrix();  //!!

}


/**
 * Function that handles the display callback (drawing routine)
 */
void display()
{
    // clear the window
    glClear (GL_COLOR_BUFFER_BIT);

    // working with the GL_MODELVIEW Matrix
    glMatrixMode(GL_MODELVIEW);

    //**********************************
    // we work on a copy of the current MODELVIEW matrix, hence we need to...
    //**********************************
    glPushMatrix();  //!!
    DrawReferenceSystem();  //!!
    //**********************************
    // Rotate the robot around the x-axis and y-axis according to the relevant angles
    //**********************************
    glRotatef(RobotAngleX,1.f,0,0.f);  //!!
    glRotatef(RobotAngleY,0.f,1.f,0.f);  //!!

    // draw the robot
    DrawRobot();

    //**********************************
    // "Release" the copy of the current MODELVIEW matrix
    //**********************************
    glPopMatrix();  //!!

    // flush drawing routines to the window
    glutSwapBuffers();
}


/**
 * Function that handles the special keys callback
 * @param[in] key the key that has been pressed
 * @param[in] x the mouse in window relative x-coordinate when the key was pressed
 * @param[in] y the mouse in window relative y-coordinate when the key was pressed
 */
void arrows (int key, int, int)
{
    //**********************************
    // Manage the update of RobotAngleX and RobotAngleY with the arrow keys
    //**********************************
//<!!
    switch (key)
    {
        case GLUT_KEY_UP:
            RobotAngleX = (RobotAngleX+5) % 360;
            break;
        case GLUT_KEY_DOWN:
            RobotAngleX = (RobotAngleX-5) % 360;
            break;
        case GLUT_KEY_LEFT:
            RobotAngleY = (RobotAngleY+5) % 360;
            break;
        case GLUT_KEY_RIGHT:
            RobotAngleY = (RobotAngleY-5) % 360;
            break;
        default: break;
    }
//>!!
    glutPostRedisplay ();
}


/**
 * Function that handles the keyboard callback
 * @param key  the key that has been pressed
 * @param[in] x the mouse in window relative x-coordinate when the key was pressed
 * @param[in] y the mouse in window relative y-coordinate when the key was pressed
 */
void keyboard (unsigned char key, int, int)
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
//<!!
        case 'a':
            Angle1 = (Angle1+5) % 360;
//            printf("Angle 1: %f\n",(float)Angle1);
            break;
        case 'z':
            Angle1 = (Angle1-5) % 360;
//            printf("Angle 1: %f\n",(float)Angle1);
            break;
            //**********************************
            // Manage the update of Angle2 with the key 'e' and 'r'
            //**********************************
        case 'e':
            Angle2 = (Angle2+5) % 360;
//            printf("Angle 2: %f\n",(float)Angle2);
            break;
        case 'r':
            Angle2 = (Angle2-5) % 360;
//            printf("Angle 2: %f\n",(float)Angle2);
            break;

        //**********************************
        // Manage the pincers
        //**********************************
        case 'o':
            open += 0.05f;
            break;
        case 'l':
            open -= 0.05f;
            break;
//>!!
        default:
            break;
    }
    open = std::clamp(open, 0.f, 1.f);   //!!
    glutPostRedisplay ();
}



void init()
{
    glClearColor (0.f, 0.f, 0.f, 0.f);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65.0, 1.0, 1.0, 100.0);

    glShadeModel (GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Place the camera
    gluLookAt(-1,5,-1,0,0,2,0,1,0);
}


/**
 * Function called every time the main window is resized
 * @param[in] width the new window width in pixels
 * @param[in] height the new window height in pixels
 */
void reshape ( int width, int height )
{

    // define the viewport transformation;
    glViewport(0,0,width,height);
    if (width < height)
        glViewport(0,(height-width)/2,width,width);
    else
        glViewport((width-height)/2,0,height,height);
}


/**
 * Function that prints out how to use the keyboard
 */
void usage()
{
    printf ("\n*******\n");
    printf ("Arrows key: rotate the whole robot\n");
    printf ("[a][z] : move the second joint of the arm\n");
    printf ("[e][r] : move the third joint of the arm\n");
    printf ("[o][l] : move the pincers\n"); //!!
    printf ("[esc]  : terminate\n");
    printf ("*******\n");
}


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
    glutKeyboardFunc(keyboard);

    //**********************************
    // Register the special key function
    //**********************************
    glutSpecialFunc(arrows);

    // just print the help
    usage();

    glutMainLoop();

    return EXIT_SUCCESS;
}


