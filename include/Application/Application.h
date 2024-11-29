#pragma once

#include "core.h"
#include "core/Window.h"
#include "Challenges/SquarePlayer.h"
#include "Challenges/TriangleExample.h"
#include "Challenges/TextureExample.h"
#include "Challenges/Pyramid.h"
#include "Challenges/Cubes.h"

class Application {
private:
    static Application* instancePtr;
    std::unique_ptr<Window> window;
    std::unique_ptr<TriangleExample> triangle;
    std::unique_ptr<SquarePlayer> square;
    std::unique_ptr<TextureExample> textureExample;
    std::unique_ptr<Pyramid> pyramid;
    std::unique_ptr<Scene> cubes;

public:
    Application();
    Application(const Application&) = delete;
    Application(Application&) = delete;
    Application(Application&&) noexcept = delete;
    Application& operator=(Application&) = delete;
    Application& operator=(Application&&) noexcept = delete;

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
    void onCursorPositionEvent(double x, double y);

    inline static Application& instance() { return *instancePtr; };

    void run();

};