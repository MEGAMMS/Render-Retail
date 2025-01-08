#include "Challenges/RenderRetail/Plain.h"
#include "AssetManager/AssetManager.h"

Plain::Plain(glm::vec3 position, glm::vec2 size, glm::vec3 orientation)
    : position(position), size(size), orientation(orientation) {

  static std::vector<Plain::Vertex> vertices = {
      Vertex{{0., 0., 0.}, {0, 0}, {0.0,0.0,1.0}},
      Vertex{{1., 0., 0.}, {1, 0}, {0.0,0.0,1.0}},
      Vertex{{0., 1., 0.}, {0, 1}, {0.0,0.0,1.0}},
      Vertex{{1., 1., 0.}, {1, 1}, {0.0,0.0,1.0}}};
  static std::vector<GLuint> indices = {0, 1, 2, 1, 2, 3};
  vertexArray = std::make_shared<VertexArray>(vertices, indices);
  vertexArray->addVertexAttributes(Plain::Vertex::vertexAttributes(),
                                   sizeof(Plain::Vertex));
  shaderProgram = AssetManager::instance().loadShaderProgram("Plain");
  // Compute the model matrix
  model = glm::mat4(1.0f);
  model = glm::translate(model, position);

  glm::vec3 defaultNormal(
      0.f, 0.f, 1.f); // Assuming the Plain initially faces the +Z direction
  orientation = glm::normalize(orientation);
  glm::vec3 axis = glm::cross(defaultNormal, orientation);
  float angle = glm::acos(glm::dot(defaultNormal, orientation));

  if (glm::length(axis) >
      0.0001f) { // Avoid invalid axis when vectors are aligned
    model = glm::rotate(model, angle, glm::normalize(axis));
  }

  model = glm::scale(model, glm::vec3(size, 1.0f));
}

Plain::Plain(glm::vec3 position, glm::vec2 size, glm::vec3 orientation,
             glm::vec3 color)
    : Plain(position, size, orientation) {
  this->color = color;
}
Plain::Plain(glm::vec3 position, glm::vec2 size, glm::vec3 orientation,
             const std::string &textureName)
    : Plain(position, size, orientation) {
  useTexture = 1;
  texture = AssetManager::instance().loadTexture(textureName);
}
void Plain::update(float dt) {}

void Plain::render(glm::mat4 &mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
  shaderProgram->setMat4("MVP", mvp);
  shaderProgram->setVec3("lightPos", lightPos);
  shaderProgram->setVec3("lightColor", lightColor);
  shaderProgram->setVec3("viewPos", viewPos);
  shaderProgram->setMat4("model", model);
  shaderProgram->setVec3("color", color);
  shaderProgram->setVec2("scale", size);
  shaderProgram->setInt("useTexture", useTexture);
  if (useTexture)
    shaderProgram->setTexture("textureSlot", texture, 1);
  shaderProgram->activate();
  vertexArray->renderIndexed();
}

void Plain::onKeyEvent(int32_t key, int32_t scancode, int32_t action,
                       int32_t mode) {}