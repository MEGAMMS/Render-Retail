#pragma once

#include "Objects/Box.h"
#include "Objects/Object.h"
#include "Render-Retail/Objects/Door.h"
#include "core.h"

class Elevator : public Object {
   public:
    Elevator(float highet = 4.f);
    struct status {
        float highet;
        int speed = 2.f;
        bool up = false;
        bool comingUp = false;
        bool comingDown = false;
        float currentHighet = 0;

        void chagneStatus() {
            up = !up;
            comingUp = up;
            comingDown = !up;
        }

        void update(float dt) {
            currentHighet += (comingUp * speed - comingDown * speed) * dt;
            currentHighet = std::min(highet, std::max(0.f, currentHighet));
            if (currentHighet == highet) comingUp = false;
            if (currentHighet == 0.f) comingDown = false;
        }
    } status;
    void update(float dt) override;
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void setDoorTexture(const std::string& texturePath, glm::vec2 textureScale = glm::vec2(1.f));
    void setBodyTexture(const std::string& texturePath, glm::vec2 textureScale = glm::vec2(1.f));
    void onCursorPositionEvent(double x, double y) override;

   private:
    std::shared_ptr<Object> m_root;
    std::shared_ptr<Box> m_body;
    std::shared_ptr<Door> m_door;
};
