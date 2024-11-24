#include "Challenges/TriangleExample.h"
#include "core/Window.h"
#include "AssetManager/AssetManager.h"

TriangleExample::TriangleExample() {
    static std::vector<TriangleExample::Vertex> vertices = {
      Vertex{ glm::vec2{-1.,-1 * sqrt(3) / 2} },
      Vertex{ glm::vec2{1.,-1 * sqrt(3) / 2} },
      Vertex{ glm::vec2{0.,1.} },
    };
    static std::vector<GLuint> indices = {
        0, 1, 2
    };


    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(TriangleExample::Vertex::vertexAttributes(), sizeof(TriangleExample::Vertex));

    shaderProgram = AssetManager::instance().loadShaderProgram("Triangle");
    shaderProgram->activate();
    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());

}
void TriangleExample::update() {
    shaderProgram->activate();
    shaderProgram->setFloat("u_time", glfwGetTime());
    shaderProgram->setFloat("u_down", (float) upSideDown);

    vertexArray->renderIndexed();
}
void TriangleExample::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    if (key == GLFW_KEY_R and action == GLFW_PRESS)upSideDown = !upSideDown;

}