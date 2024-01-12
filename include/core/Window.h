#ifndef WINDOW_H
#define WINDOW_H
#include "core.h"
#include "array"

class Window {
public:
    GLFWwindow* nativeWindow;
    std::array< int, 2 > _wndPos;
    std::array< int, 2 > _wndSize;
    std::array< int, 2 > _vpSize;
    bool _updateViewport;
    GLFWmonitor* _monitor;
    Window(int width, int height, const char* title, bool fullScreenMode = false);
    void setFullscreen(bool fullscreen);
    bool isFullscreen();
    void installMainCallbacks();
    void Resize(int cx, int cy);
    void updateView();
    void close();
};

#endif 