#pragma once

#include "core.h"
#include "glm/gtc/matrix_transform.hpp"

class Object {
   public:
    glm::mat4 model;
    std::shared_ptr<Object> parent;

    glm::vec3 position;
    glm::vec3 size;

    Object() : model(1.f), position(glm::vec3(0.f)), size(glm::vec3(1.f)) {};
    virtual ~Object() = default;

    void setPosition(const glm::vec3 in_Position) {
        position = in_Position;
        updateModelMatrix();
    };
    void setSize(const glm::vec3 in_Size) {
        size = in_Size;
        updateModelMatrix();
    };

    // Virtual methods to be implemented by each object
    virtual void update(float dt) {};
    virtual void render() {};
    virtual void onCursorPositionEvent(double x, double y) {}
    virtual void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}

    void setParent(std::shared_ptr<Object> in_Parent) { parent = in_Parent; };
    glm::mat4 getModel() {
        if (parent == nullptr) return model;
        return model * parent->getModel();
    };

   private:
    void updateModelMatrix() {
        model = glm::mat4(1.f);
        model = glm::translate(model, position);
        model = glm::scale(model, size);
    };
};
