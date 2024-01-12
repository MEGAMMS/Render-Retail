#include "core/Window.h"
#include "Error.h"

Window::Window(int width, int height, const char* title, bool fullscreen) {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    nativeWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (nativeWindow == NULL) {
        glfwTerminate();
        Error::exitWithMassage("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(nativeWindow);

    glfwSetWindowUserPointer(nativeWindow, this);

    _monitor = glfwGetPrimaryMonitor();
    glfwGetWindowSize(nativeWindow, &_wndSize[0], &_wndSize[1]);
    glfwGetWindowPos(nativeWindow, &_wndPos[0], &_wndPos[1]);
    _updateViewport = true;

}
void Window::setFullscreen(bool fullscreen) {
    if (isFullscreen() == fullscreen)
        return;

    if (fullscreen) {
        // backup window position and window size
        glfwGetWindowPos(nativeWindow, &_wndPos[0], &_wndPos[1]);
        glfwGetWindowSize(nativeWindow, &_wndSize[0], &_wndSize[1]);

        // get resolution of monitor
        const GLFWvidmode* mode = glfwGetVideoMode(_monitor);

        // switch to full screen
        glfwSetWindowMonitor(nativeWindow, _monitor, 0, 0, mode->width, mode->height, 0);
    } else {
        // restore last window size and position
        glfwSetWindowMonitor(nativeWindow, nullptr, _wndPos[0], _wndPos[1], _wndSize[0], _wndSize[1], 0);
    }

    _updateViewport = true;
}
bool Window::isFullscreen() {
    return glfwGetWindowMonitor(nativeWindow) != nullptr;
}
void Window::installMainCallbacks() {
    

}
void Window::Resize(int cx, int cy) {
    _updateViewport = true;
}
void Window::updateView() {
    if (_updateViewport) {
        glfwGetFramebufferSize(nativeWindow, &_vpSize[0], &_vpSize[1]);
        glViewport(0, 0, _vpSize[0], _vpSize[1]);
        _updateViewport = false;
    }
}
void Window::close() {
    glfwSetWindowShouldClose(nativeWindow, GLFW_TRUE);
}

