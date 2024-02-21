#pragma once

#include "core.h"
#include "core/Window.h"
#include "Challenges/SquarePlayer.h"
#include "Challenges/TriangleExample.h"
#include "Challenges/TextureExample.h"

class Application {
private:
    static Application* instancePtr;
    std::unique_ptr<Window> window;

    std::unique_ptr<TriangleExample> triangle;
    std::unique_ptr<SquarePlayer> square;
    std::unique_ptr<TextureExample> textureExample;

public:
    Application();
    Application(const Application&) = delete;
    Application(Application&) = delete;
    Application(Application&&) noexcept = delete;
    Application& operator=(Application&) = delete;
    Application& operator=(Application&&) noexcept = delete;

    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);

    inline static Application& instance() { return *instancePtr; };

    void run();

};