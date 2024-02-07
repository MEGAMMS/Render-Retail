#include "Application/Application.h"
#include "shaderClass.h"
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"


// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES                  
  -1.,-1.,
  1.,-1.,
  -1.,1.,
  1.,1.

};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    3, 1, 2
};

bool move = 0;
float dt = 0.016f;
float frameStart = 0.0f;



Application* Application::instancePtr = nullptr;

Application::Application() {
    assert(instancePtr == nullptr && "The application is already instantiated");
    instancePtr = this;

    window = std::make_unique<Window>();

}
void Application::run() {
    // Generates Shader object using shaders defualt.vert and default.frag
    Shader shaderProgram("assets/shaders/default.vert", "assets/shaders/default.frag");
    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*) 0);
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    shaderProgram.Activate();
    GLuint timeUniID = glGetUniformLocation(shaderProgram.ID, "u_time");
    GLuint resUniID = glGetUniformLocation(shaderProgram.ID, "u_resolution");
    glUniform2f(resUniID, window->getWindowWidth(), window->getWindowHeight());


    GLuint moveUniID = glGetUniformLocation(shaderProgram.ID, "u_move");
    // render loop
    // -----------
    float pos = 0;
    while (!window->shouldClose()) {
        window->update();

        dt = glfwGetTime() - frameStart;
        frameStart = glfwGetTime();
        if (move)pos += 0.2 * dt;
        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();
        glUniform1f(timeUniID, glfwGetTime());
        glUniform1f(moveUniID, pos);
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) (0 * sizeof(GLuint)));

        // Swap the back buffer with the front buffer
        window->finalizeFrame();
        // Take care of all GLFW events
        window->pollEvents();
    }
    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

}
void Application::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    if (key == GLFW_KEY_RIGHT)move = action == GLFW_PRESS;

}