#include "Render-Retail/Stores/StoreWalls.h"


#include <memory>

#include "Objects/Object.h"

StoreWalls::StoreWalls() {
        // Create six boxes for the room
        for (int i = 0; i <5; ++i) {
            walls.push_back(std::make_shared<Box>());
        }

        // Define the size of the room (example: 10x10x10 units)
        glm::vec3 roomSize(10.0f, 10.0f, 10.0f);
        // Set positions and orientations for each wall
        // Floor
        walls[0]->setPosition(glm::vec3(0.0f, -roomSize.y / 2, 0.0f));
        walls[0]->setSize(glm::vec3(roomSize.x, 1.0f, roomSize.z));

        // Ceiling
        walls[1]->setPosition(glm::vec3(0.0f, roomSize.y / 2, 0.0f));
        walls[1]->setSize(glm::vec3(roomSize.x, 1.0f, roomSize.z));

        // Back wall
        walls[2]->setPosition(glm::vec3(0.0f, -roomSize.y / 2,0.0f));
        walls[2]->setSize(glm::vec3(roomSize.x, roomSize.y, 1.0f));

        // Left wall
        walls[3]->setPosition(glm::vec3(0.0f, -roomSize.y / 2, 0.0f));
        walls[3]->setSize(glm::vec3(1.0f, roomSize.y, roomSize.z));

        // Right wall
        walls[4]->setPosition(glm::vec3(roomSize.x-1, -roomSize.y / 2, 0.0f));
        walls[4]->setSize(glm::vec3(1.0f, roomSize.y, roomSize.z));

        // Optional: Set textures for each wall
        for (int i = 0; i < 5; ++i) {
            walls[i]->setTexture("assets/brick.png");
            walls[i]->setParent(std::shared_ptr<Object>(this));
        }
}

void StoreWalls::update(float dt) {}
void StoreWalls::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    for (const auto& wall : walls) {
                wall->render(mvp, lightPos, lightColor, viewPos);
            }
}
void StoreWalls::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void StoreWalls::onCursorPositionEvent(double x, double y) {}