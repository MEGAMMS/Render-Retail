#pragma once

#include "core.h"

class Camera {
    struct MovementDirection {
        bool isMoving = false;
        glm::vec3 direction = glm::vec3(0);
    };
    enum DirectionName {
        Forward, Backward, Left, Right, Up, Down
    };

    MovementDirection directions[6] = {
        {false, {1, 0, 0}},  {false, {-1, 0, 0}}, {false, {0, 0, 1}},
        {false, {0, 0, -1}}, {false, {0, 1, 0}},  {false, {0, -1, 0}},
    };
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 4.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX, lastY;


    float walkingSpeed = 10.317;
    float runningSpeed = 10.321;
    glm::vec2 mouseSensitivity = glm::vec2(0.2);

    bool resetMouse = true;
    bool isRunning = false;

    glm::mat4 calcView();
    glm::mat4& updateView();
    glm::mat4 view = calcView();

    void updateDirection(glm::vec3 newForward);
    void updateOrientation();

public:
    Camera() {};

    glm::mat4& setPosition(glm::vec3 eye);
    glm::mat4& lookAt(glm::vec3 eye, glm::vec3 center);

    [[nodiscard]] glm::mat4& getViewMatrix() { return view; }

    void update(float deltaTime);

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
    void onCursorPositionEvent(double x, double y);
    glm::vec3 getPosition();
    glm::vec3 getLookDirection();

    void resetMousePosition();
};