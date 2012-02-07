#include "helpers.h"
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

//averages 2 Vectors together.
Vector3 average2(Vector3 v0, Vector3 v1){
	Vector3 avg;
	avg.x = (v0.x + v1.x) / 2.0;
	avg.y = (v0.y + v1.y) / 2.0;
	avg.z = (v0.z + v1.z) / 2.0;
	return avg;
}

//averages 4 Vectors together
Vector3 average4(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3){
	Vector3 avg;
	avg.x = (v0.x + v1.x + v2.x + v3.x) / 4.0;
	avg.y = (v0.y + v1.y + v2.y + v3.y) / 4.0;
	avg.z = (v0.z + v1.z + v2.z + v3.z) / 4.0;
	return avg;
}

node* listNew(int used){
	node* head;
	head = (node*)malloc(sizeof(node));
	head->next = NULL;
	head->used = used;
	return head;
}

bool listContains(node* head, int used){
	if(head == NULL)
		return false;
	if(head->used == used)
		return true;
	return listContains(head->next, used);
}

void listAdd(node* head, int used){
	if(head->next == NULL){
		head->next = (node*)malloc(sizeof(node));
		head->next->used = used;
		head->next->next = NULL;
		return;
	}
	listAdd(head->next, used);
}

void listPrint(node* head){
	if(head == NULL){
		printf("\n");
		return;
	}
	printf("%d,\n", head->used);
	listPrint(head->next);
}

void listFree(node* head){
	if(head == NULL)
		return;
	listFree(head->next);
	free(head);
}

	// For each original point P, take the average F of all n face points for faces touching P, and take the average R of all n edge midpoints for edges touching P, where each edge midpoint is the average of its two endpoint vertices. Move each original point to the point
void barycenter(int i){
	Vertex* P = &subVertices[i];
	int n = P->numFaces;
	Vector3 F = {0,0,0};
	Vector3 R = {0,0,0};
	node* list = listNew(-1); //list to keep track of which edge midpoints have been used

	//face points
	for(int j = 0; j < n; j++){
		Vector3 pos = subVertices[faces[P->faces[j]].centroid].position;
		F.x += pos.x;
		F.y += pos.y;
		F.z += pos.z;
	}
	F.x /= n;
	F.y /= n;
	F.z /= n;

	//edge midpoints
	for(int j = 0; j < n; j++){
		int po1;//potential edge values to add to R
		// 0
		Face face = faces[P->faces[j]];
		//printf("Face %d: %d %d %d %d\n", P->faces[j], face.vertex0, face.vertex1, face.vertex2, face.vertex3);
		if(face.vertex0 == i){
			po1 = face.vertex01;
		}
		// 1
		else if(face.vertex1 == i){
			po1 = face.vertex12;
		}
		// 2
		else if(face.vertex2 == i){
			po1 = face.vertex23;
		}
		// 3
		else if(face.vertex3 == i){
			po1 = face.vertex30;
		}

		//check potentials
		if(!listContains(list, po1)){
			listAdd(list, po1);
			R.x += subVertices[po1].position.x;
			R.y += subVertices[po1].position.y;
			R.z += subVertices[po1].position.z;
			//printf("po1: %f %f %f\n", subVertices[po1].position.x, subVertices[po1].position.y, subVertices[po1].position.z);
		}
	}
	//listPrint(list);
	listFree(list);
	R.x /= n;
	R.y /= n;
	R.z /= n;
	
	P->position.x = (F.x + 2*R.x + (n-3)*P->position.x) / n;
	P->position.y = (F.y + 2*R.y + (n-3)*P->position.y) / n;
	P->position.z = (F.z + 2*R.z + (n-3)*P->position.z) / n;
}
