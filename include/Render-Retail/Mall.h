#pragma once

#include "Objects/Box.h"
#include "Objects/Object.h"
#include "Render-Retail/ClothingStore.h"
#include "Render-Retail/BookStore.h"
#include "Render-Retail/Objects/Columns.h"
#include "Render-Retail/DepartmentStore.h"
#include "core.h"

class Mall : public Object {
   public:
    Mall();
    void update(float dt) override;
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;

   private:
    std::shared_ptr<Box> m_body;
    std::shared_ptr<ClothingStore> m_clothingStore;
    std::shared_ptr<BookStore> m_bookStore;
    std::shared_ptr<Columns> m_columns;
    std::shared_ptr<DepartmentStore> m_departmentStore;
};
