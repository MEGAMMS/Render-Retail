#pragma once

#include "core.h"
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Object {
   private:
    void updateModelMatrix() {
        model = glm::mat4(1.f);
        model = glm::translate(model, position);

        auto [angle, axis] = orientationToAngleAxis(orientation, defaultOrientation);
        model = glm::rotate(model, angle, glm::normalize(axis));

        model = glm::scale(model, size);
    };

   public:
    glm::vec3 defaultOrientation = glm::vec3(0.f, 0.f, 1.f);  // Assuming the plane initially faces the +Z direction
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
        return parent->getModel() * model;
    };

   private:
    std::pair<float, glm::vec3> orientationToAngleAxis(const glm::vec3& targetOrientation,
                                                       const glm::vec3& baseOrientation = glm::vec3(0.0f, 0.0f, 1.0f)) {
        // Ensure the orientations are normalized
        glm::vec3 normTarget = glm::normalize(targetOrientation);
        glm::vec3 normBase = glm::normalize(baseOrientation);

        // Calculate the angle between the vectors
        float dotProduct = glm::dot(normTarget, normBase);
        dotProduct = glm::clamp(dotProduct, -1.0f, 1.0f);  // Clamp for numerical stability
        float angle = glm::acos(dotProduct);

        // Calculate the rotation axis (cross product)
        glm::vec3 axis = glm::cross(normBase, normTarget);

        // Handle the case where the axis length is very small (parallel vectors)
        if (glm::length(axis) < 1e-6f) {
            axis = glm::vec3(1.0f, 0.0f, 0.0f);  // Default axis
            if (dotProduct < 0.0f) {             // Special case for 180-degree rotation
                axis = glm::vec3(0.0f, 1.0f, 0.0f);
            }
        } else {
            axis = glm::normalize(axis);  // Normalize the axis
        }

        return {angle, axis};
    }
};
