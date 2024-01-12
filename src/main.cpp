#include "core.h"
#include "core/Window.h"

void processInput(Window window);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    // glfw: initialize and configure
    // ------------------------------
    Window window(SCR_WIDTH, SCR_HEIGHT, "LearningOpenGL");
    window.installMainCallbacks();
    glfwSetKeyCallback(window.nativeWindow,keyCallback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        Error::exitWithMassage("Failed to initialize GLAD");
    }

    // render loop
    // -----------
    int isFullscreen = window.isFullscreen();

    while (!glfwWindowShouldClose(window.nativeWindow)) {
        window.updateView();
        // input
        // -----
        processInput(window);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window.nativeWindow);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(Window window) {
    
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_REPEAT)return;
    std::cout << key << " " << action << std::endl;
    

}

