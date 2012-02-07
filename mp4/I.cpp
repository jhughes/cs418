#include "I.h"

Vector3 iVertices[] = { 
	{ -0.3f, 0.5f, 0.1f }, //0
	{ -0.1f, 0.5f, 0.1f }, //1
	{ 0.1f, 0.5f, 0.1f },  //2
	{ 0.3f, 0.5f, 0.1f },  //3

   { -0.3f, 0.3f, 0.1f }, //4
	{ -0.1f, 0.3f, 0.1f }, //5	
	{ 0.1f, 0.3f, 0.1f },  //6  
	{ 0.3f, 0.3f, 0.1f },  //7

 	{ -0.1f, 0.1f, 0.1f }, //8
	{ 0.1f, 0.1f, 0.1f },  //9

	{ -0.1f, -0.1f, 0.1f },//10
	{ 0.1f, -0.1f, 0.1f }, //11

	{ -0.3f, -0.3f, 0.1f },//12
	{ -0.1f, -0.3f, 0.1f },//13
	{ 0.1f, -0.3f, 0.1f }, //14
	{ 0.3f, -0.3f, 0.1f }, //15

	{ -0.3f, -0.5f, 0.1f },//16
   { -0.1f, -0.5f, 0.1f },//17
	{ 0.1f, -0.5f, 0.1f }, //18
   { 0.3f, -0.5f, 0.1f },  //19

	{ -0.3f, 0.5f, -0.1f }, //20
	{ -0.1f, 0.5f, -0.1f }, //21
	{ 0.1f, 0.5f, -0.1f },  //22
	{ 0.3f, 0.5f, -0.1f },  //23

   { -0.3f, 0.3f, -0.1f }, //24
	{ -0.1f, 0.3f, -0.1f }, //25	
	{ 0.1f, 0.3f, -0.1f },  //26  
	{ 0.3f, 0.3f, -0.1f },  //27

 	{ -0.1f, 0.1f, -0.1f }, //28
	{ 0.1f, 0.1f, -0.1f },  //29

	{ -0.1f, -0.1f, -0.1f },//30
	{ 0.1f, -0.1f, -0.1f }, //31

	{ -0.3f, -0.3f, -0.1f },//32
	{ -0.1f, -0.3f, -0.1f },//33
	{ 0.1f, -0.3f, -0.1f }, //34
	{ 0.3f, -0.3f, -0.1f }, //35

	{ -0.3f, -0.5f, -0.1f },//36
   { -0.1f, -0.5f, -0.1f },//37
	{ 0.1f, -0.5f, -0.1f }, //38
   { 0.3f, -0.5f, -0.1f }  //39
};

int iFaces[][4] = {
	//front
	{0,4,5,1},//0
	{1,5,6,2},//1
	{2,6,7,3},//2
	{5,8,9,6},//3
	{8,10,11,9},//4
	{10,13,14,11},//5
	{12,16,17,13},//6
	{13,17,18,14},//7
	{14,18,19,15},//8
	//back
	{21,25,24,20},
	{22,26,25,21},
	{23,27,26,22},
	{26,29,28,25},
	{29,31,30,28},
	{31,34,33,30},
	{33,37,36,32},
	{34,38,37,33},
	{35,39,38,34},
	//top depth
	{20,0,1,21},//18
	{21,1,2,22},//19
	{22,2,3,23},//20
	{24,4,0,20},//21
	{23,3,7,27},//22
	{25,5,4,24},//23
	{27,7,6,26},//24
	//mid depth
	{28,8,5,25},//25
	{26,6,9,29},//26
	{30,10,8,28},//27
	{29,9,11,31},//28
	{33,13,10,30},//29
	{31,11,14,34},//30
	//bottom depth
	{32,12,13,33},//31
	{34,14,15,35},//32
	{36,16,12,32},//33
	{35,15,19,39},//34
	{37,17,16,36},//35
	{38,18,17,37},//36
	{39,19,18,38}//37
};

