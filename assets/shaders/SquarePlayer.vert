#version 330 core

//Positions/Coordinates
layout (location = 0) in vec2 aPos;


uniform vec2 u_move;

void main()
{
	// Outputs the positions/coordinates of all vertices
	float a = .5;

	vec2 finalPos = aPos*a*0.5;
	finalPos += u_move;
	gl_Position = vec4(finalPos,0.0, 1.0);
}