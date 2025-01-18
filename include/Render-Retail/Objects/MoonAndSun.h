#pragma once

#include <memory>
#include "core.h"
#include "Render-Retail/Objects/LightCube.h"
#include "Objects/Model.h"

class MoonAndSun {
    LightCube sun;
    LightCube moon;
    std::shared_ptr<Model> moonModel;

    glm::vec3 normalVector; // The axis of rotation
    float radius;           // Radius of the rotation circle
    float rotationSpeed;    // Rotation speed in degrees per second
    float currentAngle;     // Current angle of rotation
    bool isRotating;        // State of rotation (true = rotating, false = stopped)

public:
    MoonAndSun(float radius, glm::vec3 normalVector, float rotationSpeed);

    void update(float dt);
    void render(glm::mat4 mvp);
    glm::vec3 getLightColor();
    glm::vec3 getLightPos();

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};
