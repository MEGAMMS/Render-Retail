#include "Challenges/Cubes/Cube.h"
#include "AssetManager/AssetManager.h"
#include "core/Window.h"

Cube::Cube() {
    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(std::vector<VertexAttribute>{
        { 3, VertexAttribute::Float, 0 },
        { 2, VertexAttribute::Float, 3 * sizeof(float) }
    }, sizeof(Vertex));
    cubeShader = AssetManager::instance().loadShaderProgram("Cube");
    cubeShader->activate();
    cubeShader->setVec2("u_resolution", Window::instance().getWindowRes());

    brick = AssetManager::instance().loadTexture("assets/brick.png");
    cubeShader->setTexture("cubeFace", brick, 3);
}

void Cube::update(float dt) {
    model = glm::mat4(1.);
    model = glm::scale(model, glm::vec3(0.5));
    model = glm::rotate(model, glm::radians(45.f), glm::vec3(1., 1., 1.));
    float angle = (int(glfwGetTime() * 50000) % 360000) / 1000.f;
    // angle = 0;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.6f, 0.8f, 0.4f));


}

void Cube::render(glm::mat4 mvp) {
    cubeShader->activate();
    cubeShader->setFloat("u_time", glfwGetTime());
    cubeShader->setMat4("mvp", mvp);
    cubeShader->setMat4("model", model);
    vertexArray->renderIndexed();
}

void Cube::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {

}

void Cube::onCursorPositionEvent(double x, double y) {

}
