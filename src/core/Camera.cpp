#include "core/Camera.h"



glm::mat4 Camera::calcView() {
    return glm::lookAt(position, position + front, up);
}

glm::mat4& Camera::updateView() {
    return view = calcView();
}

void Camera::updateDirection(glm::vec3 newForward) {
    front = newForward;
    newForward.y = 0;
    directions[DirectionName::Forward].direction = glm::normalize(newForward);
    directions[DirectionName::Backward].direction = -directions[DirectionName::Forward].direction;

    directions[DirectionName::Right].direction = glm::normalize(glm::cross(newForward, up));
    directions[DirectionName::Left].direction = -directions[DirectionName::Right].direction;
}

void Camera::updateOrientation() {
    updateDirection(glm::normalize(glm::vec3{
     glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
     glm::sin(glm::radians(pitch)),
     glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
        }));
}

glm::mat4& Camera::setPosition(glm::vec3 eye) {
    position = eye;
    return updateView();
}

glm::mat4& Camera::lookAt(glm::vec3 eye, glm::vec3 center) {
    position = eye;
    updateDirection(center);
    return updateView();
}

void Camera::update(float deltaTime) {
    auto moveDirection = glm::vec3(0);

    for (const auto& [isMoving, direction] : directions) {
        if (!isMoving) {
            continue;
        }

        moveDirection += direction;
    }
    float movementSpeed = isRunning ? runningSpeed : walkingSpeed;
    auto posOffset = glm::length(moveDirection) != 0 ?
        glm::normalize(moveDirection) * movementSpeed * deltaTime : glm::vec3(0);
    position += posOffset;
    updateOrientation();
    updateView();
}

void Camera::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    bool pressed = action == GLFW_PRESS;
    if (key == GLFW_KEY_W)directions[DirectionName::Forward].isMoving = pressed;
    if (key == GLFW_KEY_S)directions[DirectionName::Backward].isMoving = pressed;
    if (key == GLFW_KEY_A)directions[DirectionName::Left].isMoving = pressed;
    if (key == GLFW_KEY_D)directions[DirectionName::Right].isMoving = pressed;
    if (key == GLFW_KEY_LEFT_SHIFT)directions[DirectionName::Down].isMoving = pressed;
    if (key == GLFW_KEY_SPACE)directions[DirectionName::Up].isMoving = pressed;
    if (key == GLFW_KEY_LEFT_CONTROL)isRunning = pressed;
}

void Camera::onCursorPositionEvent(double x, double y) {
    if (resetMouse) {
        resetMouse = false;
        lastX = x;
        lastY = y;
    }

    float xoffset = static_cast<float>(x - lastX);
    float yoffset = static_cast<float>(lastY - y);

    yaw += xoffset * mouseSensitivity.x;
    pitch += yoffset * mouseSensitivity.y;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    lastX = x;
    lastY = y;
}

glm::vec3 Camera::getPosition() {
    return position;
}

glm::vec3 Camera::getLookDirection() {
    return front;
}

void Camera::resetMousePosition() {
    resetMouse = true;
}
