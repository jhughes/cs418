Cs418 MP4 JELLO-I
Jonathan Hughes
hughes11
Created on EWS linux machines
__________________________________________________________________________________________________________________________

Features:
	* Jello - I
	* c0 continuity cubic Bezier camera path
	* Mostly working subdivision

To make:
make clean; make

To run:
./mp4
__________________________________________________________________________________________________________________________

Controls:	(^,v,<,> = arrow keys)
W,A,S,D - Move camera around
Hold SpaceBar - Subdivide I
Q - negative Y force
E - positive Y force
^ - negative Z force
v - positive Z force
< - negative X force
> - positive X force
__________________________________________________________________________________________________________________________

Notes:
	* It's possible to get pieces of the I to stick to itself if large forces are applied, so do not mash the buttons.
	* If the I gets stuck close and restart the program to fix it.
	* The camera will move in a random path around the center.  The path it follows is a cubic Bezier curve continuous on c0, so when it switches to a new curve it will feel sharp.
	* Subdivision only mostly works.  I only did 1 level of subdivision because I was trying to figure out why the 1st level of subdivision looks incorrect.

Notable Included Files:
mp4.cpp 			The main openGL window and init calls and Bezier curve for camera view
i.cpp 			Subdivides and holds all the data to render the I
particle.cpp 	Contains the particle class
helper.cpp 		Misc helper functions
structures.h 	Structs used to represent meshes and lists.
