float dance = 0.0f; //Used in the sin/cos to make the I wiggle
float colorRotation = 0.0f; //Used to make a wave of orange and blue color that goes through the I
float color[] = {0,0,0}; //The most recently calculated color

//A low polygon I
float iVertices[][2] = { 
	{ -0.3f, 0.5f }, //0
	{ -0.1f, 0.5f }, //1
	{ 0.1f, 0.5f },  //2
	{ 0.3f, 0.5f },  //3
        { -0.3f, 0.3f }, //4
	{ -0.1f, 0.3f }, //5	
	{ 0.1f, 0.3f },  //6  
	{ 0.3f, 0.3f },  //7
 	{ -0.1f, 0.1f }, //8
	{ 0.1f, 0.1f },  //9
	{ -0.1f, -0.1f },//10
	{ 0.1f, -0.1f }, //11
	{ -0.3f, -0.3f },//12
	{ -0.1f, -0.3f },//13
	{ 0.1f, -0.3f }, //14
	{ 0.3f, -0.3f }, //15
	{ -0.3f, -0.5f },//16
        { -0.1f, -0.5f },//17
	{ 0.1f, -0.5f }, //18
        { 0.3f, -0.5f }  //19
};

//The triangle strips used to create the low polygon I
int iTriangleStripTop[] = {
	0,4,1,5,2,6,3,7
};
int iTriangleStripMiddle[] = {
	5,6,8,9,10,11,13,14
};
int iTriangleStripBottom[] = {
	12,16,13,17,14,18,15,19
};
int* iTriangleStrips[] = {
	iTriangleStripTop,
	iTriangleStripMiddle,
	iTriangleStripBottom
};

//A higher polygon I
float iDoubleVertices[][2] = { 
	{ -0.3f, 0.5f }, //0
	{ -0.2f, 0.5f }, //1
	{ -0.1f, 0.5f }, //2
	{ -0.0f, 0.5f }, //3
	{ 0.1f, 0.5f },  //4
	{ 0.2f, 0.5f },  //5
	{ 0.3f, 0.5f },  //6
        { -0.3f, 0.4f }, //7
	{ -0.2f, 0.4f }, //8
	{ -0.1f, 0.4f }, //9
	{ -0.0f, 0.4f }, //10
	{ 0.1f, 0.4f },  //11
	{ 0.2f, 0.4f },  //12
	{ 0.3f, 0.4f },  //13
	{ -0.3f, 0.3f }, //14
	{ -0.2f, 0.3f }, //15
	{ -0.1f, 0.3f }, //16
	{ -0.0f, 0.3f }, //17
	{ 0.1f, 0.3f },  //18
	{ 0.2f, 0.3f },  //19
	{ 0.3f, 0.3f },  //20
	{ -0.1f, 0.2f }, //21
	{ 0.0f, 0.2f },  //22
	{ 0.1f, 0.2f },  //23
	{ -0.1f, 0.1f }, //24
	{ 0.0f, 0.1f },  //25
	{ 0.1f, 0.1f },  //26
	{ -0.1f, 0.0f }, //27
	{ 0.0f, 0.0f },  //28
	{ 0.1f, 0.0f },  //29
	{ -0.1f, -0.1f }, //30
	{ 0.0f, -0.1f },  //31
	{ 0.1f, -0.1f },  //32
	{ -0.1f, -0.2f }, //33
	{ 0.0f, -0.2f },  //34
	{ 0.1f, -0.2f },  //35
	{ -0.3f, -0.3f }, //36
	{ -0.2f, -0.3f }, //37
	{ -0.1f, -0.3f }, //38
	{ -0.0f, -0.3f }, //39
	{ 0.1f, -0.3f },  //40
	{ 0.2f, -0.3f },  //41
	{ 0.3f, -0.3f },  //42
        { -0.3f, -0.4f }, //43
	{ -0.2f, -0.4f }, //44
	{ -0.1f, -0.4f }, //45
	{ -0.0f, -0.4f }, //46
	{ 0.1f, -0.4f },  //47
	{ 0.2f, -0.4f },  //48
	{ 0.3f, -0.4f },  //49
	{ -0.3f, -0.5f }, //50
	{ -0.2f, -0.5f }, //51
	{ -0.1f, -0.5f }, //52
	{ -0.0f, -0.5f }, //53
	{ 0.1f, -0.5f },  //54
	{ 0.2f, -0.5f },  //55
	{ 0.3f, -0.5f },  //56
};

//The triangle strips used to create the high polygon I
int iDoubleTriangleStripTop[] = {
	0,7,1,8,2,9,3,10,4,11,5,12,6,13
};
int iDoubleTriangleStripTop2[] = {
	7,14,8,15,9,16,10,17,11,18,12,19,13,20
};
int iDoubleTriangleStripMiddle[] = {
	16,17,21,22,24,25,27,28,30,31,33,34,38,39
};
int iDoubleTriangleStripMiddle2[] = {
	17,18,22,23,25,26,28,29,31,32,34,35,39,40
};
int iDoubleTriangleStripBottom[] = {
	36,43,37,44,38,45,39,46,40,47,41,48,42,49
};
int iDoubleTriangleStripBottom2[] = {
	43,50,44,51,45,52,46,53,47,54,48,55,49,56
};
int* iDoubleTriangleStrips[] = {
	iDoubleTriangleStripTop,
	iDoubleTriangleStripTop2,
	iDoubleTriangleStripMiddle,
	iDoubleTriangleStripMiddle2,
	iDoubleTriangleStripBottom,
	iDoubleTriangleStripBottom2
};


//Used to find the color for a vertex of the I
void findColor(float x, float y)
{
	//find the percentages of orange and blue the color will have
	float bluepercent = (float) sin(colorRotation + x + y);
	bluepercent *= bluepercent; //square the percent; looks better
	float orangepercent = 1.0f - bluepercent;
	
	//calculate the R G B values
	float r = orangepercent * 1.0f;
	float g = orangepercent * 0.5f;
	float b = bluepercent * 1.0f;
	
	//set the color
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

int numberTriangleStrips = 5;
int numberVerticesInStrips = 13;
//Uses opengl calls to create the I
void drawI()
{
	//Plot the 5 Different parts of the I
	glColor3f(0, 0, 1);
	
	for(int j = 0; j <= numberTriangleStrips; j++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            for (int i = 0; i <= numberVerticesInStrips; i++)
            {	
		float x = iDoubleVertices[iDoubleTriangleStrips[j][i]][0];
		float y = iDoubleVertices[iDoubleTriangleStrips[j][i]][1];
		// Calculates the offsets used to make the I wiggle and dance
		float offsetx =  (float) (0.1f * sin(dance + 5*y));
                float offsety =  (float) (0.01f * cos(dance + 1*x));

		findColor(x, y);
		glColor3fv(color);		
                glVertex2f(x + offsetx,y + offsety);
            }
            glEnd();
        }
}
