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
    GLFWmonitor* primaryMonitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    nativeWindow = glfwCreateWindow(width, height, title, primaryMonitor, nullptr);

    if (nativeWindow == NULL) {
        glfwTerminate();
        Error::exitWithMassage("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(nativeWindow);

}

void Window::installMainCallbacks() {
}

void Window::close() {
    glfwSetWindowShouldClose(nativeWindow, GLFW_TRUE);
}
