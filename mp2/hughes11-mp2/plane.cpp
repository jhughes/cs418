#include "plane.h"
Vector3 wing;//the wing of the plane
Vector3 up;//the top of the plane
Vector3 view;//where the plane is looking
Vector3 translation;//keeps track of the overall translation of the plane
float speed;
float dRoll;
float dPitch;
//keeps track of which buttons are currently pressed: {W,A,S,D,space,C}
bool pressed[] = {false,false,false,false,false,false};

//initialize plane vectors
void plane_init(){

	speed = 0.001;
	dRoll = 0.03;
	dPitch = 0.03;
	translation = (Vector3){0.0,0.0,0.10};
	wing = (Vector3){0.0,1.0,0.0};
	up = (Vector3){0.0,0.0,1.0};
	view = (Vector3){1.0,0.0,0.0};
}

//handles keypresses
void plane_keyboard(unsigned char key, int x, int y){
	   switch (key) {
		case 'w':
			pressed[0] = true;
			break;
		case 'a':
			pressed[1] = true;
			break;
		case 's':
			pressed[2] = true;	
			break;
		case 'd':
			pressed[3] = true;
			break;
		case ' ':
			pressed[4] = true;
			speed += .001;
			if( speed > 0.1 )
				speed = 0.1;
			break;
		case 'c':
			pressed[5] = true;
			speed -= .001;
			if( speed < 0.001 )
				speed = 0.001;
			break;
		default:
			break;
   }
}

//handles key releases
void plane_keyboardup(unsigned char key, int x, int y){
	   switch (key) {
		case 'w':
			pressed[0] = false;
			break;
		case 'a':
			pressed[1] = false;
			break;
		case 's':
			pressed[2] = false;	
			break;
		case 'd':
			pressed[3] = false;
			break;
		case ' ':
			pressed[4] = false;
			break;
		case 'c':
			pressed[5] = false;
			break;
		default:
			break;
   }
}

//on every timer call: rolls, pitches, handles speed, and moves the plane
void planeTimer(int v)
{
	if(pressed[0])
	{
		pitch_down();
	}
	if(pressed[1])
	{
		roll_left();
	}
	if(pressed[2])
	{
		pitch_up();			
	}
	if(pressed[3])
	{
		roll_right();
	}
	if(pressed[4])
	{
		speed += .0001;
		if( speed > 0.1 )
			speed = 0.1;
	}
	if(pressed[5])
	{
		speed -= .0001;
		if( speed < 0.001 )
			speed = 0.001;
	}
	move();
}

//Sets the view to whatever the plane it pointing at
void update_view(){
	glLoadIdentity();
	gluLookAt(translation.x,translation.y,translation.z, 
	translation.x + view.x,translation.y + view.y, translation.z + view.z,
	up.x,up.y,up.z);
}

//translates the plane
void move(){
	translation.x += speed*view.x;
	translation.y += speed*view.y;
	translation.z += speed*view.z;
}

//rolls the plane around the view vector
void roll_plane(float roll){
	up = rotate_point(up, view, roll);
	wing = rotate_point(wing, view, roll);
}

//pitches the plane around the wing vector
void pitch_plane(float pitch){
	up = rotate_point(up, wing, pitch);
	view = rotate_point(view, wing, pitch);
}

//a method for rotating a point around a given vector by angle theta
//found at: http://inside.mines.edu/~gmurray/ArbitraryAxisRotation/ArbitraryAxisRotation.html
Vector3 rotate_point(Vector3 point, Vector3 vector, float theta){
	float x,y,z,u,v,w, xrot,yrot,zrot;
	x = point.x;
	y= point.y;
	z= point.z;
	u= vector.x;
	v = vector.y;
	w = vector.z;
	xrot = u*(u*x+v*y+w*z) + (x*(v*v+w*w)-u*(v*y+w*z))*cos(theta) + sqrt(u*u+v*v+w*w) * (-w*y+v*z) * sin(theta);
	yrot = v*(u*x+v*y+w*z) + (y*(u*u+w*w)-v*(u*x+w*z))*cos(theta) + sqrt(u*u+v*v+w*w) * (w*x-u*z) * sin(theta);
	zrot = w*(u*x+v*y+w*z) + (z*(u*u+v*v)-w*(u*x+v*y))*cos(theta) + sqrt(u*u+v*v+w*w) * (-v*x+u*y) * sin(theta);
	float denom = u*u+v*v+w*w;
	return (Vector3){xrot/denom,yrot/denom,zrot/denom};
}
void roll_left(){
	roll_plane(-dRoll);
}
void roll_right(){
	roll_plane(dRoll);
}
void pitch_up(){
	pitch_plane(dPitch);
}
void pitch_down(){
	pitch_plane(-dPitch);
}