int iFaceNeighbors[][4] = {
	//front
	{21,23,1,18},
	{0,3,2,19},
	{1,24,22,20},
	{25,4,26,1},
	{27,5,28,3},
	{29,7,30,4},
	{33,35,7,31},
	{6,36,8,5},
	{7,37,34,32},
	//back
	{10,23,21,18},
	{11,12,9,19},
	{22,24,10,20},
	{26,13,25,10},
	{28,14,27,12},
	{30,16,29,13},
	{16,35,33,31},
	{17,36,15,14},
	{34,37,16,32},
	//top depth
	{21,0,19,9},
	{18,1,20,10},
	{19,2,22,11},
	{23,0,18,9},
	{20,2,24,11},
	{25,0,21,9},
	{22,2,26,11},
	//mid depth
	{27,3,23,12},//error?
	{24,3,28,12},
	{29,4,25,13},
	{26,4,30,13},
	{31,5,27,14},
	{28,5,32,14},
	//bottom depth
	{33,6,29,15},
	{30,8,34,17},
	{35,6,31,15},
	{32,8,37,17},
	{36,6,33,15},
	{37,7,35,16},
	{34,8,36,17}
};

//unmodified I, for use with physics calculations
Vertex* vertices;
int numVertices;
Face* faces;
int numFaces;

//subdivided I, for displaying
Vertex* subVertices;
int numSubVertices;
Face* subFaces;
int numSubFaces;

void I_init(){
	I_faces_create();
	subFaces = NULL;
	numSubFaces = 0;
	subVertices = NULL;
	numSubVertices = 0;
}

void I_faces_create(){
	//create vertex list
	numVertices = 40;
	vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));
	for(int i = 0; i < numVertices; i++)
	{
		vertices[i].position = iVertices[i];
		vertices[i].numFaces = 0;
	}

	//create face list
	numFaces = 38;
	faces = (Face*)malloc(numFaces * sizeof(Face));
	for(int i = 0; i < numFaces; i++)
	{
		faces[i].vertex0 = iFaces[i][0];
		vertices[iFaces[i][0]].faces[vertices[iFaces[i][0]].numFaces++] = i;

		faces[i].vertex1 = iFaces[i][1];
		vertices[iFaces[i][1]].faces[vertices[iFaces[i][1]].numFaces++] = i;

		faces[i].vertex2 = iFaces[i][2];
		vertices[iFaces[i][2]].faces[vertices[iFaces[i][2]].numFaces++] = i;

		faces[i].vertex3 = iFaces[i][3];
		vertices[iFaces[i][3]].faces[vertices[iFaces[i][3]].numFaces++] = i;

		faces[i].face01 = iFaceNeighbors[i][0];
		faces[i].face12 = iFaceNeighbors[i][1];
		faces[i].face23 = iFaceNeighbors[i][2];
		faces[i].face30 = iFaceNeighbors[i][3];
	}
}

//subdivide wrapper
void I_subdivide(int n){
	//free old subdivided surface
	if(faces != NULL){
		free(faces);
	}
	if(vertices != NULL){
		free(vertices);
	}
	//copy in original I
	I_faces_create();
	//subdivide n times
	for(int i = 0; i < n; i++){
		subdivide();
	}
}

