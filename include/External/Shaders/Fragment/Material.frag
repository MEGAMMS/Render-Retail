#version 330 core

in vec3 normal;
in vec3 fragmentPosition;
in vec2 texCoord;
uniform vec3 color;
uniform vec3 cameraPos;
out vec4 FragColor;

uniform sampler2D tex;


/* Logic */
void main() {
    vec3 cameraDirection = normalize(cameraPos-fragmentPosition);

    FragColor = texture(tex,texCoord);
}