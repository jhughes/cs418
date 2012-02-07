#include "helpers.h"

//opens a raw image file and returns a char* pointing to the image data in that file
char* open_raw_image(char* filename, int width, int height) {
	FILE* f = fopen(filename,"rb");
	char* image = (char *)malloc(3*width*height);
	fread(image, 3*width*height, 1, f);
	fclose(f);
	return image;
}

//Find the magnitude of a vector
float magnitude(Vector3* vector) {
	return sqrt(vector->x*vector->x + vector->y*vector->y + vector->z*+vector->z);
}


//Normalizes a vector
void normalize(Vector3* vector) {
	float mag = magnitude(vector);
	vector->x/=mag;
	vector->y/=mag;
	vector->z/=mag;
}

//Calculates the normal vector given 3 vertices.
Vector3 normal(Vertex* vertex0, Vertex* vertex1, Vertex* vertex2) {
	//n = (x1 – x0)x(x2 – x0)
	Vector3 position0 = vertex0->position;
	Vector3 position1 = vertex1->position;
	Vector3 position2 = vertex2->position;
	Vector3 x10 = {position1.x - position0.x, position1.y - position0.y, position1.z - position0.z};
	Vector3 x20 = {position2.x - position0.x, position2.y - position0.y, position2.z - position0.z};
	Vector3 norm = {0,0,0};
	norm.x = x10.y * x20.z - x10.z * x20.y;
	norm.y = x10.z * x20.x - x10.x * x20.z;
	norm.z = x10.x * x20.y - x10.y * x20.x;
	normalize(&norm);
	return norm;
}

