#include "Challenges/SquarePlayer.h"
#include "buffers/EBO.h"
#include "core/Window.h"
#include "AssetManager/AssetManager.h"



struct Vertex {
    glm::vec2 position;
};
SquarePlayer::SquarePlayer() {
    static std::array<Vertex, 4> vertices = {
      Vertex{ glm::vec2{-1.,-1.} },
      Vertex{ glm::vec2{ 1.,-1.} },
      Vertex{ glm::vec2{-1., 1.} },
      Vertex{ glm::vec2{ 1., 1.} }
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

    shaderProgram = AssetManager::instance().loadShaderProgram("SquarePlayer");
    shaderProgram->activate();

    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());

    vbo.Delete();
    ebo.Delete();
}

void SquarePlayer::update(float dt) {

    glm::vec2 dpos = { (move.x - move.y) * playerSpeed.x,(move.z - move.w) * playerSpeed.y };
    pos += dpos * dt;

    degree += rotate * dt * 90.;

    glm::mat4 trans = glm::mat4(1.0f);
    trans = scale(trans, glm::vec3(0.3));
    trans = glm::translate(trans, glm::vec3(pos, 0.0f));
    trans = glm::rotate(trans, glm::radians(degree), glm::vec3(0.0, 0.0, 1.0));

    // Tell OpenGL which Shader Program we want to use
    shaderProgram->activate();
    shaderProgram->setFloat("u_time", glfwGetTime());
    shaderProgram->setMat4("u_trans", trans);
    // Bind the VAO so OpenGL knows to use it
    vao.Bind();
    // Draw primitives, number of indices, datatype of indices, index of indices
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) (0 * sizeof(GLuint)));

    glm::mat4 trans2 = glm::mat4(1.0f);
    trans2 = scale(trans2, glm::vec3(0.1));
    trans2 = glm::translate(trans2, glm::vec3(pos, 0.0f));
    trans2 = glm::rotate(trans2, glm::radians(degree), glm::vec3(0.0, 0.0, 1.0));

    shaderProgram->setMat4("u_trans", trans2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) (0 * sizeof(GLuint)));

}

void SquarePlayer::Delete() {
    vao.Delete();
}
void SquarePlayer::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    bool pressed = action == GLFW_PRESS;
    if (key == GLFW_KEY_RIGHT)move.x = pressed;
    if (key == GLFW_KEY_LEFT)move.y = pressed;
    if (key == GLFW_KEY_UP)move.z = pressed;
    if (key == GLFW_KEY_DOWN)move.w = pressed;
    if (key == GLFW_KEY_R and pressed)rotate = !rotate;

}

