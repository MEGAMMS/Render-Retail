#include "Challenges/Pyramid.h"
#include "buffers/EBO.h"
#include "core/Window.h"


struct Vertex {
    glm::vec2 position;
};
Pyramid::Pyramid() {
    static std::array<Vertex, 4> vertices = {
      Vertex{ glm::vec2{-1.,-1.} },
      Vertex{ glm::vec2{ 1.,-1.} },
      Vertex{ glm::vec2{-1., 1.} },
      Vertex{ glm::vec2{ 1., 1.} }
    };
    static std::array<GLuint, 6> indices = {
        0, 1, 2,
        3, 1, 2
    };


    vao = VAO();
    vao.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo((GLfloat*) vertices.data(), sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO ebo((GLuint*) indices.data(), sizeof(indices));

    // Links VBO to VAO
    vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*) 0);
    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();


    shaderProgram = std::make_shared<Shader>(
        "assets/shaders/Pyramid.vert",
        "assets/shaders/Pyramid.frag");
    shaderProgram->Activate();

    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());

    vbo.Delete();
    ebo.Delete();
}

void Pyramid::update(float dt) {
}

void Pyramid::Delete() {
}
void Pyramid::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    bool pressed = action == GLFW_PRESS;
}

