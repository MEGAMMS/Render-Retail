#pragma once

#include "Render/Shader.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "core.h"

class Object {
public:
  glm::mat4 model;
  std::shared_ptr<Object> parent;

  Object() : model(1.0f) {};
  virtual ~Object() = default;

  // Virtual methods to be implemented by each object
  virtual void update(float dt) = 0;
  virtual void render() = 0;
  virtual void onCursorPositionEvent(double x, double y) {}
  virtual void onKeyEvent(int32_t key, int32_t scancode, int32_t action,
                          int32_t mode) {}

  void translate(glm::vec3 pos) { model = glm::translate(model, pos); };
  void rotate(float angle, glm::vec3 axis) {
    model = glm::rotate(model, glm::radians(angle), axis);
  };
  void scale(glm::vec3 scale) { model = glm::scale(model, scale); };

  void setParent(std::shared_ptr<Object> in_Parent) { parent = in_Parent; };
  glm::mat4 getModel() {
    if (parent == nullptr)
      return model;
    return model * parent->getModel();
  };
};
