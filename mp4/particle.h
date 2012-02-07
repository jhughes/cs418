#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "structures.h"

#define GRAVITY -0.5
#define Ks 3.0
#define Kd 0.15
#define FLOOR_LEVEL -0.5
#define FLOOR_DAMP 0.5
#define FRICTION_DAMP 0.1
#define EPSILON 0.03

class Particle {
	public:
		Particle(Vector3* posit);
		void addConnection(Particle* particle);
		void update(float forceX, float forceY, float forceZ);
		void updatePositions();

	private:
		float mass;
		Vector3* position;
		Vector3 velocity;
		Vector3 acceleration;
		Particle** connections;
		Vector3* restLengths;
		int numConnections;
		int connectionsSize;
};

#endif
