#include "AngryNeighbor/Door.h"
#include "AssetManager/AssetManager.h"

Door::Door(glm::vec3 position, glm::vec2 size, glm::vec3 orientation,
           int32_t key)
    : position(position), size(size), orientation(orientation), key(key) {

  static std::vector<Door::Vertex> vertices = {
      Vertex{glm::vec3{0., 0., 0.}, glm::vec2{0, 0}, {0.0, 0.0, 1.0}},
      Vertex{glm::vec3{1., 0., 0.}, glm::vec2{1, 0}, {0.0, 0.0, 1.0}},
      Vertex{glm::vec3{0., 1., 0.}, glm::vec2{0, 1}, {0.0, 0.0, 1.0}},
      Vertex{glm::vec3{1., 1., 0.}, glm::vec2{1, 1}, {0.0, 0.0, 1.0}}};
  static std::vector<GLuint> indices = {0, 1, 2, 1, 2, 3};
  vertexArray = std::make_shared<VertexArray>(vertices, indices);
  vertexArray->addVertexAttributes(Door::Vertex::vertexAttributes(),
                                   sizeof(Door::Vertex));
  shaderProgram = AssetManager::instance().loadShaderProgram("Plane");
}

Door::Door(glm::vec3 position, glm::vec2 size, glm::vec3 orientation,
           int32_t key, const std::string &textureName)
    : Door(position, size, orientation, key) {
  useTexture = 1;
  texture = AssetManager::instance().loadTexture(textureName);
}
void Door::update(float dt) {
  // Compute the model matrix
  model = glm::mat4(1.0f);
  model = glm::translate(model, position);

  glm::vec3 defaultNormal(
      0.f, 0.f, 1.f); // Assuming the plane initially faces the +Z direction
  orientation = glm::normalize(orientation);
  glm::vec3 axis = glm::cross(defaultNormal, orientation);
  float angle = glm::acos(glm::dot(defaultNormal, orientation));
  if (glm::length(axis) >
      0.0001f) { // Avoid invalid axis when vectors are aligned
    model = glm::rotate(model, angle, glm::normalize(axis));
  }
  angle = (int(glfwGetTime() * 50000) % 360000) / 1000.f;
  // angle = 0;
  model = glm::rotate(model, glm::radians(open * (-90.f)),
                      glm::vec3(0.f, 1.f, 0.f));

  model = glm::scale(model, glm::vec3(size, 1.0f));
}

void Door::render(glm::mat4 &mvp, glm::vec3 lightPos, glm::vec3 lightColor,
                  glm::vec3 viewPos) {

  shaderProgram->setMat4("MVP", mvp);
  shaderProgram->setVec3("lightPos", lightPos);
  shaderProgram->setVec3("lightColor", lightColor);
  shaderProgram->setVec3("viewPos", viewPos);
  shaderProgram->setMat4("model", model);
  shaderProgram->setVec3("color", color);
  shaderProgram->setVec2("scale", glm::vec3(1, 1, 1));
  shaderProgram->setInt("useTexture", useTexture);
  if (useTexture)
    shaderProgram->setTexture("textureSlot", texture, 1);
  shaderProgram->activate();
  vertexArray->renderIndexed();
}

void Door::onKeyEvent(int32_t key, int32_t scancode, int32_t action,
                      int32_t mode) {
  bool pressed = action == GLFW_PRESS;
  if (key == this->key)
    open = pressed;
}
