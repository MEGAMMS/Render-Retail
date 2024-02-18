#include "Challenges/TriangleExample.h"
#include "buffers/EBO.h"
#include "buffers/VBO.h"
#include "core/Window.h"

struct Vertex {
    glm::vec2 position;
};
TriangleExample::TriangleExample() {
    static std::array<Vertex, 4> vertices = {
      Vertex{ glm::vec2{-1.,-1 * sqrt(3) / 2} },
      Vertex{ glm::vec2{1.,-1 * sqrt(3) / 2} },
      Vertex{ glm::vec2{0.,1.} },
    };
    static std::array<GLuint, 6> indices = {
        0, 1, 2
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

    shaderProgram = std::make_shared<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
    shaderProgram->Activate();
    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());


    vbo.Delete();
    ebo.Delete();

}
void TriangleExample::update() {
    shaderProgram->Activate();
    shaderProgram->setFloat("u_time", glfwGetTime());
    shaderProgram->setFloat("u_down", (float) upSideDown);

    vao.Bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*) (0 * sizeof(GLuint)));

}
void TriangleExample::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    if (key == GLFW_KEY_R and action == GLFW_PRESS)upSideDown = !upSideDown;

}