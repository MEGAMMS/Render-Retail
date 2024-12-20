#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;  

uniform sampler2D cubeFace;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 cubeColor;

out vec4 FragColor;


vec3 calcLight(vec3 Normal, vec3 FragPos, vec3 lightColor, vec3 lightPos, vec3 viewPos) {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Ensure the normal is always facing the viewer
    if (dot(norm, viewDir) < 0.0) {
        norm = -norm;
    }

    // Ambient lighting
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting
    float specularStrength = 0.5;
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine results
    return ambient + diffuse + specular;
}


void main()
{
    // vec2 TexCoordCopy = TexCoord* float(cubeFace);
    // FragColor = vec4(TexCoordCopy,0.0,1.0);
    vec4 textColor =  texture(cubeFace,TexCoord);

    vec3 lightRes = calcLight(Normal,FragPos, lightColor,lightPos,viewPos);

    FragColor =  vec4(cubeColor * lightRes,1.0);
    FragColor = textColor * vec4(lightRes, 1.0);
}
