#ifndef TEAPOT_H
#define TEAPOT_H
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "objLoader.h"
#include "structures.h"
#include "helpers.h"

void texture_map_init();
void teapot_init(GLuint cubemap);

void texture_map_on();
void cube_map_on();
void texture_combine();
void teapot_display();
void teapot_keyboard(unsigned char key, int x, int y);

void teapot_load();
void teapot_create_display_list();
#endif
