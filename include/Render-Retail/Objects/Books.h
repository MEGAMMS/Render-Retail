#pragma once

#include "Objects/Box.h"
#include "Objects/Object.h"
#include "Render-Retail/Objects/Lamp.h"
#include "Render-Retail/Objects/Shelves.h"
#include "Render-Retail/Objects/Table.h"
#include "Render-Retail/Objects/Wardrobe.h"
#include "Render-Retail/Stores/StoreWalls.h"
#include "core.h"

class Books : public Object {
   public:
    Books(unsigned int books);
    void update(float dt) override;
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;

   private:
    std::vector<std::shared_ptr<Box>> m_books;
};