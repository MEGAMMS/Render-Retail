#include "Render-Retail/Objects/LightCube.h"

#include "AssetManager/AssetManager.h"
#include "core/Window.h"

LightCube::LightCube(glm::vec3 lightPos, glm::vec3 lightColor) : lightPos(lightPos), lightColor(lightColor) {
    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(
        std::vector<VertexAttribute>{
            {3, VertexAttribute::Float, 0},
        },
        sizeof(Vertex));
    lightShader = AssetManager::instance().loadShaderProgram("LightCube");
    lightShader->activate();
    lightShader->setVec2("u_resolution", Window::instance().getWindowRes());
}
void LightCube::updatePos(glm::vec3 newPos) { lightPos = newPos; }
void LightCube::update(float dt) {
    model = glm::mat4(1.);

    model = glm::translate(model, lightPos);

    model = glm::scale(model, glm::vec3(0.2));
    // model = glm::rotate(model, glm::radians(45.f), glm::vec3(1., 1., 1.));
}

void LightCube::render(glm::mat4 mvp) {
    lightShader->activate();
    lightShader->setFloat("u_time", glfwGetTime());
    lightShader->setMat4("mvp", mvp);
    lightShader->setVec3("lightColor", lightColor);
    lightShader->setMat4("model", model);
    vertexArray->renderIndexed();
}

void LightCube::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}

void LightCube::onCursorPositionEvent(double x, double y) {}
