#include "teapot.h"
#define TEAPOT_LIST 1
#define PI 3.141509

int numFaces;
int numVertices;
Face* faces;
Vertex* vertices;
GLuint cube_map2;
GLuint texture;

GLfloat potamb[] = {0.4, 0.4, 0.6, 1.0};
GLfloat potdiff[] = {0.8, 0.8, 1.0, 1.0};
GLfloat potspec[] = {0.8, 0.8, 1.0, 1.0};

char* teapot_loc = "teapot.obj";
char* texture_filename = "textures/texture.raw";

//Initializes the texture map
void texture_map_init(){
	int image_width = 512;
	int image_height = 512;
	char* image = open_raw_image(texture_filename,image_width,image_height);

	// allocate a texture name
	glGenTextures( 1, &texture );
	// select our current texture
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexImage2D (GL_TEXTURE_2D, 0, 3, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	free(image);
}

//Initializes the teapot.
void teapot_init(GLuint cubemap) {
	cube_map2 = cubemap;
    teapot_load();
    teapot_create_display_list();
	texture_map_init();
}

//turns on the texture map
void texture_map_on() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
}

//turns on the cube map
void cube_map_on() {
	glEnable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map2);
}

//blends the texture and cubemaps together
void texture_combine() {
	glActiveTexture(GL_TEXTURE0);
		texture_map_on();
	//Simply sample the texture
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//------------------------
	glActiveTexture(GL_TEXTURE1);
		cube_map_on();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	//Sample RGB, multiply by previous texunit result
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);   //Modulate RGB with RGB
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
	glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
}

//displays the teapot
void teapot_display() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
    glColor3f(1.0, 1.0, 1.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, potamb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, potdiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, potspec);
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0);

	texture_combine();
    glCallList(TEAPOT_LIST);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glPopAttrib();
}

// Loads the teapot from .obj file and converts it into arrays of faces and vertices
void teapot_load() {
    objLoader *objData = new objLoader();
    objData->load(teapot_loc);

    numFaces = objData->faceCount;
    numVertices = objData->vertexCount;
    faces = (Face*) malloc(numFaces * sizeof (Face)); //need to free
    vertices = (Vertex*) malloc(numVertices * sizeof (Vertex)); //need to free

    //set all vertices
    for (int i = 0; i < numVertices; i++) {
        vertices[i].position.x = (*(objData->vertexList[i])).e[0];
        vertices[i].position.y = (*(objData->vertexList[i])).e[1];
        vertices[i].position.z = (*(objData->vertexList[i])).e[2];
    }
    //set all faces
    for (int i = 0; i < numFaces; i++) {
        obj_face* face = objData->faceList[i];
        int vertex_count = face->vertex_count;
        faces[i].vertices = (Vertex**) malloc(vertex_count * sizeof (Vertex*)); //need to free
        for (int j = 0; j < vertex_count; j++) {
            faces[i].vertices[j] = &vertices[face->vertex_index[j]];
        }
        //calculate norm vector for each face
        Vector3 norm = normal(faces[i].vertices[0], faces[i].vertices[1], faces[i].vertices[2]);
        //add norm vector to each vertex norm vector
        for (int j = 0; j < vertex_count; j++) {
            faces[i].vertices[j]->normal.x += norm.x;
            faces[i].vertices[j]->normal.y += norm.y;
            faces[i].vertices[j]->normal.z += norm.z;
        }
    }
    //normalize all vertices norm vector
    for (int i = 0; i < numVertices; i++) {
        normalize(&vertices[i].normal);
    }
    delete(objData);
}

//Creates a display list out of the faces and vertices
void teapot_create_display_list() {
    glNewList(TEAPOT_LIST, GL_COMPILE);
    glBegin(GL_TRIANGLES);
	Vector3 norm;
	Vector3 vert;
	float theta;
	float thetamin;
	float thetamax;
	//for each vertex on a face specify texture coord and normal vector
    for (int i = 0; i < numFaces; i++) {
		thetamin = 0;
		thetamax = 0;
		//do this to make the texture wrap around with cylindrical coords
		for (int j = 0; j < 3; j++) {
			vert = faces[i].vertices[j]->position;
			theta = atan2(vert.z,vert.x);
			if(theta > thetamax){
				thetamax = theta;
			}
			if(theta < thetamin){			
				thetamin = theta;
			}
		}
		for (int j = 0; j < 3; j++) {
        norm = faces[i].vertices[j]->normal;
        vert = faces[i].vertices[j]->position;
			theta = atan2(vert.z,vert.x);
			if(thetamax > PI - 1 && thetamin < -PI + 1) {
				if(theta < thetamin + 1){ 
					theta += 2*PI;
				}
			}
			glTexCoord2f(theta/3, vert.y/3); //cylindrical coords
			//glTexCoord2f(vert.x/5, vert.y/5); //orthographic rectangular coords
			glNormal3f(norm.x, norm.y, norm.z);
			glVertex3f(vert.x, vert.y, vert.z);
		}
    }
    glEnd();
	glEndList();
}
