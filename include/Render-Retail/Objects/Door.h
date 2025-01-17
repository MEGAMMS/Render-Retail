#pragma once

#include "Objects/Box.h"
#include "Objects/Object.h"
#include "core.h"

class Door : public Object {
   public:
    Door(float openDegree = 1.f);
    struct status {
        float openDegree;
        float speed;
        bool open = false;
        bool isOpening = false;
        bool isClosing = false;
        float currentDegree = 0;

        void chagneStatus() {
            open = !open;
            isOpening = open;
            isClosing = !open;
        }

        void update(float dt) {
            currentDegree += (isOpening * speed - isClosing * speed) * dt;
            currentDegree = std::min(openDegree, std::max(0.f, currentDegree));
            if (currentDegree == openDegree) isOpening = false;
            if (currentDegree == 0.f) isClosing = false;
        }
    } status;
    void update(float dt) override;
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;

   private:
    std::shared_ptr<Box> m_body;
};
