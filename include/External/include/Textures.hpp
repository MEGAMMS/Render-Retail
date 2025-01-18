#pragma once
#include "stbloader.h"
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;


namespace workspace {

    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false)
    {
        string filename = string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            cout << "Texture failed to load at path: " << path << endl;
            stbi_image_free(data);
        }

        return textureID;
    }


    unsigned int loadCubemap(vector<string> faces)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, nrComponents;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
            if (data)
            {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data
                );
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return textureID;
    }



    class Textures {
    public:
        inline static map<string, unsigned int> id_map;

        static void load() {
            stbi_set_flip_vertically_on_load(true);


            id_map.insert({ "outer_wall",TextureFromFile("wall2.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "outer_wall2",TextureFromFile("wall.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "outer_wall3",TextureFromFile("wall3.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "outer_wall4",TextureFromFile("wall4.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "floor",TextureFromFile("floor_diffuse.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "ceil",TextureFromFile("ceil.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "base",TextureFromFile("base.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "arma",TextureFromFile("arma1.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "logo",TextureFromFile("logo.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "shutter",TextureFromFile("shutter.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "glass",TextureFromFile("glass.png","assets/external/Assets/Textures") });
            id_map.insert({ "frame",TextureFromFile("frame.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "ad1",TextureFromFile("ad1.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "ad2",TextureFromFile("ad2.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "ad3",TextureFromFile("ad3.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "ad4",TextureFromFile("ad4.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "ad5",TextureFromFile("ad5.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "ad6",TextureFromFile("ad6.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "holder",TextureFromFile("holder.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "fridgeBody",TextureFromFile("fridgeBody.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "fridgeTop",TextureFromFile("fridgeTop.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "fridgeBottom",TextureFromFile("fridgeBottom.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "fridgeFrame",TextureFromFile("fridgeFrame.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "desk",TextureFromFile("desk.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "can0",TextureFromFile("can0.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "can1",TextureFromFile("can1.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "can2",TextureFromFile("can2.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "can3",TextureFromFile("can3.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "can4",TextureFromFile("can4.bmp","assets/external/Assets/Textures") });

            id_map.insert({ "ball0",TextureFromFile("football.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "ball1",TextureFromFile("basketball.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "ball2",TextureFromFile("colorball.bmp","assets/external/Assets/Textures") });
            id_map.insert({ "ball3",TextureFromFile("patternball.bmp","assets/external/Assets/Textures") });


            stbi_set_flip_vertically_on_load(false);
        }

    };

}