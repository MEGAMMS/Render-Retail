#pragma once

#include "core.h"
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Object {
   private:
    const glm::vec3 defaultOrientation =
        glm::vec3(0.f, 0.f, 1.f);  // Assuming the plane initially faces the +Z direction
    void updateModelMatrix() {
        model = glm::mat4(1.f);
        model = glm::translate(model, position);

        orientation = glm::normalize(orientation);
        glm::vec3 axis = glm::cross(defaultOrientation, orientation);
        float angle = glm::acos(glm::dot(defaultOrientation, orientation));

        if (glm::length(axis) > 0.0001f) {  // Avoid invalid axis when vectors are aligned
            model = glm::rotate(model, angle, glm::normalize(axis));
        }
        model = glm::scale(model, size);
    };

   public:
    glm::mat4 model;
    std::shared_ptr<Object> parent;

    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 orientation;
    Object() : model(1.f), position(glm::vec3(0.f)), size(glm::vec3(1.f)), orientation(defaultOrientation) {};
    virtual ~Object() = default;

    void setPosition(const glm::vec3 in_Position) {
        position = in_Position;
        updateModelMatrix();
    };
    void setSize(const glm::vec3 in_Size) {
        size = in_Size;
        updateModelMatrix();
    };
    void setOrientation(const glm::vec3 in_Orientation) {
        orientation = in_Orientation;
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
};
