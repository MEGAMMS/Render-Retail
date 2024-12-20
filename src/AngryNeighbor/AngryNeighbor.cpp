#include "AngryNeighbor/AngryNeighbor.h"
#include "AngryNeighbor/MoonAndSun.h"
#include "Challenges/Cubes/LightCube.h"

AngryNeighbor::AngryNeighbor() {
    camera = std::make_shared<Camera>();
    camera->setPosition(glm::vec3(0, 2, 0));
    camera->walkingSpeed = 20;
    camera->runningSpeed = 200;
    this->setProjectionMatrixParams(80.f, 0.001, 100000.f);
    lightCube = std::make_shared<LightCube>(
        glm::vec3{ 1.7,9., 10. },
        // glm::vec3(.5f, 0.5f, 0.8f)
        glm::vec3(1., 1., 1.)
    );
    moonAndSun = std::make_shared<MoonAndSun>(100.0f, glm::vec3(0.8f, 0.3f, 0.0f), 30.0f);
    planes = {
        std::make_shared<Plane>(
        glm::vec3{ -60,0,60 },
        glm::vec2{ 120,120 },
        glm::vec3{ 0,1,0 },
            "assets/test-textures/dirt_128.png"),

        std::make_shared<Plane>(
        glm::vec3{ -1,0,0 },
        glm::vec2{ 19,1 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plane>(
        glm::vec3{ -1,5,0 },
        glm::vec2{ 19,1 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plane>(
        glm::vec3{ -1,10,0 },
        glm::vec2{ 19,1 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plane>(
        glm::vec3{ -1,1,0 },
        glm::vec2{ 1,9 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plane>(
        glm::vec3{ 10,1,0 },
        glm::vec2{ 1,9 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plane>(
        glm::vec3{ 17,1,0 },
        glm::vec2{ 1,9 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),



    };
    boxes = {
        std::make_shared<Box>(
            glm::vec3{ 0,1,0 },
            glm::vec3{ 10,5,4},
            glm::vec3{ 0,1,0 },
            std::vector<int>{1,2,4,5,6},
            // glm::vec3{0.3,0.5,0.9}
            "assets/test-textures/default_pine_wood.png"
            ),
        std::make_shared<Box>(
            glm::vec3{ 11,1,0 },
            glm::vec3{ 7,5,4},
            glm::vec3{ 0,1,0 },
            std::vector<int>{1,2,4,5,6},
            // glm::vec3{0.3,0.5,0.9}
            "assets/test-textures/default_pine_wood.png"
            ),
        std::make_shared<Box>(
            glm::vec3{ 11,6,0 },
            glm::vec3{ 7,5,4},
            glm::vec3{ 0,1,0 },
            std::vector<int>{1,2,4,5,6},
            // glm::vec3{0.3,0.5,0.9}
            "assets/test-textures/default_pine_wood.png"
            ),
        std::make_shared<Box>(
            glm::vec3{ 0,6,0 },
            glm::vec3{ 10,5,4},
            glm::vec3{ 0,1,0 },
            std::vector<int>{1,2,4,5,6},
            // glm::vec3{0.3,0.5,0.9}
            "assets/test-textures/default_pine_wood.png"
            ),
        std::make_shared<Box>(
            glm::vec3{ 7,1.01,-4 + 0.01},
            glm::vec3{ 1,1,2},
            glm::vec3{ 0,1,0 },
            std::vector<int>{1,2,4,5,6},
            "assets/test-textures/fridgeWall.png"
            ),
        std::make_shared<Box>(
            glm::vec3{ 4,1.01,-4 + 0.01},
            glm::vec3{ 1,1,1},
            glm::vec3{ 0,1,0 },
            std::vector<int>{1,2,3,4,5,6},
            "assets/test-textures/fridgeWall.png"
            ),
        std::make_shared<Box>(
            glm::vec3{ 4,3.01,-4 + 0.01},
            glm::vec3{ 1,1,1},
            glm::vec3{ 0,1,0 },
            std::vector<int>{1,2,3,4,5,6},
            "assets/test-textures/fridgeWall.png"
            ),

    };

    doors = {
        std::make_shared<Door>(
            glm::vec3{ 0.01,1,-2 },
            glm::vec2{ 1,2 },
            glm::vec3{ 1,0,0 },
            GLFW_KEY_1,
            "assets/test-textures/doors_wood.png"),

            std::make_shared<Door>(
        glm::vec3{ 7,1,-4 },
        glm::vec2{ 1,2 },
        glm::vec3{ 0,0,-1 },
        GLFW_KEY_2,
            "assets/test-textures/fridge.png")
    };

}
void AngryNeighbor::update(float dt) {
    camera->update(dt);
    lightCube->update(dt);
    moonAndSun->update(dt);
    for (auto door : doors)
        door->update(dt);
    mvp = projection * camera->getViewMatrix();
}

void AngryNeighbor::render() {
    // auto lightPos = lightCube->getLightPos();
    // auto lightColor = lightCube->getLightColor();
    auto lightPos = moonAndSun->getLightPos();
    auto lightColor = moonAndSun->getLightColor();
    auto viewPos = camera->getPosition();
    std::cerr << lightPos.y << std::endl;
    // cube->render(mvp, lightPos, lightColor, viewPos);
    // lightCube->render(mvp);
    moonAndSun->render(mvp);
    for (auto plane : planes)
        plane->render(mvp, lightPos, lightColor, viewPos);
    for (auto box : boxes)
        box->render(mvp, lightPos, lightColor, viewPos);
    for (auto door : doors)
        door->render(mvp, lightPos, lightColor, viewPos);

}

void AngryNeighbor::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    camera->onKeyEvent(key, scancode, action, mode);
    moonAndSun->onKeyEvent(key, scancode, action, mode);
    for (auto door : doors)door->onKeyEvent(key, scancode, action, mode);

}
void AngryNeighbor::onCursorPositionEvent(double x, double y) {
    camera->onCursorPositionEvent(x, y);
}
