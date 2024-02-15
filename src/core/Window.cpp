#include "core/Window.h"
#include "Error.h"
#include "Application/Application.h"

Window* Window::instancePtr = nullptr;
bool Window::_updateViewport = true;
Window::Window() {
    assert(instancePtr == nullptr && "The window is already instantiated");
    instancePtr = this;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    _window = glfwCreateWindow(windowWidth, windowHeight, name, nullptr, nullptr);
    glfwMakeContextCurrent(_window);

    if (_window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return;
    }

    if (!setupGlad()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        _window = nullptr;
        return;
    }


    installMainCallbacks();

    _monitor = glfwGetPrimaryMonitor();
    _updateViewport = true;

}
void Window::setFullscreen(bool fullscreen) {
    if (isFullscreen() == fullscreen)
        return;

    if (fullscreen) {
        // backup window position and window size
        glfwGetWindowSize(_window, &windowWidth, &windowHeight);
        // get resolution of monitor
        const GLFWvidmode* mode = glfwGetVideoMode(_monitor);

        // switch to full screen
        glfwSetWindowMonitor(_window, _monitor, 0, 0, mode->width, mode->height, 0);
    } else {
        // restore last window size and position
        glfwSetWindowMonitor(_window, nullptr, 100, 100, windowWidth, windowHeight, 0);
    }

    _updateViewport = true;
}

bool Window::isFullscreen() {
    return glfwGetWindowMonitor(_window) != nullptr;
}

void Window::finalizeFrame() {
    glfwSwapBuffers(_window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::update() {
    updateView();
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::installMainCallbacks() {
    glfwSetKeyCallback(_window, onKeyEvent);
    glfwSetMouseButtonCallback(_window, onMouseButtonEvent);
    glfwSetCursorPosCallback(_window, onCursorPosition);
    glfwSetFramebufferSizeCallback(_window, onResized);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(onOpenGlMessage, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    // glfwSwapInterval(2);

    glfwSetWindowRefreshCallback(_window, onRefreshWindow);
    glfwSetErrorCallback(Window::onWindowError);

}

void Window::updateView() {
    if (_updateViewport) {
        int currWidth, currHeight;
        glfwGetFramebufferSize(_window, &currWidth, &currHeight);
        glViewport(0, 0, currWidth, currHeight);
        _updateViewport = false;
    }
}

void Window::close() {
    glfwSetWindowShouldClose(_window, GLFW_TRUE);
}

Window::~Window() {
    instancePtr = nullptr;
    glfwTerminate();
}

bool Window::setupGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        return false;
    }

    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);

    return true;
}

void Window::onKeyEvent(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    if(action == GLFW_REPEAT)return;
    if (key == GLFW_KEY_F11 and action == GLFW_PRESS)Window::instance().setFullscreen(!instance().isFullscreen());
    if (key == GLFW_KEY_ESCAPE and action == GLFW_PRESS)Window::instance().close();
    Application::instance().onKeyEvent(key, scancode, action, mode);
}

void Window::onResized(GLFWwindow* window, int32_t width, int32_t height) {
    _updateViewport = true;
}

void Window::onMouseButtonEvent(GLFWwindow* window, int32_t button, int32_t action, int32_t mods) {
}

void Window::onCursorPosition(GLFWwindow* window, double x, double y) {
}

void Window::onRefreshWindow(GLFWwindow* window) {
}

void Window::onWindowError(int32_t errorCode, const char* description) {
    std::cerr << "GLFW: **ERROR** error=" << errorCode << " description=" << description << std::endl;
}

void GLAPIENTRY Window::onOpenGlMessage(GLenum source,
                                        GLenum type,
                                        GLuint id,
                                        GLenum severity,
                                        GLsizei,
                                        const GLchar *message,
                                        const void *) {
  if (id == 131185 || id == 131218) {
    return;
  }

  std::cerr << "---------------" << std::endl;
  std::cerr << "Debug message (" << id << "): " << message << std::endl;

  switch (source) {
    case GL_DEBUG_SOURCE_API:
      std::cerr << "Source: API";
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      std::cerr << "Source: Window System";
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      std::cerr << "Source: Shader Compiler";
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      std::cerr << "Source: Third Party";
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      std::cerr << "Source: Application";
      break;
    case GL_DEBUG_SOURCE_OTHER:
      std::cerr << "Source: Other";
      break;
    default:
      break;
  }
  std::cerr << std::endl;

  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      std::cerr << "Type: Error";
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      std::cerr << "Type: Deprecated Behaviour";
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      std::cerr << "Type: Undefined Behaviour";
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      std::cerr << "Type: Portability";
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      std::cerr << "Type: Performance";
      break;
    case GL_DEBUG_TYPE_MARKER:
      std::cerr << "Type: Marker";
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      std::cerr << "Type: Push Group";
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      std::cerr << "Type: Pop Group";
      break;
    case GL_DEBUG_TYPE_OTHER:
      std::cerr << "Type: Other";
      break;
    default:
      break;
  }
  std::cerr << std::endl;

  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      std::cerr << "Severity: high";
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      std::cerr << "Severity: medium";
      break;
    case GL_DEBUG_SEVERITY_LOW:
      std::cerr << "Severity: low";
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      std::cerr << "Severity: notification";
      break;
    default:
      break;
  }
  std::cerr << std::endl;
  std::cerr << std::endl;
}
