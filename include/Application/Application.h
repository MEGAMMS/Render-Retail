#pragma once

#include "Application/Scene.h"
#include "core/Window.h"
<<<<<<< HEAD
#include "Challenges/SquarePlayer.h"
#include "Challenges/TriangleExample.h"
#include "Challenges/TextureExample.h"
#include "Challenges/Pyramid.h"
#include "Challenges/Cubes.h"
#include "AngryNeighbor/AngryNeighbor.h"
=======
>>>>>>> e38afa02146e740d334799357ce72ad028b60d81

class Application {
private:
    static Application* instancePtr;
    std::unique_ptr<Window> window;

    std::vector<std::shared_ptr<Scene>> scenes = std::vector<std::shared_ptr<Scene>>();

public:
    Application();
    Application(const Application&) = delete;
    Application(Application&) = delete;
    Application(Application&&) noexcept = delete;
    Application& operator=(Application&) = delete;
    Application& operator=(Application&&) noexcept = delete;

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
    void onCursorPositionEvent(double x, double y);
    void onResized();

    inline static Application& instance() { return *instancePtr; };

    void run();

};
