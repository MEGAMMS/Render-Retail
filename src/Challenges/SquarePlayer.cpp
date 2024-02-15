#include "Challenges/SquarePlayer.h"



void SquarePlayer::setup() {
    Window &window = Window::instance();
    // Generates Shader object using shaders defualt.vert and default.frag
    VAO1.Bind();


    // Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*) 0);
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    shaderProgram.Activate();
    timeUniID = glGetUniformLocation(shaderProgram.ID, "u_time");
    resUniID = glGetUniformLocation(shaderProgram.ID, "u_resolution");
    glUniform2f(resUniID, window.getWindowWidth(), window.getWindowHeight());


    moveUniID = glGetUniformLocation(shaderProgram.ID, "u_move");

}
void SquarePlayer::destroy() {
    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
}

void SquarePlayer::update(float dt) {
    if (move)pos += 0.2 * dt;
    // Tell OpenGL which Shader Program we want to use
    shaderProgram.Activate();
    glUniform1f(timeUniID, glfwGetTime());
    glUniform1f(moveUniID, pos);
    // Bind the VAO so OpenGL knows to use it
    VAO1.Bind();
    // Draw primitives, number of indices, datatype of indices, index of indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) (0 * sizeof(GLuint)));
}
