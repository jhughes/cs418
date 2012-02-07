#include "particle.h"

/*Treat the vertices of your (coarse) mesh as particles, and create a gravity force and spring forces on the particles, using Euler integration to simulate the motion.

    * The gravity force should apply to all particles. If all particles weight the same, then this force can simply be a vector pointing down.
    * The spring force acts between any two particles connected by a spring. The rest length of the spring should be the distance between the particles (vertices) when the mesh is in its desired shape. The spring force is F = -k (||a - b|| - r) where a and b are the positions of the two particles, r is the rest length of the spring, and k is the spring constant. Start with k very small, making it larger makes your springs stiffer but can also make your integration unstable. Experiment. There should be a spring for every edge in the mesh, and you should add diagonal springs as well to keep the I from collapsing.
    * Keep track of the position x and velocity v of each particle. Then Euler integration is just x += epsilon * v and v += epsilon F/m, and you can ignore mass if all the particles weigh the same. Your step size epsilon should start very small. Making it bigger will produce more motion but may also cause instability. Experiment. */

Particle::Particle(Vector3* posit) {
	position = posit;
	mass = 1;
	velocity = (Vector3){0.0f,0.0f,0.0f};
	acceleration = (Vector3){0.0f, GRAVITY, 0.0f};
	numConnections = 0;
	connectionsSize = 5;
	connections = (Particle**) malloc(connectionsSize * sizeof(Particle*));
	restLengths = (Vector3*) malloc(connectionsSize * sizeof(Vector3));
}

void Particle::addConnection(Particle* particle){
	if(numConnections == connectionsSize){
		connectionsSize*=2;
		connections = (Particle**) realloc(connections, connectionsSize * sizeof(Particle*));
		restLengths = (Vector3*) realloc(restLengths, connectionsSize * sizeof(Vector3));
	}
	float x = particle->position->x - position->x;
	float y = particle->position->y - position->y;
	float z = particle->position->z - position->z;
	restLengths[numConnections].x = fabs(x);
	restLengths[numConnections].y = fabs(y);
	restLengths[numConnections].z = fabs(z);

	connections[numConnections] = particle;
	numConnections++;
}

void Particle::update(float forceX, float forceY, float forceZ) {
	//find force
	Vector3 force = (Vector3){forceX,forceY,forceZ};
	float xamxb, yamyb, zamzb;
	float fx = 0, fy = 0, fz = 0;
	for(int i = 0; i < numConnections; i++){
		xamxb = position->x - connections[i]->position->x;
		yamyb = position->y - connections[i]->position->y;
		zamzb = position->z - connections[i]->position->z;
		if(xamxb != 0.0)
			fx = -(Ks * (fabs(xamxb) - restLengths[i].x) + Kd * (velocity.x - connections[i]->velocity.x) * (xamxb/fabs(xamxb))) * (xamxb/fabs(xamxb));
		else
			fx = 0;
		if(yamyb != 0.0)
			fy = -(Ks * (fabs(yamyb) - restLengths[i].y) + Kd * (velocity.y - connections[i]->velocity.y) * (yamyb/fabs(yamyb))) * (yamyb/fabs(yamyb));
		else
			fy = 0;
		if(zamzb != 0.0)
			fz = -(Ks * (fabs(zamzb) - restLengths[i].z) + Kd * (velocity.z - connections[i]->velocity.z) * (zamzb/fabs(zamzb))) * (zamzb/fabs(zamzb));
		else
			fz = 0;

		force.x += fx;
		force.y += fy;
		force.z += fz;
	}
	//update acceleraton
	acceleration.x = force.x/mass;
	acceleration.y = force.y/mass + GRAVITY;
	acceleration.z = force.z/mass;
	//update velocity
	velocity.x += acceleration.x * EPSILON;
	velocity.y += acceleration.y * EPSILON;
	velocity.z += acceleration.z * EPSILON;
}

void Particle::updatePositions(){
	//update position
	position->x += velocity.x * EPSILON;
	position->y += velocity.y * EPSILON;
	position->z += velocity.z * EPSILON;

	//printf("y: %f\n", position->y);
	if(position->y < FLOOR_LEVEL){
		position->y = FLOOR_LEVEL;
		velocity.y = -velocity.y * FLOOR_DAMP;
		velocity.x = -velocity.x * FRICTION_DAMP;
		velocity.z = -velocity.z * FRICTION_DAMP;
	}
}
