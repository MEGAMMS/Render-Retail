#pragma once

#include "Application/Scene.h"
#include "core/Window.h"

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
