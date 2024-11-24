#include "Challenges/Cubes.h"
#include "core/Window.h"
#include "core/Image.h"
#include "Application/Application.h"
#include "AssetManager/AssetManager.h"


struct Vertex {
    glm::vec3 position;
};


Cubes::Cubes() {
    static std::vector<Vertex> vertices = {
          Vertex{ glm::vec3{-1.,-1.,-1.} },
          Vertex{ glm::vec3{ 1.,-1.,-1.} },
          Vertex{ glm::vec3{-1., 1.,-1.} },
          Vertex{ glm::vec3{ 1., 1.,-1.} },
          Vertex{ glm::vec3{-1.,-1.,1.} },
          Vertex{ glm::vec3{ 1.,-1.,1.} },
          Vertex{ glm::vec3{-1., 1.,1.} },
          Vertex{ glm::vec3{ 1., 1.,1.} }
    };
    static std::vector<GLuint> indices = {
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

    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(std::vector<VertexAttribute>{ {3, VertexAttribute::Float, 0} }, sizeof(Vertex));

    cubesShader = AssetManager::instance().loadShaderProgram("Cubes");
    cubesShader->activate();
    cubesShader->setVec2("u_resolution", Window::instance().getWindowRes());

}
void Cubes::update(float dt) {
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

    cubesShader->activate();
    cubesShader->setFloat("u_time", glfwGetTime());
    cubesShader->setMat4("projection", projection);
    cubesShader->setMat4("view", view);
    cubesShader->setMat4("model", model);
    vertexArray->renderIndexed();
}

void Cubes::Delete() {

}

void Cubes::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {

}
