#version 330 core

in FragmentIn {
    vec3 normal;
    vec3 fragmentPosition;
} fragin;

uniform vec3 cameraPos;
uniform samplerCube tex;

out vec4 FragColor;

void main () {
    vec3 I = normalize(fragin.fragmentPosition - cameraPos);
    vec3 r = reflect(I,normalize(fragin.normal));
    //float ratio = 1.00 / 1.52;
    //vec3 r = refract(I,normalize(fragin.normal),ratio);
    FragColor = texture(tex,r);
}