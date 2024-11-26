#include "Challenges/Cubes.h"
#include "core/Window.h"
#include "Application/Application.h"
#include "AssetManager/AssetManager.h"





Cubes::Cubes() {


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
          { glm::vec3{-1., -1.,-1.}, glm::vec2{0.,1.} },
          { glm::vec3{ 1., -1.,-1.}, glm::vec2{1.,1.} },

          { glm::vec3{-1.,-1.,-1.}, glm::vec2{0.,0.} },
          { glm::vec3{ 1.,-1.,-1.}, glm::vec2{1.,0.} },
          { glm::vec3{ 1., 1.,1.}, glm::vec2{0.,1.} },
          { glm::vec3{ -1., 1.,1.}, glm::vec2{1.,1.} },

          { glm::vec3{-1.,-1.,1.}, glm::vec2{0.,0.} },
          { glm::vec3{ 1.,-1.,1.}, glm::vec2{1.,0.} },
          { glm::vec3{-1., 1.,1.}, glm::vec2{0.,1.} },
          { glm::vec3{ 1., 1.,1.}, glm::vec2{1.,1.} },
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
    const float cameraSpeed = 1.f * dt; // adjust accordingly
    if (move.x)cameraPos += cameraSpeed * cameraFront;
    if (move.y)cameraPos -= cameraSpeed * cameraFront;
    if (move.z)cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (move.w)cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    glm::mat4 model = glm::mat4(1.);
    model = glm::scale(model, glm::vec3(0.5));
    // model = glm::rotate(model, glm::radians(45.f), glm::vec3(1., 1., 1.));
    float angle = (int(glfwGetTime() * 50000) % 360000) / 1000.f;
    angle = 0;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.6f, 0.8f, 0.4f));

    Window& window = Window::instance();
    float aspect = (float) window.getWindowWidth() / window.getWindowHeight();
    glm::mat4 projection = glm::perspective(glm::radians(80.f), aspect, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

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
    std::cerr << action << std::endl;
    bool pressed = action == GLFW_PRESS;
    if (key == GLFW_KEY_W)move.x = pressed;
    if (key == GLFW_KEY_S)move.y = pressed;
    if (key == GLFW_KEY_A)move.z = pressed;
    if (key == GLFW_KEY_D)move.w = pressed;
}
void Cubes::onCursorPosition(double x, double y) {
    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }
  
    float xoffset = x - lastX;
    float yoffset = lastY - y; 
    lastX = x;
    lastY = y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}