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

void main()
{
    // vec2 TexCoordCopy = TexCoord* float(cubeFace);
    // FragColor = vec4(TexCoordCopy,0.0,1.0);
    vec4 textColor =  texture(cubeFace,TexCoord);
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lightRes = ambient + diffuse + specular;

    FragColor =  vec4(cubeColor * lightRes,1.0);
    FragColor = textColor * vec4(lightRes, 1.0);
}