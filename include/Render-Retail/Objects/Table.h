#pragma once

#include "Objects/Box.h"
#include "Objects/Object.h"
#include "core.h"

class Table : public Object
{
    public:
        Table();

        void update(float dt) override;
        void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
        void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
        void onCursorPositionEvent(double x, double y) override;
    private:
        std::shared_ptr<Box>m_body;
        std::vector<std::shared_ptr<Box>>m_legs;

};
