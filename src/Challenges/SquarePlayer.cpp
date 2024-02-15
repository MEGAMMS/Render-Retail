#include "Challenges/SquarePlayer.h"
#include "buffers/EBO.h"
#include "core/Window.h"


SquarePlayer::SquarePlayer() {
    shaderProgram = std::make_shared<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
    GLfloat vertices[] =
    { //               COORDINATES                  
      -1.,-1.,
      1.,-1.,
      -1.,1.,
      1.,1.

    };

    GLuint indices[] =
    {
        0, 1, 2,
        3, 1, 2
    };


    VAO1 = VAO();
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
    shaderProgram->Activate();

    Window& window = Window::instance();

    timeUniID = glGetUniformLocation(shaderProgram->ID, "u_time");

    resUniID = glGetUniformLocation(shaderProgram->ID, "u_resolution");
    glUniform2f(resUniID, window.getWindowWidth(), window.getWindowHeight());

    moveUniID = glGetUniformLocation(shaderProgram->ID, "u_move");
}

void SquarePlayer::update(float dt) {
    if (move)pos += 0.2 * dt;
    // Tell OpenGL which Shader Program we want to use
    shaderProgram->Activate();
    glUniform1f(timeUniID, glfwGetTime());
    glUniform1f(moveUniID, pos);
    // Bind the VAO so OpenGL knows to use it
    VAO1.Bind();
    // Draw primitives, number of indices, datatype of indices, index of indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) (0 * sizeof(GLuint)));
}

void SquarePlayer::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    if (key == GLFW_KEY_RIGHT)move = action == GLFW_PRESS;

}

