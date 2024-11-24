#include "Challenges/TextureExample.h"
#include "core/Window.h"
#include "core/Image.h"
#include "AssetManager/AssetManager.h"

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

    static std::vector<TextureExample::Vertex> vertices = {
        Vertex{glm::vec3{ 0.5f,  0.5f, 0.0f},glm::vec3{1.0f, 0.0f, 0.0f},glm::vec2{1.0f, 1.0f}},
        Vertex{glm::vec3{ 0.5f, -0.5f, 0.0f},glm::vec3{0.0f, 1.0f, 0.0f},glm::vec2{1.0f, 0.0f}},
        Vertex{glm::vec3{-0.5f, -0.5f, 0.0f},glm::vec3{1.0f, 0.0f, 1.0f},glm::vec2{0.0f, 0.0f}},
        Vertex{glm::vec3{-0.5f,  0.5f, 0.0f},glm::vec3{1.0f, 1.0f, 0.0f},glm::vec2{0.0f, 1.0f}}
    };
    std::cerr << vertices.size() << std::endl;

    static std::vector<GLuint> indices = {
        0, 1, 2,
        0, 2, 3
    };

    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(
        std::vector<VertexAttribute>{
            { 3, VertexAttribute::Float, 0 },
            { 3, VertexAttribute::Float, 3 * sizeof(float) },
            { 2, VertexAttribute::Float, 6 * sizeof(float) }
    }, sizeof(Vertex));

    std::cerr << sizeof(Vertex) << " " << 8 * sizeof(float) << std::endl;
    // vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*) (0 * sizeof(float)));
    // vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    // vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*) (6 * sizeof(float)));

    shaderProgram = AssetManager::instance().loadShaderProgram("TextureExample");
    shaderProgram->activate();
    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());
    shaderProgram->setInt("texture1", 0);
    shaderProgram->setInt("texture2", 1);
}

void TextureExample::update() {
    shaderProgram->activate();
    shaderProgram->setFloat("mix_portion", mix_portion);
    vertexArray->renderIndexed();
}

void TextureExample::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    if (key == GLFW_KEY_UP and action == GLFW_PRESS)mix_portion = std::min(mix_portion + 0.1f, 1.0f);
    if (key == GLFW_KEY_DOWN and action == GLFW_PRESS)mix_portion = std::max(mix_portion - 0.1f, 0.0f);
}
