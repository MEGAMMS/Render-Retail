#version 330 core

//Positions/Coordinates
layout (location = 0) in vec2 aPos;




void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = vec4(aPos,0.0, 1.0);
}