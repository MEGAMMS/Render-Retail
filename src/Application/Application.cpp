#include "Application/Application.h"

Application* Application::instancePtr = nullptr;

float dt = 0.016f;
float frameStart = 0.0f;

enum class Program {
    SQUARE, TRIANGLE, TEXTURE, PYRAMID, CUBES, Count
};

int programIdx = (int) Program::CUBES;


Application::Application() {
    assert(instancePtr == nullptr && "The application is already instantiated");
    instancePtr = this;

    window = std::make_unique<Window>();
    // window->setFullscreen(1);
    window->lockMouse();

    square = std::make_unique<SquarePlayer>();
    triangle = std::make_unique<TriangleExample>();
    textureExample = std::make_unique<TextureExample>();
    pyramid = std::make_unique<Pyramid>();
    cubes = std::make_unique<Cubes>();
}
void Application::run() {

    // render loop
    // -----------
    while (!window->shouldClose()) {
        window->update();

        dt = glfwGetTime() - frameStart;
        frameStart = glfwGetTime();


        switch ((Program) programIdx) {
        case Program::SQUARE:
            square->update(dt);
            break;
        case Program::TRIANGLE:
            triangle->update();
            break;
        case Program::TEXTURE:
            textureExample->update();
            break;
        case Program::PYRAMID:
            pyramid->update(dt);
            break;

        case Program::CUBES:
            cubes->update(dt);
            break;
        }



        // Swap the back buffer with the front buffer
        window->finalizeFrame();
        // Take care of all GLFW events
        window->pollEvents();
    }
    square->Delete();

}
void Application::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    square->onKeyEvent(key, scancode, action, mode);
    triangle->onKeyEvent(key, scancode, action, mode);
    textureExample->onKeyEvent(key, scancode, action, mode);
    cubes->onKeyEvent(key, scancode, action, mode);
    if (key == GLFW_KEY_SPACE and action == GLFW_PRESS)programIdx = ((++programIdx) % (int) Program::Count);
}
void Application::onCursorPosition(double x, double y) {
    cubes->onCursorPosition(x,y);
}