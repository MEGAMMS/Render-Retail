#include "Challenges/Cubes.h"
#include "core/Window.h"
#include "Application/Application.h"
#include "AssetManager/AssetManager.h"

Cubes::Cubes() {
    camera1 = std::make_shared<Camera>();
    camera2 = std::make_shared<Camera>();
    activeCamera = camera1;

    static std::vector<Cubes::Vertex> vertices = {
          { glm::vec3{-1.,-1.,-1.}, glm::vec2{0.,0.} },
          { glm::vec3{ 1.,-1.,-1.}, glm::vec2{1.,0.} },
          { glm::vec3{-1., 1.,-1.}, glm::vec2{0.,1.} },
          { glm::vec3{ 1., 1.,-1.}, glm::vec2{1.,1.} },

          { glm::vec3{-1.,-1.,1.}, glm::vec2{0.,0.} },
          { glm::vec3{ 1.,-1.,1.}, glm::vec2{1.,0.} },
          { glm::vec3{-1., 1.,1.}, glm::vec2{0.,1.} },
          { glm::vec3{ 1., 1.,1.}, glm::vec2{1.,1.} },

          { glm::vec3{-1.,-1.,1.}, glm::vec2{0.,0.} },
          { glm::vec3{ 1.,-1.,1.}, glm::vec2{1.,0.} },
          { glm::vec3{-1.,-1.,-1.}, glm::vec2{0.,1.} },
          { glm::vec3{ 1.,-1.,-1.}, glm::vec2{1.,1.} },

          { glm::vec3{-1., 1.,1.}, glm::vec2{0.,0.} },
          { glm::vec3{ 1., 1.,1.}, glm::vec2{1.,0.} },
          { glm::vec3{-1., 1.,-1.}, glm::vec2{0.,1.} },
          { glm::vec3{ 1., 1.,-1.}, glm::vec2{1.,1.} },

          { glm::vec3{ 1.,-1.,-1.}, glm::vec2{0.,0.} },
          { glm::vec3{ 1.,-1., 1.}, glm::vec2{1.,0.} },
          { glm::vec3{ 1., 1.,-1.}, glm::vec2{0.,1.} },
          { glm::vec3{ 1., 1., 1.}, glm::vec2{1.,1.} },

          { glm::vec3{-1.,-1.,-1.}, glm::vec2{0.,0.} },
          { glm::vec3{-1.,-1., 1.}, glm::vec2{1.,0.} },
          { glm::vec3{-1., 1.,-1.}, glm::vec2{0.,1.} },
          { glm::vec3{-1., 1., 1.}, glm::vec2{1.,1.} },
    };
    static std::vector<GLuint> indices = {
        0, 1 ,2,
        1, 2 ,3,

        4, 5 ,6,
        5, 6 ,7,

        8, 9 ,10,
        9, 10 ,11,

        12, 13 ,14,
        13, 14 ,15,

        16, 17 ,18,
        17, 18 ,19,

        20, 21 ,22,
        21, 22 ,23
    };

    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(std::vector<VertexAttribute>{
        { 3, VertexAttribute::Float, 0 },
        { 2, VertexAttribute::Float, 3 * sizeof(float) }
    }, sizeof(Vertex));
    cubesShader = AssetManager::instance().loadShaderProgram("Cubes");
    cubesShader->activate();
    cubesShader->setVec2("u_resolution", Window::instance().getWindowRes());

    brick = AssetManager::instance().loadTexture("assets/brick.png");
    cubesShader->setTexture("cubeFace", brick, 3);
}
void Cubes::update(float dt) {
    model = glm::mat4(1.);
    model = glm::scale(model, glm::vec3(0.5));
    model = glm::rotate(model, glm::radians(45.f), glm::vec3(1., 1., 1.));
    float angle = (int(glfwGetTime() * 50000) % 360000) / 1000.f;
    // angle = 0;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.6f, 0.8f, 0.4f));

    Window& window = Window::instance();
    float aspect = (float) window.getWindowWidth() / window.getWindowHeight();
    projection = glm::perspective(glm::radians(80.f), aspect, 0.001f, 100.0f);

    activeCamera->update(dt);
    view = activeCamera->getViewMatrix();
}

void Cubes::render() {
    cubesShader->activate();
    cubesShader->setFloat("u_time", glfwGetTime());
    cubesShader->setMat4("projection", projection);
    cubesShader->setMat4("view", view);
    cubesShader->setMat4("model", model);
    vertexArray->renderIndexed();
}

void Cubes::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    bool pressed = action == GLFW_PRESS;
    activeCamera->onKeyEvent(key, scancode, action, mode);
    if (key == GLFW_KEY_H and pressed) {
        activeCamera = activeCamera == camera1 ? camera2 : camera1;
        activeCamera->resetMousePosition();
    }
}
void Cubes::onCursorPositionEvent(double x, double y) {
    activeCamera->onCursorPositionEvent(x, y);
}