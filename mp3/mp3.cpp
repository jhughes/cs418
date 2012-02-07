#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "objLoader.h"
#include "structures.h"
#include "helpers.h"
#include "teapot.h"
#include "cube.h"

//http://www.kixor.net/dev/objloader/
int FPS = 60;
float fRotateAngle0 = 0.0f;
float fRotateAngle1 = 0.0f;
float fLightRotateAngle0 = 0.0f;
float fLightRotateAngle1 = 0.0f;
//char* vs_filename = "shaders/phong.vs";
//char* fs_filename = "shaders/phong.fs";
bool* key_pressed;

/*
char *loadshader(char *filename)
{
	std::string strbuf;
	std::string line;
	std::ifstream in(filename);
	while(std::getline(in,line))
		strbuf += line + '\n';

	char *buf = (char *)malloc(strbuf.size()*sizeof(char));
	strcpy(buf,strbuf.c_str());

	return buf;
}

void shaders_init(){
	GLint vtx_shader = glCreateShader(GL_VERTEX_SHADER);
	GLint fmt_shader = glCreateShader(GL_FRAGMENT_SHADER);

	GLchar *vertexShaderCodeStr = loadshader(vs_filename);
	const GLchar **vertexShaderCode = (const GLchar **)&vertexShaderCodeStr;

	GLchar *fragmentShaderCodeStr = loadshader(fs_filename);
	const GLchar **fragmentShaderCode = (const GLchar **)&fragmentShaderCodeStr;

	glShaderSource(vtx_shader, 1, vertexShaderCode, 0);
	glCompileShader(vtx_shader);
	glShaderSource(fmt_shader, 1, fragmentShaderCode, 0);
	glCompileShader(fmt_shader);

	GLint shader_program = glCreateProgram();
	glAttachObjectARB(shader_program, vtx_shader);
	glAttachObjectARB(shader_program, fmt_shader);
	glLinkProgram(shader_program);
	glUseProgram(shader_program);
}*/

GLfloat lAmbient[] = {1, 1, 1, 1};
GLfloat lColor[] = {1, 1, 1, 1};
GLfloat lPos[] = {6, 5, 3, 1.0};

void init(void) {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lColor);

    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR); 
    glClearColor(1.0, 0.0, 1.0, 1.0);

	teapot_init(load_cube_textures());
	//shaders_init();
	key_pressed = (bool*)malloc(sizeof(bool) * 256);
	memset(key_pressed, 0, sizeof(bool) * 256);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

	glLoadIdentity ();
	gluLookAt(0.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glRotatef(fLightRotateAngle0, 1.0, 0.0, 0.0);
	glRotatef(fLightRotateAngle1, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, lPos);
	glPopMatrix();

	glRotatef(fRotateAngle0, 1.0, 0.0, 0.0);
	glRotatef(fRotateAngle1, 0.0, 1.0, 0.0);
	glTranslatef(0.0, -1.25, 0.0);

	cube_display();
	teapot_display();

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
float dLightRot = 4.0f;
void timer(int v) {
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
	if(key_pressed[GLUT_KEY_UP - 100]){ // subtract 100 to prevent a conflict with 'D' ASCII
		fLightRotateAngle0 -= dLightRot;
	}
	if(key_pressed[GLUT_KEY_DOWN - 100]){ // subtract 100 to prevent a conflict with 'D' ASCII
		fLightRotateAngle0 += dLightRot;
	}
	if(key_pressed[GLUT_KEY_LEFT - 100]){ // subtract 100 to prevent a conflict with 'D' ASCII
		fLightRotateAngle1 -= dLightRot;
	}
	if(key_pressed[GLUT_KEY_RIGHT - 100]){ // subtract 100 to prevent a conflict with 'D' ASCII
		fLightRotateAngle1 += dLightRot;
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
