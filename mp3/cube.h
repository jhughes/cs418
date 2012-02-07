#ifndef CUBE_H
#define CUBE_H
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "helpers.h"
#include "structures.h"

GLuint load_cube_textures();
void cube_display();
#endif
