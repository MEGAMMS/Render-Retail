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
    glUniform2f(resUniID,window->getWindowWidth(),window->getWindowHeight());
    // render loop
    // -----------
    while (!window->shouldClose()) {
        window->update();
        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();
        glUniform1f(timeUniID, glfwGetTime());
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