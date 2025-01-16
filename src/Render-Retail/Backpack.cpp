#include "Render-Retail/Backpack.h"

#include <memory>

#include "Model/model.h"
#include "Render/ShaderProgram.h"

Backpack::Backpack() {
    m_model = std::make_shared<Model>("assets/objects/backpack/backpack.obj");
    m_shader = std::make_shared<const ShaderProgram>("Model");
}

void Backpack::update(float dt) {}
void Backpack::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_shader->activate();
    m_shader->setMat4("model", this->model);
    m_shader->setMat4("mvp", mvp);
    m_model->Draw(m_shader);
}
void Backpack::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Backpack::onCursorPositionEvent(double x, double y) {}
