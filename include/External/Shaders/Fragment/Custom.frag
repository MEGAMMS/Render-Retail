#version 330 core

in vec3 normal;
in vec3 fragmentPosition;
in vec2 texCoord;
uniform vec3 color;
uniform vec3 cameraPos;


#define textureLimit 4
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_diffuse4;
uniform sampler2D texture_speculer1;
uniform sampler2D texture_speculer2;
uniform sampler2D texture_speculer3;
uniform sampler2D texture_speculer4;

out vec4 FragColor;



/* Lighting */
struct PointLight {
    float constant;
    float linear;
    float quadratic;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 speculer;
};
uniform PointLight point_light;


vec3 process_pointLight (PointLight light, vec3 cameraDirection);



/* Logic */
void main() {
    vec3 cameraDirection = normalize(cameraPos-fragmentPosition);

    vec3 result = vec3(0.0);

    if (point_light.constant != 0.0) {
        result += process_pointLight(point_light,cameraDirection);
    }

    vec4 tex = texture(texture_diffuse1,texCoord);
    FragColor = vec4(((color + vec3(tex)) * result),1.0);
}



/* Light Functions */
vec3 process_pointLight (PointLight light, vec3 cameraDirection) {
    vec3 lightDirection = light.position - fragmentPosition;
    float d = length(lightDirection);
    float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * pow(d,2));
    lightDirection = normalize(lightDirection);

    // Ambient
    vec3 ambient = light.ambient;

    // Difuse
    float diff = max(dot(normal,lightDirection),0.0);
    vec3 diffuse = light.diffuse * diff;

    // Speculer
    vec3 lightReflection = reflect(-lightDirection,normal);
    float spec = pow(max(dot(cameraDirection,lightReflection),0.0),32.0f);
    vec3 speculer = light.speculer * spec;

    // Result
    return attenuation * (ambient + diffuse + speculer);
}