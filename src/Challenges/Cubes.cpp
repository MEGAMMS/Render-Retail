#include "Challenges/Cubes.h"
#include "buffers/EBO.h"
#include "core/Window.h"
#include "core/Image.h"
#include "Application/Application.h"


struct Vertex {
    glm::vec3 position;
};


Cubes::Cubes() {
    static std::array<Vertex, 9> vertices = {
          Vertex{ glm::vec3{-1.,-1.,-1.} },
          Vertex{ glm::vec3{ 1.,-1.,-1.} },
          Vertex{ glm::vec3{-1., 1.,-1.} },
          Vertex{ glm::vec3{ 1., 1.,-1.} },
          Vertex{ glm::vec3{-1.,-1.,1.} },
          Vertex{ glm::vec3{ 1.,-1.,1.} },
          Vertex{ glm::vec3{-1., 1.,1.} },
          Vertex{ glm::vec3{ 1., 1.,1.} }
    };
    static std::array<GLuint, 6 * 2 * 3> indices = {
        0, 1 ,2,
        1, 2 ,3,

        4, 5 ,6,
        5, 6 ,7,

        1, 5 ,3,
        5, 3 ,7,

        0, 1 ,4,
        1, 4 ,5,

        2, 3 ,6,
        3, 6 ,7,

        0, 2 ,4,
        2, 4 ,6
    };


    vao = VAO();
    vao.Bind();
    VBO vbo((GLfloat*) vertices.data(), sizeof(vertices));
    EBO ebo((GLuint*) indices.data(), sizeof(indices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*) 0);
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    shaderProgram = std::make_shared<Shader>(
        "assets/shaders/Cubes.vert",
        "assets/shaders/Cubes.frag");
    shaderProgram->Activate();
    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());
    vbo.Delete();
    ebo.Delete();

}
void Cubes::update(float dt) {

    vao.Bind();
    shaderProgram->Activate();
    shaderProgram->setFloat("u_time", glfwGetTime());

    glm::mat4 model = glm::mat4(1.);
    model = glm::scale(model, glm::vec3(0.5));
    model = glm::rotate(model, glm::radians(45.f), glm::vec3(1., 1., 1.));

    Window& window = Window::instance();
    float aspect = (float) window.getWindowWidth() / window.getWindowHeight();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.f));
    float angle = (int(glfwGetTime() * 50000) % 360000) / 1000.f;
    view = glm::rotate(view, glm::radians(angle), glm::vec3(0.6f, 0.8f, 0.4f));

    shaderProgram->setMat4("projection", projection);
    shaderProgram->setMat4("view", view);

    shaderProgram->setMat4("model", model);
    glDrawElements(GL_TRIANGLES, 6 * 2 * 3, GL_UNSIGNED_INT, 0);

}

void Cubes::Delete() {

}

void Cubes::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {

}
