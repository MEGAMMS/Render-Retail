#pragma once

#include "Objects/Box.h"
#include "Objects/Object.h"
#include "core.h"

enum class Wall {
    Down,
    Up,
    Back,
    Left,
    Right,
};

class StoreWalls : public Object
{
    public:
        StoreWalls();
        void update(float dt) override;
        void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
        void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
        void onCursorPositionEvent(double x, double y) override;

        void setWallTexture(Wall wall, const std::string& texturePath);
    private:
        std::vector<std::shared_ptr<Box>>frontWall;
        std::vector<std::shared_ptr<Box>> walls;

};