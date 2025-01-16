#version 330 core
in vec2 texCoord;
uniform vec3 color;
uniform sampler2D tex;
out vec4 FragColor;


void main() {
    FragColor = vec4(color,1.0) + texture(tex,texCoord);
    /*
    FragColor = color;
    if (FragColor == vec4(0)) {
        FragColor = texture(tex,texCoord);
        if (FragColor.w < 0.1)
            discard;
    }
    */
}