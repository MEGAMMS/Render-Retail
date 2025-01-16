#version 330 core

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 speculer;
    
};


struct PointLight {
    float constant;
    float linear;
    float quadratic;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 speculer;
};


struct SpotLight {
    float innerCutOff;
    float outerCutOff;
    vec3 direction;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 speculer;
};


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 speculer;
    float shineness;
};

struct MaterialMap {
    sampler2D diffuse;
    sampler2D speculer;
    sampler2D emission;
    float shineness;
};


#define lights_num 4
layout(std140) uniform Lighting {
DirectionalLight directional_lights[lights_num];
PointLight point_lights[lights_num];
SpotLight spot_lights[lights_num];
};


vec3 process_directionalLight (DirectionalLight light, vec3 cameraDirection);
vec3 process_pointLight (PointLight light, vec3 cameraDirection);
vec3 process_spotLight (SpotLight light, vec3 cameraDirection);



in vec3 normal;
in vec3 fragmentPosition;
in vec2 texCoord;

uniform vec3 cameraPos;
uniform vec3 color;

out vec4 FragColor;


void main() {
    vec3 cameraDirection = normalize(cameraPos-fragmentPosition);

    vec3 result = vec3(0.0);

    for (int i = 0 ; i<lights_num ; ++i) {
        result += process_directionalLight(directional_lights[i],cameraDirection);
        result += process_pointLight(point_lights[i],cameraDirection);
        result += process_spotLight(spot_lights[i],cameraDirection);
    }
    
    FragColor = vec4(result*color,1.0);
}




vec3 process_directionalLight (DirectionalLight light, vec3 cameraDirection) {
    vec3 lightDirection = normalize(-light.direction);

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
    return ambient + diffuse + speculer ;
}

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

vec3 process_spotLight (SpotLight light, vec3 cameraDirection) {
    vec3 lightDirection = normalize(light.position - fragmentPosition);
    float theta = dot(lightDirection,normalize(-light.direction));
    float intensity = (theta - light.outerCutOff) / (light.innerCutOff - light.outerCutOff);
    intensity = clamp(intensity,0.0,1.0);

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
    return intensity * (ambient + diffuse + speculer);
}