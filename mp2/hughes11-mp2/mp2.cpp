#include <GL/glut.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include "plane.h"
#include "mountain.h"

int FPS = 60;
float sun = 0; //the position of the sun in radians
float dSun = .01;
float sunsetHeight = 0.5; // the height that sunset/sunrise will start
float radiansToDegrees = 57.2957795; // 180/pi to convert from radians to degrees
GLfloat sunset[] = {1.0,0.8,0.0,1.0}; //sunset color
GLfloat day[] = {0.3, 0.5, 1.0, 1.0}; //day color
GLfloat night[] = {0.01, 0.01, 0.01, 1.0}; //night color


void init(void) 
{
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	//sun light
	glEnable(GL_LIGHT0);
	//moon light
	glEnable(GL_LIGHT1);

	glEnable(GL_DEPTH_TEST);
	plane_init();
	mountain_init();
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);

	//update the plane's camera
	update_view();

	//draw the mountain
	mountain_display();

	//rotate sun and moon
	glRotatef(sun*radiansToDegrees , 0,-1,0);

	//translate and draw sun
	glTranslatef(5,1,0);
	GLfloat sunAmbient[] = {0.5,0.5,0.5,1};
	float sunIntensity = sin(sun)*2;
	GLfloat sunColor[] = {sunIntensity,sunIntensity,sunIntensity*0.8,1};
	GLfloat sunPos[] = {0,0,0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, sunPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sunColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sunColor);
	GLfloat sunamb[] = {1.0,1.0,1.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sunamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sunamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sunamb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);
	glBegin(GL_QUADS);
		glVertex3f(0.0,1.0,1.0);
		glVertex3f(0.0,-1.0,1.0);
		glVertex3f(0.0,-1.0,-1.0);
		glVertex3f(0.0,1.0,-1.0);
	glEnd();

	//translate and draw moon
	glTranslatef(-10,0,0);
	GLfloat moonAmbient[] = {0.5,0.5,0.5,1};
	float moonIntensity = -sin(sun);
	GLfloat moonColor[] = {moonIntensity,moonIntensity,moonIntensity,1};
	GLfloat moonPos[] = {0,0,0,1.0};
	glLightfv(GL_LIGHT1, GL_POSITION, moonPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, moonAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, moonColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, moonColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sunamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sunamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sunamb);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);
	glBegin(GL_QUADS);
		glVertex3f(0.0,0.5,0.5);
		glVertex3f(0.0,-0.5,0.5);
		glVertex3f(0.0,-0.5,-0.5);
		glVertex3f(0.0,0.5,-0.5);
	glEnd();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

//resize the window
void reshape (int w, int h)
{
	float aspectRatio = ((float)w)/h;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(90.0,aspectRatio,0.01,10.0);
	glMatrixMode (GL_MODELVIEW);
}

//sets the clear color base on where the day/night cycle is
void clearColor()
{
	float sunHeight = sin(sun);
	float mix = 0;

	//sunset or sunrise
	if(fabs(sunHeight) < sunsetHeight){
		mix = 1-(fabs(sunHeight)/sunsetHeight);
	}
	//day
	if(sunHeight > 0)
	{
		glClearColor(
			mix*sunset[0] + day[0] * (1-mix), 
			mix*sunset[1] + day[1] * (1-mix),
			mix*sunset[2] + day[2] * (1-mix), 0.0);
	}
	//night
	else
	{
		glClearColor(
			mix*sunset[0] + night[0] * (1-mix), 
			mix*sunset[1] + night[1] * (1-mix),
			mix*sunset[2] + night[2] * (1-mix), 0.0);
	}
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
		case '*'://slow down the day/night cycle
			dSun -= 0.002;
			break;
		case '/'://speed up the day/night cycle
			dSun += 0.002;
			break;
		case 27:
			exit(0);
			break;
   }
	mountain_keyboard(key,x,y);
	plane_keyboard(key,x,y);
}

void keyboardup(unsigned char key, int x, int y)
{
	plane_keyboardup(key,x,y);
}

void timer(int v)
{
	planeTimer(v);
	clearColor();
	sun += dSun;
	glutPostRedisplay(); // trigger display function by sending redraw into message queue
	glutTimerFunc(1000/FPS,timer,v); // restart timer again
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutTimerFunc(100, timer, FPS);
   glutMainLoop();
   return 0;
}