//Subdivide using catmill clark.  Should not be called outside of I_subdivide(int n).
void subdivide(){
	numSubFaces = numFaces*4;
	subFaces = (Face*) malloc(numSubFaces * sizeof(Face));
	numSubVertices = numSubFaces*4;
	subVertices = (Vertex*) malloc(numSubVertices * sizeof(Vertex));
	memcpy(subVertices, vertices, numVertices * sizeof(Vertex));
	int usedVertices = numVertices;

	for(int i = 0; i < numFaces; i++) {
		faces[i].vertex01 = -1;
		faces[i].vertex12 = -1;
		faces[i].vertex23 = -1;
		faces[i].vertex30 = -1;
	}

	//calculate face points for each face.
	for(int i = 0; i < numFaces; i++) {
		//centroid
		subVertices[usedVertices].position = average4(subVertices[faces[i].vertex0].position, subVertices[faces[i].vertex1].position, subVertices[faces[i].vertex2].position, subVertices[faces[i].vertex3].position);
		faces[i].centroid = usedVertices;
		usedVertices++;

	}

	//calculate edge points.
	for(int i = 0; i < numFaces; i++) {
		// 0 1
		if(faces[i].vertex01 == -1){
			subVertices[usedVertices].position = average4(subVertices[faces[i].vertex0].position, subVertices[faces[i].vertex1].position, subVertices[faces[i].centroid].position, subVertices[faces[faces[i].face01].centroid].position);
			faces[i].vertex01 = usedVertices;
			usedVertices++;
		}
		// 1 2
		if(faces[i].vertex12 == -1){
			subVertices[usedVertices].position = average4(subVertices[faces[i].vertex1].position, subVertices[faces[i].vertex2].position, subVertices[faces[i].centroid].position, subVertices[faces[faces[i].face12].centroid].position);
			faces[i].vertex12 = usedVertices;
			usedVertices++;
		}
		// 2 3
		if(faces[i].vertex23 == -1){
			subVertices[usedVertices].position = average4(subVertices[faces[i].vertex2].position, subVertices[faces[i].vertex3].position, subVertices[faces[i].centroid].position, subVertices[faces[faces[i].face23].centroid].position);
			faces[i].vertex23 = usedVertices;
			usedVertices++;
		}
		// 3 0
		if(faces[i].vertex30 == -1){
			subVertices[usedVertices].position = average4(subVertices[faces[i].vertex3].position, subVertices[faces[i].vertex0].position, subVertices[faces[i].centroid].position, subVertices[faces[faces[i].face30].centroid].position);
			faces[i].vertex30 = usedVertices;
			usedVertices++;
		}
	}

	//For each face point, add an edge for every edge of the face, connecting the face point to each edge point for the face.
	for(int i = 0; i < numFaces; i++){
		subFaces[4*i+0].vertex0 = faces[i].vertex0;
		subFaces[4*i+0].vertex1 = faces[i].vertex01;
		subFaces[4*i+0].vertex2 = faces[i].centroid;
		subFaces[4*i+0].vertex3 = faces[i].vertex30;

		subFaces[4*i+1].vertex0 = faces[i].vertex01;
		subFaces[4*i+1].vertex1 = faces[i].vertex1;
		subFaces[4*i+1].vertex2 = faces[i].vertex12;
		subFaces[4*i+1].vertex3 = faces[i].centroid;

		subFaces[4*i+2].vertex0 = faces[i].centroid;
		subFaces[4*i+2].vertex1 = faces[i].vertex12;
		subFaces[4*i+2].vertex2 = faces[i].vertex2;
		subFaces[4*i+2].vertex3 = faces[i].vertex23;

		subFaces[4*i+3].vertex0 = faces[i].vertex30;
		subFaces[4*i+3].vertex1 = faces[i].centroid;
		subFaces[4*i+3].vertex2 = faces[i].vertex23;
		subFaces[4*i+3].vertex3 = faces[i].vertex3;
	}

	// For each original point P, take the average F of all n face points for faces touching P, and take the average R of all n edge midpoints for edges touching P, where each edge midpoint is the average of its two endpoint vertices. Move each original point to the point
	for(int i = 0; i < numVertices; i++){
		barycenter(i);
	}

	//reassemble face->face pointers and vertex->face pointers
	for(int i = 0; i < numFaces; i++){
		//centroids
		/*subVertices[faces[i].centroid].faces[subVertices[faces[i].centroid].numFaces++] = 4*i+0;
		subVertices[faces[i].centroid].faces[subVertices[faces[i].centroid].numFaces++] = 4*i+1;
		subVertices[faces[i].centroid].faces[subVertices[faces[i].centroid].numFaces++] = 4*i+2;
		subVertices[faces[i].centroid].faces[subVertices[faces[i].centroid].numFaces++] = 4*i+3;
		//edges
		subVertices[subFaces[4*i+0].vertex0].faces[subVertices[subFaces[4*i+0].vertex0].numFaces++] = 4*i+0;
		subVertices[subFaces[4*i+0].vertex1].faces[subVertices[subFaces[4*i+0].vertex1].numFaces++] = 4*i+0;
		subVertices[subFaces[4*i+0].vertex2].faces[subVertices[subFaces[4*i+0].vertex2].numFaces++] = 4*i+0;
		subVertices[subFaces[4*i+0].vertex3].faces[subVertices[subFaces[4*i+0].vertex3].numFaces++] = 4*i+0;
		subVertices[subFaces[4*i+1].vertex0].faces[subVertices[subFaces[4*i+1].vertex0].numFaces++] = 4*i+1;
		subVertices[subFaces[4*i+1].vertex1].faces[subVertices[subFaces[4*i+1].vertex1].numFaces++] = 4*i+1;
		subVertices[subFaces[4*i+1].vertex2].faces[subVertices[subFaces[4*i+1].vertex2].numFaces++] = 4*i+1;
		subVertices[subFaces[4*i+1].vertex3].faces[subVertices[subFaces[4*i+1].vertex3].numFaces++] = 4*i+1;
		subVertices[subFaces[4*i+2].vertex0].faces[subVertices[subFaces[4*i+2].vertex0].numFaces++] = 4*i+2;
		subVertices[subFaces[4*i+2].vertex1].faces[subVertices[subFaces[4*i+2].vertex1].numFaces++] = 4*i+2;
		subVertices[subFaces[4*i+2].vertex2].faces[subVertices[subFaces[4*i+2].vertex2].numFaces++] = 4*i+2;
		subVertices[subFaces[4*i+2].vertex3].faces[subVertices[subFaces[4*i+2].vertex3].numFaces++] = 4*i+2;
		subVertices[subFaces[4*i+3].vertex0].faces[subVertices[subFaces[4*i+3].vertex0].numFaces++] = 4*i+3;
		subVertices[subFaces[4*i+3].vertex1].faces[subVertices[subFaces[4*i+3].vertex1].numFaces++] = 4*i+3;
		subVertices[subFaces[4*i+3].vertex2].faces[subVertices[subFaces[4*i+3].vertex2].numFaces++] = 4*i+3;
		subVertices[subFaces[4*i+3].vertex3].faces[subVertices[subFaces[4*i+3].vertex3].numFaces++] = 4*i+3;*/

		//0
		subFaces[4*i+0].face01 = 4*(faces[i].face01)+3;
		subFaces[4*i+0].face12 = 4*i+1;
		subFaces[4*i+0].face23 = 4*i+3;
		subFaces[4*i+0].face30 = 4*(faces[i].face30)+1;
		//1
		subFaces[4*i+1].face01 = 4*(faces[i].face01)+2;
		subFaces[4*i+1].face12 = 4*(faces[i].face12)+0;
		subFaces[4*i+1].face23 = 4*i+2;
		subFaces[4*i+1].face30 = 4*i+0;
		//2
		subFaces[4*i+2].face01 = 4*i+1;
		subFaces[4*i+2].face12 = 4*(faces[i].face12)+3;
		subFaces[4*i+2].face23 = 4*(faces[i].face23)+1;
		subFaces[4*i+2].face30 = 4*i+3;
		//3
		subFaces[4*i+3].face01 = 4*i+0;
		subFaces[4*i+3].face12 = 4*i+2;
		subFaces[4*i+3].face23 = 4*(faces[i].face23)+0;
		subFaces[4*i+3].face30 = 4*(faces[i].face30)+2;
	}

	//finished. copy data to original pointers
	free(vertices);
	free(faces);
	vertices = subVertices;
	faces = subFaces;
	numVertices = numSubVertices;
	numFaces = numSubFaces;
}

