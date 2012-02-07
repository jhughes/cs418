#ifndef I_H
#define I_H
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

//unmodified I, for use with physics calculations
extern Vertex* vertices;
extern int numVertices;
extern Face* faces;
extern int numFaces;

//subdivided I, for displaying
extern Vertex* subVertices;
extern int numSubVertices;
extern Face* subFaces;
extern int numSubFaces;

extern Vector3 iVertices[];
extern int iFaces[][4];

void I_init();
void I_faces_create();
void I_subdivide(int n);
void I_display();
void subdivide();

#endif
