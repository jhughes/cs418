#ifndef HELPERS_H
#define HELPERS_H
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "structures.h"

char* open_raw_image(char* filename, int width, int height);
float magnitude(Vector3* vector);
void normalize(Vector3* vector);
Vector3 normal(Vertex* vertex0, Vertex* vertex1, Vertex* vertex2);

#endif
