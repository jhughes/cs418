#ifndef HELPERS_H
#define HELPERS_H
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "structures.h"
#include "I.h"

float magnitude(Vector3* vector);
void normalize(Vector3* vector);
Vector3 normal(Vertex* vertex0, Vertex* vertex1, Vertex* vertex2);
Vector3 average2(Vector3 v0, Vector3 v1);
Vector3 average4(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3);
node* listNew(int used);
bool listContains(node* head, int used);
void listAdd(node* head, int used);
void listPrint(node* head);
void listFree(node* head);
void barycenter(int i);
#endif
