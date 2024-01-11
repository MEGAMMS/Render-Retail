#ifndef WINDOW_H
#define WINDOW_H
#include "core.h"

class Window {
public:
    GLFWwindow* nativeWindow;
    int windowWidth;
    int windowHeight;
    Window(int width, int height, const char* title, bool fullScreenMode = false);

    void installMainCallbacks();

    void close();
};

#endif 