#include "Render-Retail/Objects/MoonAndSun.h"
#include <memory>

MoonAndSun::MoonAndSun(float radius, glm::vec3 normalVector,
                       float rotationSpeed)
    : sun(glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 0.9f)),  // Sun: yellow light
      moon(glm::vec3(0.0f), glm::vec3(0.4f, 0.4f, 0.85f)), // Moon: gray light
      normalVector(glm::normalize(normalVector)), radius(radius),
      rotationSpeed(rotationSpeed), currentAngle(0.0f), isRotating(true) {
  isRotating = true;
  moonModel = std::make_shared<Model>("assets/objects/planet/planet.obj");
}

void MoonAndSun::update(float dt) {
  if (isRotating) {
    currentAngle += rotationSpeed * dt; // Increment the angle
    if (currentAngle >= 360.0f)
      currentAngle -= 360.0f; // Keep angle within bounds
  }
  // Base position is the center of the circle (assume origin)
  glm::vec3 basePosition = glm::vec3(0.0f);

  glm::mat4 model = glm::mat4(1.);
  float minValue = std::min({normalVector.x, normalVector.y, normalVector.z});
  if (minValue == normalVector.x)
    model =
        glm::translate(glm::mat4(1.), glm::vec3(radius, 0.0f, 0.0f)) * model;
  if (minValue == normalVector.y)
    model =
        glm::translate(glm::mat4(1.), glm::vec3(0.0f, radius, 0.0f)) * model;
  if (minValue == normalVector.z)
    model =
        glm::translate(glm::mat4(1.), glm::vec3(0.0f, 0.0f, radius)) * model;

  model = glm::rotate(glm::mat4(1.), glm::radians(currentAngle), normalVector) *
          model;
  glm::vec3 sunPos = glm::vec3(model * glm::vec4(0, 0, 0, 1));

  model = glm::rotate(glm::mat4(1.), glm::radians(180.f), normalVector) * model;
  glm::vec3 moonPos = glm::vec3(model * glm::vec4(0, 0, 0, 1));
  // Update the positions in their respective LightCubes
  // sunPos.y = std::max(sunPos.y, 0.0f);   // Clamp below-ground Sun to 0
  // moonPos.y = std::max(moonPos.y, 0.0f); // Clamp below-ground Moon to 0

  sun.updatePos(sunPos);
  moon.updatePos(moonPos);
  moonModel->setPosition(moonPos);

  sun.update(dt);
  moon.update(dt);
}

void MoonAndSun::render(glm::mat4 mvp) {
  sun.render(mvp);
  moon.render(mvp);
  moonModel->render(mvp, glm::vec3(0),glm::vec3(1), glm::vec3(0)); 
}

glm::vec3 MoonAndSun::getLightColor() {
  // Return the color of the Sun or Moon depending on which is above ground
  return (sun.getLightPos().y > 0.0f) ? sun.getLightColor()
                                      : moon.getLightColor();
}

glm::vec3 MoonAndSun::getLightPos() {
  // Return the position of the Sun or Moon depending on which is above ground
  return (sun.getLightPos().y > 0.0f) ? sun.getLightPos() : moon.getLightPos();
}

void MoonAndSun::onKeyEvent(int32_t key, int32_t scancode, int32_t action,
                            int32_t mode) {
  // Toggle rotation on key press
  if (action == GLFW_PRESS && key == GLFW_KEY_R) {
    isRotating = !isRotating;
  }
}
