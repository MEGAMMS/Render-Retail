#include "Challenges/SquarePlayer.h"
#include "buffers/EBO.h"
#include "core/Window.h"


struct Vertex {
    glm::vec2 position;
};
SquarePlayer::SquarePlayer() {
    shaderProgram = std::make_shared<Shader>("assets/shaders/default.vert", "assets/shaders/default.frag");
    static std::array<Vertex, 4> vertices = {
      Vertex{ glm::vec2{-1.,-1.} },
      Vertex{ glm::vec2{1.,-1.} },
      Vertex{ glm::vec2{-1.,1.} },
      Vertex{ glm::vec2{1.,1.} }
    };
    static std::array<GLuint, 6> indices = {
        0, 1, 2,
        3, 1, 2
    };


    vao = VAO();
    vao.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo((GLfloat*) vertices.data(), sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO ebo((GLuint*) indices.data(), sizeof(indices));

    // Links VBO to VAO
    vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*) 0);
    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
    shaderProgram->Activate();

    Window& window = Window::instance();

    timeUniID = glGetUniformLocation(shaderProgram->ID, "u_time");

    resUniID = glGetUniformLocation(shaderProgram->ID, "u_resolution");
    glUniform2f(resUniID, window.getWindowWidth(), window.getWindowHeight());

    moveUniID = glGetUniformLocation(shaderProgram->ID, "u_move");
    vbo.Delete();
    ebo.Delete();
}

void SquarePlayer::update(float dt) {
    pos += move * dt;
    // Tell OpenGL which Shader Program we want to use
    shaderProgram->Activate();
    glUniform1f(timeUniID, glfwGetTime());
    glUniform2f(moveUniID, pos.x, pos.y);
    // Bind the VAO so OpenGL knows to use it
    vao.Bind();
    // Draw primitives, number of indices, datatype of indices, index of indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) (0 * sizeof(GLuint)));
}

void SquarePlayer::Delete() {
    vao.Delete();
    shaderProgram->Delete();
}
void SquarePlayer::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    if (key == GLFW_KEY_RIGHT)move.x = SPEED * (action == GLFW_PRESS);
    if (key == GLFW_KEY_LEFT)move.x = -SPEED * (action == GLFW_PRESS);
    if (key == GLFW_KEY_UP)move.y = SPEED * (action == GLFW_PRESS);
    if (key == GLFW_KEY_DOWN)move.y = -SPEED * (action == GLFW_PRESS);

}

