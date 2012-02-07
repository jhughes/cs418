//The vertices of the heart
//These are ordered so a simple GL_TRIANGLE_FAN will draw the entire heart.
float heartVertices[][2] = { 
	{ 0.0f, 0.0f },
	{ 0.0f, -0.8f },
	{ 0.4f, -0.5f },
	{ 0.6f, -0.27f },
	{ 0.7f, -0.1f },
	{ 0.72f, 0.01f },
	{ 0.73f, 0.15f },
	{ 0.71f, 0.3f },
	{ 0.65f, 0.45f },
	{ 0.58f, 0.55f },
	{ 0.51f, 0.63f },
	{ 0.42f, 0.7f },
	{ 0.32f, 0.72f },
	{ 0.25f, 0.72f },
	{ 0.20f, 0.70f },
	{ 0.14f, 0.67f },
	{ 0.08f, 0.61f },
	{ 0.04f, 0.54f },
	{ 0.0f, 0.47f },
	{ -0.04f, 0.54f },
	{ -0.08f, 0.61f },
	{ -0.14f, 0.67f },
	{ -0.20f, 0.70f },
	{ -0.25f, 0.72f },
	{ -0.32f, 0.72f },
	{ -0.42f, 0.7f },
	{ -0.51f, 0.63f },
	{ -0.58f, 0.55f },
	{ -0.65f, 0.45f },
	{ -0.71f, 0.3f },
	{ -0.73f, 0.15f },
	{ -0.72f, 0.01f },
	{ -0.7f, -0.1f },
	{ -0.6f, -0.27f },
	{ -0.4f, -0.5f },  
	{ 0.0f, -0.8f }
};
int numberVerticesInHeart = 35;
//Uses opengl calls to create the heart
void drawHeart()
{
	glBegin(GL_TRIANGLE_FAN);

	//color the center darker pink
	glColor3f(1, 0.2, 0.4);
	glVertex2fv(heartVertices[0]);

	//color the rest of the heart lighter pink
	glColor3f(1, 0.4f, 0.8f);
	for(int i = 1; i <= numberVerticesInHeart; i++)
	{
		glVertex2fv(heartVertices[i]);
	}
	glEnd();
}
