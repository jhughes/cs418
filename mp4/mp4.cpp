#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

#include "I.h"
#include "structures.h"
#include "helpers.h"
#include "particle.h"

int FPS = 120;
float fRotateAngle0 = 0.0f;
float fRotateAngle1 = 0.0f;
float forceY = 0.0f;
float forceX = 0.0f;
float forceZ = 0.0f;

bool* key_pressed;

GLfloat lAmbient[] = {1, 1, 1, 1};
GLfloat lColor[] = {1, 1, 1, 1};
GLfloat lPos[] = {6, 5, 3, 1.0};

Particle* particles[40];

//Bezier curve
Vector3 cameraPath[4];
Vector3 B;
float t;
int pointsUsed;

#define CAMERA_DISTANCE 1.5
#define CAMERA_HEIGHT 0.15

void init(void) {
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
   //glEnable(GL_LIGHTING);
   //glEnable(GL_LIGHT0);

	//glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lColor);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lColor);

    //glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR); 
    glClearColor(0.1, 0.1, 0.1, 1.0);

	//set particles to vertices of the I.
	for(int i = 0; i<40; i++){
		particles[i] = new Particle(&iVertices[i]);
	}

	//connect each particle to every other particle in the faces it's part of.
	for(int i = 0; i < 38; i++)
	{
		for(int j = 0; j < 4; j++){
			particles[iFaces[i][0]]->addConnection(particles[iFaces[i][1]]);
			particles[iFaces[i][0]]->addConnection(particles[iFaces[i][2]]);
			particles[iFaces[i][0]]->addConnection(particles[iFaces[i][3]]);
			particles[iFaces[i][1]]->addConnection(particles[iFaces[i][0]]);
			particles[iFaces[i][1]]->addConnection(particles[iFaces[i][2]]);
			particles[iFaces[i][1]]->addConnection(particles[iFaces[i][3]]);
			particles[iFaces[i][2]]->addConnection(particles[iFaces[i][0]]);
			particles[iFaces[i][2]]->addConnection(particles[iFaces[i][1]]);
			particles[iFaces[i][2]]->addConnection(particles[iFaces[i][3]]);
			particles[iFaces[i][3]]->addConnection(particles[iFaces[i][0]]);
			particles[iFaces[i][3]]->addConnection(particles[iFaces[i][1]]);
			particles[iFaces[i][3]]->addConnection(particles[iFaces[i][2]]);
		}
	}

	cameraPath[0] = (Vector3){0.0, CAMERA_HEIGHT, CAMERA_DISTANCE};
	cameraPath[1] = (Vector3){CAMERA_DISTANCE, CAMERA_HEIGHT, 0.0};
	cameraPath[2] = (Vector3){0.0, CAMERA_HEIGHT, -CAMERA_DISTANCE};
	cameraPath[3] = (Vector3){-CAMERA_DISTANCE, CAMERA_HEIGHT, 0.0};
	t = 0;
	pointsUsed = 0;

	I_init();

	key_pressed = (bool*)malloc(sizeof(bool) * 256);
	memset(key_pressed, 0, sizeof(bool) * 256);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(B.x, B.y, B.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(fRotateAngle0, 1, 0, 0);
	glRotatef(fRotateAngle1, 0, 1, 0);

	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glVertex3f(-10, FLOOR_LEVEL, -10);
	glVertex3f(-10, FLOOR_LEVEL, 10);
	glVertex3f(10, FLOOR_LEVEL, 10);
	glVertex3f(10, FLOOR_LEVEL, -10);
	glEnd();

	I_display();

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    float aspectRatio = ((float) w) / h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, aspectRatio, 0.01, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	key_pressed[key] = true;
}

void keyboardup(unsigned char key, int x, int y) {
	key_pressed[key] = false;
}

void specialkeyboard(int key, int x, int y) {
	if(key >= 100 && key < 104)
		key_pressed[key-100] = true; // subtract 100 to prevent a conflict with 'D' ASCII
}

void specialkeyboardup(int key, int x, int y) {
	if(key >= 100 && key < 104)
		key_pressed[key-100] = false; // subtract 100 to prevent a conflict with 'D' ASCII
}

float dRot = 2.0f;
float dForce = 10.0f;
float dT = 0.001f;
float getRand(){
	float ran = (-0.5 + rand()/(float)RAND_MAX) * 0.8;
	return ran;
}

void timer(int v) {
	t+=dT;
	if(t > 1){
		t -= 1;
		Vector3 newPath[4];
		newPath[0] = cameraPath[3];
		
		//attempting c2 continuity
		//how does it work?
		/*newPath[1] = (Vector3){
			cameraPath[3].x - cameraPath[2].x + newPath[0].x, 
			0.25, 
			cameraPath[3].z - cameraPath[2].z + newPath[0].z};
		newPath[2] = (Vector3){
			cameraPath[3].x - 2*cameraPath[2].x + cameraPath[1].x - newPath[0].x + 2*newPath[1].x,
			0.25, 
			cameraPath[3].z - 2*cameraPath[2].z + cameraPath[1].z - newPath[0].z + 2*newPath[1].z};*/
		if(pointsUsed % 4 == 0){
			newPath[1] = (Vector3){0.0+getRand(), CAMERA_HEIGHT+getRand(), CAMERA_DISTANCE+getRand()};
			newPath[2] = (Vector3){CAMERA_DISTANCE+getRand(), CAMERA_HEIGHT+getRand(), 0.0+getRand()};
			newPath[3] = (Vector3){0.0+getRand(), CAMERA_HEIGHT+getRand(), -CAMERA_DISTANCE+getRand()};
		}
		else if(pointsUsed % 4 == 1){
			newPath[1] = (Vector3){-CAMERA_DISTANCE+getRand(), CAMERA_HEIGHT+getRand(), 0.0+getRand()};
			newPath[2] = (Vector3){0.0+getRand(), CAMERA_HEIGHT+getRand(), CAMERA_DISTANCE+getRand()};
			newPath[3] = (Vector3){CAMERA_DISTANCE+getRand(), CAMERA_HEIGHT+getRand(), 0.0+getRand()};
		}
		else if(pointsUsed % 4 == 2){
			newPath[1] = (Vector3){0.0+getRand(), CAMERA_HEIGHT+getRand(), -CAMERA_DISTANCE+getRand()};
			newPath[2] = (Vector3){-CAMERA_DISTANCE+getRand(), CAMERA_HEIGHT+getRand(), 0.0+getRand()};
			newPath[3] = (Vector3){0.0+getRand(), CAMERA_HEIGHT+getRand(), CAMERA_DISTANCE+getRand()};
		}
		else if(pointsUsed % 4 == 3){
			newPath[1] = (Vector3){CAMERA_DISTANCE+getRand(), CAMERA_HEIGHT+getRand(), 0.0+getRand()};
			newPath[2] = (Vector3){0.0+getRand(), CAMERA_HEIGHT+getRand(), -CAMERA_DISTANCE+getRand()};
			newPath[3] = (Vector3){-CAMERA_DISTANCE+getRand(), CAMERA_HEIGHT+getRand(), 0.0+getRand()};
		}
		for(int i = 0; i < 4; i++)
		{
			cameraPath[i] = newPath[i];
		}
		pointsUsed++;
	}
	B.x = 
		(1.0 - t)*(1.0 - t)*(1.0 - t)*cameraPath[0].x + 
		3 * (1.0 - t)*(1.0 - t)*t*cameraPath[1].x + 
		3 * (1.0 - t)*t*t*cameraPath[2].x +
		t*t*t*cameraPath[3].x;
	B.y = 
		(1.0 - t)*(1.0 - t)*(1.0 - t)*cameraPath[0].y + 
		3 * (1.0 - t)*(1.0 - t)*t*cameraPath[1].y + 
		3 * (1.0 - t)*t*t*cameraPath[2].y +
		t*t*t*cameraPath[3].y;
	B.z = 
		(1.0 - t)*(1.0 - t)*(1.0 - t)*cameraPath[0].z + 
		3 * (1.0 - t)*(1.0 - t)*t*cameraPath[1].z + 
		3 * (1.0 - t)*t*t*cameraPath[2].z +
		t*t*t*cameraPath[3].z;
	forceY = 0;
	forceX = 0;
	forceZ = 0;
	if(key_pressed['w']){
		fRotateAngle0 -= dRot;
	}
	if(key_pressed['s']){
		fRotateAngle0 += dRot;
	}
	if(key_pressed['a']){
		fRotateAngle1 -= dRot;
	}
	if(key_pressed['d']){
		fRotateAngle1 += dRot;
	}
	if(key_pressed['q']){ // subtract 100 to prevent a conflict with 'D' ASCII
		key_pressed['q'] = false;
		forceY -= dForce;
	}
	if(key_pressed['e']){ // subtract 100 to prevent a conflict with 'D' ASCII
		key_pressed['e'] = false;
		forceY += dForce;
	}
	if(key_pressed[GLUT_KEY_UP - 100]){ // subtract 100 to prevent a conflict with 'D' ASCII
		key_pressed[GLUT_KEY_UP - 100] = false;
		forceZ -= dForce;
	}
	if(key_pressed[GLUT_KEY_DOWN - 100]){ // subtract 100 to prevent a conflict with 'D' ASCII
		key_pressed[GLUT_KEY_DOWN - 100] = false;
		forceZ += dForce;
	}
	if(key_pressed[GLUT_KEY_LEFT - 100]){ // subtract 100 to prevent a conflict with 'D' ASCII
		key_pressed[GLUT_KEY_LEFT - 100] = false;
		forceX -= dForce;
	}
	if(key_pressed[GLUT_KEY_RIGHT - 100]){ // subtract 100 to prevent a conflict with 'D' ASCII
		key_pressed[GLUT_KEY_RIGHT - 100] = false;
		forceX += dForce;
	}
	for(int i = 0; i<40; i++){
		particles[i]->update(forceX, forceY, forceZ);
	}
	for(int i = 0; i<40; i++){
		particles[i]->updatePositions();
	}
	if(key_pressed[' ']){
		I_subdivide(1);
	}
	else{
		I_faces_create();
	}
    glutPostRedisplay(); // trigger display function by sending redraw into message queue
    glutTimerFunc(1000 / FPS, timer, v); // restart timer again
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 0);
    glutCreateWindow(argv[0]);
	glewInit();
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutSpecialFunc(specialkeyboard);
	glutSpecialUpFunc(specialkeyboardup);
    glutTimerFunc(100, timer, FPS);
    glutMainLoop();
    return 0;
}
