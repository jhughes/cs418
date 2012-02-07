#include "cube.h"

GLfloat cubeamb[] = {1.0, 1.0, 1.0, 1.0};
GLfloat cubediff[] = {1.0, 1.0, 1.0, 1.0};
GLfloat cubespec[] = {1.0, 1.0, 1.0, 1.0};

char* cube_xp_filename = "cube_maps/xp2.raw";
char* cube_xn_filename = "cube_maps/xn2.raw";
char* cube_yp_filename = "cube_maps/yp2.raw";
char* cube_yn_filename = "cube_maps/yn2.raw";
char* cube_zp_filename = "cube_maps/zp2.raw";
char* cube_zn_filename = "cube_maps/zn2.raw";

GLuint* skybox_textures;
GLuint cube_map;
GLsizei num_textures;

// Loads the textures used for cubemap / skybox
GLuint load_cube_textures() {
	num_textures = 6;
	int image_width = 512;
	int image_height = 512;
	char* filenames[] = {cube_xp_filename,cube_xn_filename,cube_yp_filename,cube_yn_filename,cube_zp_filename,cube_zn_filename};
	GLenum enums[] = {GL_TEXTURE_CUBE_MAP_POSITIVE_X,GL_TEXTURE_CUBE_MAP_NEGATIVE_X,GL_TEXTURE_CUBE_MAP_POSITIVE_Y,GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,GL_TEXTURE_CUBE_MAP_POSITIVE_Z,GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};
	// allocate texture names
	skybox_textures = (GLuint*) malloc(sizeof(GLuint) * num_textures);
	glGenTextures( num_textures, skybox_textures );
	glGenTextures( 1, &cube_map );
	for(int i = 0; i < num_textures; i++) {
		char* image = open_raw_image(filenames[i], image_width, image_height);
		// skybox texture 2d
		glBindTexture( GL_TEXTURE_2D, skybox_textures[i] );
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D (GL_TEXTURE_2D, 0, 3, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		// cubemap texture
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map);
		glTexImage2D (enums[i], 0, 3, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		free(image);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	return cube_map;
}

//http://sidvind.com/wiki/Skybox_tutorial
// Renders the skybox
void cube_display() {
	// Store the current matrix
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	// Enable/Disable features
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glDisable(GL_BLEND);
	// Just in case we set all vertices to white.
	glColor4f(0,1,0,1);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, skybox_textures[4]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex3f(  0.5f, -0.5f, -0.5f );
		glTexCoord2f(1, 1); glVertex3f( -0.5f, -0.5f, -0.5f );
		glTexCoord2f(1, 0); glVertex3f( -0.5f,  0.5f, -0.5f );
		glTexCoord2f(0, 0); glVertex3f(  0.5f,  0.5f, -0.5f );
	glEnd();
	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, skybox_textures[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
		glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f, -0.5f );
		glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f, -0.5f );
		glTexCoord2f(0, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
	glEnd();
	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, skybox_textures[5]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
		glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
		glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
		glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
	glEnd();
	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, skybox_textures[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f, -0.5f );
		glTexCoord2f(1, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
		glTexCoord2f(1, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
		glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f, -0.5f );
	glEnd();
	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, skybox_textures[2]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
		glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
		glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
		glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
	glEnd();
	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, skybox_textures[3]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
		glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
		glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
		glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
	glEnd();
	// Restore enable bits and matrix
	glPopAttrib();
	glPopMatrix();
}
