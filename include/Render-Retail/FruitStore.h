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
#include "Objects/Model.h"
#include "core.h"

class FruitStore : public Object {
   public:
    FruitStore();
    void update(float dt) override;
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;

   private:
    std::shared_ptr<StoreWalls> m_room;
    std::vector<std::shared_ptr<StoreWalls>> m_boxes;
    std::vector<std::shared_ptr<Model>> m_fruits;
    std::vector<std::shared_ptr<Box>> m_legs;
    std::shared_ptr<Table> m_desk;
    std::shared_ptr<Shelves> m_shelf;
    std::shared_ptr<Lamp> m_lamp;
    std::vector<std::shared_ptr<Clothes>> m_clothes;
};
