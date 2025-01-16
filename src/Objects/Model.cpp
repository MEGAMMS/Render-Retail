#include "Objects/Model.h"

#include "Model/model.h"
#include "Render/ShaderProgram.h"

Model::Model(const std::string& modelPath) {
    m_model = std::make_shared<aiModel>(modelPath);
    m_shader = std::make_shared<const ShaderProgram>("Model");
}

void Model::update(float dt) {}
void Model::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_shader->activate();
    m_shader->setMat4("model", this->model);
    m_shader->setMat4("mvp", mvp);
    m_model->Draw(m_shader);
}
void Model::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Model::onCursorPositionEvent(double x, double y) {}
