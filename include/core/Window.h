#ifndef WINDOW_H
#define WINDOW_H
#include "core.h"

class Window {

public:
    Window();
    Window(const Window&) = delete;
    Window(Window&) = delete;
    Window(Window&&) = delete;

    inline int32_t getWindowHeight() const { return windowHeight; }
    inline int32_t getWindowWidth() const { return windowWidth; }
    inline float getWindowAspectRatio() const { return (float) getWindowWidth() / getWindowHeight(); }
    inline glm::vec2 getWindowRes() const { return glm::vec2{ getWindowWidth(),getWindowHeight() }; }
    inline GLFWwindow* getContext() { return _window; };
    inline bool isValid() { return _window != nullptr; };
    inline bool shouldClose() const { return glfwWindowShouldClose(_window); };
    inline static Window& instance() { return *instancePtr; }

    void unlockMouse();
    void lockMouse();

    void setFullscreen(bool fullscreen);
    bool isFullscreen();
    void update();
    void finalizeFrame();
    void pollEvents();
    void close();
    ~Window();
private:

    static Window* instancePtr;

    const char* name = "glCraft";
    int32_t windowWidth = 800;
    int32_t windowHeight = 800;
    GLFWwindow* _window = nullptr;
    GLFWmonitor* _monitor = nullptr;
    std::array< int, 2 > _wndPos{ 0, 0 };
    std::array< int, 2 > _wndSize{ 0, 0 };
    static bool _updateViewport;

    glm::vec4 clearColor = { 0.17, 0.145, 0.133, 1 };


    void updateView();
    void installMainCallbacks();
    static bool setupGlad();

    static void onKeyEvent(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
    static void onResized(GLFWwindow* window, int32_t width, int32_t height);
    static void onMouseButtonEvent(GLFWwindow* window, int32_t button, int32_t action, int32_t mods);
    static void onCursorPositionEvent(GLFWwindow* window, double x, double y);
    static void onRefreshWindow(GLFWwindow* window);

    static void onWindowError(int32_t errorCode, const char* description);
    static void onOpenGlMessage(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam);
};

#endif 