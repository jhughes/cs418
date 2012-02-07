#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "vector.h"

#ifndef PLANE_H
#define PLANE_H

void plane_init();
void planeTimer(int v);
void plane_keyboard(unsigned char key, int x, int y);
void plane_keyboardup(unsigned char key, int x, int y);
void update_view();
void move();
void roll_plane(float roll);
void pitch_plane(float pitch);
Vector3 rotate_point(Vector3 point, Vector3 vector, float theta);
void roll_left();
void roll_right();
void pitch_up();
void pitch_down();

#endif 
