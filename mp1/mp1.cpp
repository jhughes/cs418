//  
// Example code for OpenGL programming
//
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "heart.cpp"
#include "I.cpp"


int FPS = 30;
float iRotateAngle = 0.f;
bool wireframe = false;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	drawHeart();

	//translate and rotate the I
	glRotatef(iRotateAngle,0.f,0.f,1.f);
	glTranslatef(0.5,0.f,0.f);

	drawI();

        glFlush();	
	glutSwapBuffers();	// swap front/back framebuffer to avoid flickering 
}

void mouse(int button, int state, int x, int y)
{
	// If the right mouse button is down, toggle wireframe
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		wireframe = !wireframe;
		if(wireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}


void timer(int v)
{
	glutPostRedisplay(); // trigger display function by sending redraw into message queue
	colorRotation += 0.01f;
	iRotateAngle += 1.0f;
	dance += 0.1f;
	glutTimerFunc(1000/FPS,timer,v); // restart timer again
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	// set up for double-buffering & RGB color buffer & depth test
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow ((const char*)"mp1");
	glClearColor(0,0,0,1.0); // clear color is black	
	
	// set up the call-back functions 
	glutDisplayFunc(display);  // called when drawing 
	glutMouseFunc(mouse);	    // called when received mouse interaction
	glutTimerFunc(100,timer,FPS); // a periodic timer. Usually used for updating animation
	
	glutMainLoop(); // start the main message-callback loop

	return 0;
}

