#include "Challenges/TextureExample.h"
#include "core/Window.h"
#include "buffers/EBO.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 textureCorr;

};


class Img {
public:
    std::vector<unsigned char> data; // Image buffer
    unsigned width, height;
    Img(std::string path) {

        unsigned error = lodepng::decode(data, width, height, path, LCT_RGBA);

        // Check if there's an error
        if (error) {
            std::cerr << "Decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
            exit(1);
        }
        vertical_flip(data, width, height);
    }
private:
    void vertical_flip(std::vector<unsigned char>& image, unsigned& width, unsigned& height) {
        size_t number_of_channels = 4;
        size_t bytes_per_pixel = sizeof(unsigned char) * number_of_channels;
        size_t bytes_per_row = static_cast<size_t>(width) * bytes_per_pixel;

        for (int row = 0; row < (height >> 1); ++row) {
            auto row0 = image.begin() + row * bytes_per_row;
            auto row1 = image.begin() + (height - row - 1) * bytes_per_row;

            std::swap_ranges(row0, row0 + bytes_per_row, row1);
        }
    }
};

TextureExample::TextureExample() {
    unsigned int conTex;
    glGenTextures(1, &conTex);
    glBindTexture(GL_TEXTURE_2D, conTex);
    Img container("assets/container.png");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, container.width, container.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, container.data.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    unsigned int faceTex;
    glGenTextures(1, &faceTex);
    glBindTexture(GL_TEXTURE_2D, faceTex);
    Img face("assets/awesomeface.png");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, face.width, face.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, face.data.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, conTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, faceTex);

    static std::array<Vertex, 4> vertices = {
        Vertex{glm::vec3{ 0.5f,  0.5f, 0.0f},glm::vec3{1.0f, 0.0f, 0.0f},glm::vec2{1.0f, 1.0f}},
        Vertex{glm::vec3{ 0.5f, -0.5f, 0.0f},glm::vec3{0.0f, 1.0f, 0.0f},glm::vec2{1.0f, 0.0f}},
        Vertex{glm::vec3{-0.5f, -0.5f, 0.0f},glm::vec3{1.0f, 0.0f, 1.0f},glm::vec2{0.0f, 0.0f}},
        Vertex{glm::vec3{-0.5f,  0.5f, 0.0f},glm::vec3{1.0f, 1.0f, 0.0f},glm::vec2{0.0f, 1.0f}}
    };

    static std::array<GLuint, 6> indices = {
        0, 1, 2,
        0, 2, 3
    };


    vao = VAO();
    vao.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo((GLfloat*) vertices.data(), sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO ebo((GLuint*) indices.data(), sizeof(indices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*) (0 * sizeof(float)));
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*) (6 * sizeof(float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();


    shaderProgram = std::make_shared<Shader>("assets/shaders/TextureExample.vert", "assets/shaders/TextureExample.frag");
    shaderProgram->Activate();
    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());
    shaderProgram->setInt("texture1", 0);
    shaderProgram->setInt("texture2", 1);
}

void TextureExample::update() {
    shaderProgram->Activate();
    shaderProgram->setFloat("mix_portion", mix_portion);
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TextureExample::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    if (key == GLFW_KEY_UP and action == GLFW_PRESS)mix_portion = std::min(mix_portion + 0.1f, 1.0f);
    if (key == GLFW_KEY_DOWN and action == GLFW_PRESS)mix_portion = std::max(mix_portion - 0.1f, 0.0f);
}
