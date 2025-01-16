#pragma once

#include "Objects/Box.h"
#include "Objects/Object.h"
#include "Render-Retail/Objects/Shelves.h"
#include "Render-Retail/stores/StoreWalls.h"
#include "core.h"

class Wardrobe : public Object {
   public:
    Wardrobe(unsigned int shelfCount = 3);

    void update(float dt) override;
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;

    void setTexture(const std::string& texturePath);

   private:
    std::shared_ptr<StoreWalls> m_body;
    std::vector<std::shared_ptr<Shelves>> m_shelves;
};