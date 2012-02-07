#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "vector.h"
#ifndef MOUNTAIN_H
#define MOUNTAIN_H

int seed(float x, float y);
void mountain(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float s);
void mountain_init(void);
void mountain_display(void);
void mountain_keyboard(unsigned char key, int x, int y);

#endif
