#include "mountain.h"
#define MOUNTAIN_LIST 1
/* A slightly modified version of the given mountain.cpp
 *	This version draws the mountain with a display list for increased performance, and changes the materials of the 
 *	mountains and water.  Also doubles the size of the world for a bigger area to fly in.
*/
float sealevel;
float polysize;

int seed(float x, float y) {
    static int a = 1588635695, b = 1117695901;
	int xi = *(int *)&x;
	int yi = *(int *)&y;
    return ((xi * a) % b) - ((yi * b) % a);
}

void mountain(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float s)
{
	float x01,y01,z01,x12,y12,z12,x20,y20,z20;

	if (s < polysize) {
		x01 = x1 - x0;
		y01 = y1 - y0;
		z01 = z1 - z0;

		x12 = x2 - x1;
		y12 = y2 - y1;
		z12 = z2 - z1;

		x20 = x0 - x2;
		y20 = y0 - y2;
		z20 = z0 - z2;

		float nx = y01*(-z20) - (-y20)*z01;
		float ny = z01*(-x20) - (-z20)*x01;
		float nz = x01*(-y20) - (-x20)*y01;

		float den = sqrt(nx*nx + ny*ny + nz*nz);

		if (den > 0.0) {
			nx /= den;
			ny /= den;
			nz /= den;
		}

		glBegin(GL_TRIANGLES);
			glNormal3f(nx,ny,nz);
			glVertex3f(x0,y0,z0);
			glNormal3f(nx,ny,nz);
			glVertex3f(x1,y1,z1);
			glNormal3f(nx,ny,nz);
			glVertex3f(x2,y2,z2);
		glEnd();

		return;
	}

	x01 = 0.5*(x0 + x1);
	y01 = 0.5*(y0 + y1);
	z01 = 0.5*(z0 + z1);

	x12 = 0.5*(x1 + x2);
	y12 = 0.5*(y1 + y2);
	z12 = 0.5*(z1 + z2);

	x20 = 0.5*(x2 + x0);
	y20 = 0.5*(y2 + y0);
	z20 = 0.5*(z2 + z0);

	s /=2;

	srand(seed(x01,y01));
	z01 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
	srand(seed(x12,y12));
	z12 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
	srand(seed(x20,y20));
	z20 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);

	mountain(x0,y0,z0,x01,y01,z01,x20,y20,z20,s);
	mountain(x1,y1,z1,x12,y12,z12,x01,y01,z01,s);
	mountain(x2,y2,z2,x20,y20,z20,x12,y12,z12,s);
	mountain(x01,y01,z01,x12,y12,z12,x20,y20,z20,s);
}

void mountain_init(void) 
{
	sealevel = 0.0;
	polysize = 0.003;
	//create a display list for the mountain so we don't have to recreate it every time.
	glNewList(MOUNTAIN_LIST, GL_COMPILE);
	mountain(0.0,0.0,0.0, 2.0,0.0,0.0, 0.0,2.0,0.0, 2.0);
	mountain(2.0,2.0,0.0, 0.0,2.0,0.0, 2.0,0.0,0.0, 2.0);
   glEndList();
}

void mountain_display(void)
{
	GLfloat tanamb[] = {0.0,0.05,0.0,1.0};
	GLfloat tandiff[] = {0.0,0.2,0.0,1.0};
	GLfloat tanspec[] = {0.0,0.0,0.0,1.0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tanspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);

	glTranslatef(-1,-1,0);
	glCallList(MOUNTAIN_LIST);

	GLfloat seaamb[] = {0.0,0.0,0.2,1.0};
	GLfloat seadiff[] = {0.0,0.0,0.8,1.0};
	GLfloat seaspec[] = {0.2,0.2,0.5,1.0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, seaamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, seadiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, seaspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);

	glNormal3f(0.0,0.0,1.0);
	glBegin(GL_QUADS);
		glVertex3f(0,0,sealevel);
		glVertex3f(2,0,sealevel);
		glVertex3f(2,2,sealevel);
		glVertex3f(0,2,sealevel);
	glEnd();
}

void mountain_keyboard(unsigned char key, int x, int y)
{
   switch (key) {
		case '-':
			sealevel -= 0.01;
			break;
		case '+':
		case '=':
			sealevel += 0.01;
			break;
		default:
			break;
   }
}
