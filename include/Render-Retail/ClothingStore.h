#pragma once

#include "Objects/Box.h"
#include "Objects/Object.h"
#include "Render-Retail/Objects/Clothes.h"
#include "Render-Retail/Objects/Hanger.h"
#include "Render-Retail/Objects/Lamp.h"
#include "Render-Retail/Objects/Shelves.h"
#include "Render-Retail/Objects/Shirt/Shirt.h"
#include "Render-Retail/Objects/Table.h"
#include "Render-Retail/Objects/Wardrobe.h"
#include "Render-Retail/Stores/StoreWalls.h"
#include "Render-Retail/Stores/FrontWall.h"
#include "core.h"

class ClothingStore : public Object {
   public:
    ClothingStore();
    void update(float dt) override;
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;

   private:
    std::shared_ptr<StoreWalls> m_room;
    std::shared_ptr<Table> m_desk;
    std::shared_ptr<Shelves> m_shelf;
    std::shared_ptr<Lamp> m_lamp;
    std::shared_ptr<FrontWall> m_frontWall;
    std::vector<std::shared_ptr<Clothes>> m_clothes;
};