//Display the I.
void I_display(){
if(faces != NULL){
	Vector3 vert;
   for (int i = 0; i < numFaces; i++) {
			glColor3f(1.0* (i/(float)numFaces), 0.5* (i/(float)numFaces), 1.0* (1-(i/(float)numFaces)));
			glBegin(GL_QUADS);
			//printf("QUAD %d:\n", i);
			vert = vertices[faces[i].vertex0].position;
			glVertex3f(vert.x, vert.y, vert.z);
			//printf("vert0 %d: %f %f %f\n", faces[i].vertex0, vert.x, vert.y, vert.z);
			vert = vertices[faces[i].vertex1].position;
			glVertex3f(vert.x, vert.y, vert.z);
			//printf("vert1 %d: %f %f %f\n", faces[i].vertex1, vert.x, vert.y, vert.z);
			vert = vertices[faces[i].vertex2].position;
			glVertex3f(vert.x, vert.y, vert.z);
			//printf("vert2 %d: %f %f %f\n", faces[i].vertex2, vert.x, vert.y, vert.z);
			vert = vertices[faces[i].vertex3].position;
			glVertex3f(vert.x, vert.y, vert.z);
			//printf("vert3 %d: %f %f %f\n", faces[i].vertex3, vert.x, vert.y, vert.z);
			glEnd();
	   }
	}
}

