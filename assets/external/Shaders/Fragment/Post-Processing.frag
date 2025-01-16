#version 330 core
in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D tex;

void main() { 
    FragColor = texture(tex,texCoord);
    
    /* Inversion */
    //FragColor = vec4((1.0 - vec3(FragColor)) , 1.0);


    /* Grey Scale */
    //float avg = (FragColor.r + FragColor.g + FragColor.b) / 3;
    //FragColor = vec4(avg,avg,avg,1.0);


    /* Kernal */
    const float offset = 1.0 / 300.0;
    vec2 coords [9] = vec2[](
        vec2(texCoord.x - offset , texCoord.y + offset),
        vec2(texCoord.x , texCoord.y + offset),
        vec2(texCoord.x + offset , texCoord.y + offset),
        vec2(texCoord.x - offset , texCoord.y),
        vec2(texCoord.x , texCoord.y),
        vec2(texCoord.x + offset , texCoord.y),
        vec2(texCoord.x - offset , texCoord.y - offset),
        vec2(texCoord.x , texCoord.y - offset),
        vec2(texCoord.x + offset , texCoord.y - offset)
    );
    vec3 texEle[9];
    for (int i = 0 ; i<9 ; i++)
        texEle[i] = vec3(texture(tex,coords[i]));

    float kernal[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16  
    );

    vec3 res = vec3(0);
    for (int i = 0 ; i<9 ; i++)
        res += texEle[i] * kernal[i];

    FragColor = vec4(res,1.0);
}