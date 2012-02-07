#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Vector3 Vector3;
typedef struct Vertex Vertex;
typedef struct Face Face;
typedef struct node node;

struct node{
	int used;
	node* next;
};

struct Vector3{
	float x;
	float y;
	float z;
};

struct Vertex{
	Vector3 position;
	Vector3 normal;
	int numFaces;
	int faces[5];
};

struct Face{
	//the 4 vertices of the quad face
	int vertex0;
	int vertex1;
	int vertex2;
	int vertex3;
	//centroid of the quad face (average of 4 vertices)
	int centroid;
	//the edge midpoints
	int vertex01;
	int vertex12;
	int vertex23;
	int vertex30;
	//the faces connected to each edge
	int face01;
	int face12;
	int face23;
	int face30;
};
#endif
