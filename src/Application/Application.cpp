#include "Application/Application.h"

Application* Application::instancePtr = nullptr;

float dt = 0.016f;
float frameStart = 0.0f;

int sceneIndex = 5;


Application::Application() {
    assert(instancePtr == nullptr && "The application is already instantiated");
    instancePtr = this;

    window = std::make_unique<Window>();
    // window->setFullscreen(1);
    window->lockMouse();

    scenes.push_back(std::make_shared<SquarePlayer>());
    scenes.push_back(std::make_shared<TriangleExample>());
    scenes.push_back(std::make_shared<TextureExample>());
    scenes.push_back(std::make_shared<Pyramid>());
    scenes.push_back(std::make_shared<Cubes>());
    scenes.push_back(std::make_shared<AngryNeighbor>());

}
void Application::run() {

    // render loop
    // -----------
    while (!window->shouldClose()) {
        window->update();

        dt = glfwGetTime() - frameStart;
        frameStart = glfwGetTime();

        scenes[sceneIndex]->update(dt);
        scenes[sceneIndex]->render();
        // Swap the back buffer with the front buffer
        window->finalizeFrame();
        // Take care of all GLFW events
        window->pollEvents();
    }

}
void Application::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    scenes[sceneIndex]->onKeyEvent(key, scancode, action, mode);
    if (key == GLFW_KEY_LEFT_ALT and action == GLFW_PRESS)sceneIndex = (++sceneIndex % scenes.size());
}
void Application::onCursorPositionEvent(double x, double y) {
    scenes[sceneIndex]->onCursorPositionEvent(x, y);
}
void Application::onResized() {
    for (auto scene : scenes)scene->onResized();
};