#version 330 core

//Positions/Coordinates
layout(location = 0) in vec2 aPos;

out vec3 verPos;

uniform float u_down;

void main() {
    vec2 finalPos = aPos * 0.5;
    
    verPos = vec3(finalPos,0.0);

    finalPos.y *= 1. - u_down * 2;

    gl_Position = vec4(finalPos, 0.0, 1.0);
}