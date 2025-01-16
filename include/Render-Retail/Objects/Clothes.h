#pragma once

#include "Objects/Box.h"
#include "Objects/Object.h"
#include "core.h"

#include "Render-Retail/Objects/Hanger.h"
#include "Render-Retail/Objects/Shirt/Shirt.h"

class Clothes : public Object {
   public:

    Clothes(unsigned int shirts=5);
    void update(float dt) override;
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;

   private:
        std::shared_ptr<Hanger>m_hanger;
        std::vector<std::shared_ptr<Shirt>>m_shirts;
};