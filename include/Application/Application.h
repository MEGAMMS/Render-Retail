#pragma once

#include "core.h"
#include "core/Window.h"

class Application {
private:
    static Application* instancePtr;
    std::unique_ptr<Window> window;


public:
    Application();
    Application(const Application&) = delete;
    Application(Application&) = delete;
    Application(Application&&) noexcept = delete;
    Application& operator=(Application&) = delete;
    Application& operator=(Application&&) noexcept = delete;

    inline static Application& instance() { return *instancePtr; };

    void run();

};