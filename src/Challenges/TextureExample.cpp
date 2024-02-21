#include "Challenges/TextureExample.h"
#include "core/Window.h"
#include "buffers/EBO.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 textureCorr;

};

TextureExample::TextureExample() {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    std::vector<unsigned char> image; // Image buffer
    unsigned width, height;

    // Load PNG file
    unsigned error = lodepng::decode(image, width, height, "assets/container.png");

    // Check if there's an error
    if (error) {
        std::cerr << "Decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        exit(1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    glGenerateMipmap(GL_TEXTURE_2D);

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


    shaderProgram = std::make_shared<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
    shaderProgram->Activate();
    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());
    glBindTexture(GL_TEXTURE_2D, texture);

}

void TextureExample::update() {
    shaderProgram->Activate();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TextureExample::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {

}
