#include "Application/Application.h"

float dt = 0.016f;
float frameStart = 0.0f;

Application* Application::instancePtr = nullptr;

Application::Application() {
    assert(instancePtr == nullptr && "The application is already instantiated");
    instancePtr = this;

    window = std::make_unique<Window>();
    square = std::make_unique<SquarePlayer>();
    triangle = std::make_unique<TriangleExample>();
}
void Application::run() {

    // render loop
    // -----------
    while (!window->shouldClose()) {
        window->update();

        dt = glfwGetTime() - frameStart;
        frameStart = glfwGetTime();

        // square->update(dt);
        triangle->update();

        // Swap the back buffer with the front buffer
        window->finalizeFrame();
        // Take care of all GLFW events
        window->pollEvents();
    }
    square->Delete();

}
void Application::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    // square->onKeyEvent(key, scancode, action, mode);
    triangle->onKeyEvent(key,scancode,action,mode);
}