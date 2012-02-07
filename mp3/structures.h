#ifndef STRUCTURES_H
#define STRUCTURES_H
struct Vector3{
float x;
float y;
float z;
};

struct Vertex{
Vector3 normal;
Vector3 position;
};

struct Face{
	Vertex **vertices;
};

#endif
