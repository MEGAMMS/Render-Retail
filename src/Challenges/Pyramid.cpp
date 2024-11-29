#include "Challenges/Pyramid.h"
#include "core/Window.h"
#include "Render/Image.h"
#include "Application/Application.h"
#include "AssetManager/AssetManager.h"

Pyramid::Pyramid() {
    static std::vector<Pyramid::Vertex> vertices = {
      Vertex{ glm::vec3{-1.,-1.,0.} ,glm::vec2{2.5,0} },
      Vertex{ glm::vec3{ 1.,-1.,0.} ,glm::vec2{0,0}},
      Vertex{ glm::vec3{-1., 1.,0.} ,glm::vec2{0,0}},
      Vertex{ glm::vec3{ 1., 1.,0.} ,glm::vec2{2.5,0}},
      Vertex{ glm::vec3{ 0., 0.,1.6} ,glm::vec2{1.25,2.5}},

      Vertex{ glm::vec3{-1.,-1.,0.} ,glm::vec2{0,0} },
      Vertex{ glm::vec3{ 1.,-1.,0.} ,glm::vec2{2.5,0}},
      Vertex{ glm::vec3{-1., 1.,0.} ,glm::vec2{0,2.5}},
      Vertex{ glm::vec3{ 1., 1.,0.} ,glm::vec2{2.5,2.5}}
    };

    static std::vector<GLuint> indices = {
        0, 1, 4,
        0, 2, 4,
        1, 3, 4,
        2, 3, 4,

        5, 6, 7,
        8, 6, 7
    };

    std::array<glm::vec3, 19> pyramidsPositions{
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(2.0f,  5.0f, 15.0f),
        glm::vec3(-1.5f, -2.2f, 2.5f),
        glm::vec3(-3.8f, -2.0f, 12.3f),
        glm::vec3(2.4f, -0.4f, 3.5f),
        glm::vec3(-1.7f,  3.0f, 7.5f),
        glm::vec3(1.3f, -2.0f, 2.5f),
        glm::vec3(1.5f,  2.0f, 2.5f),
        glm::vec3(1.5f,  0.2f, 1.5f),
        glm::vec3(-1.3f,  1.0f, 1.5f)
    };

    glActiveTexture(GL_TEXTURE2);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    std::shared_ptr<const Image> brick = AssetManager::instance().loadImage("assets/brick.png");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, brick->width, brick->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, brick->data.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE7);
    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(Pyramid::Vertex::vertexAttributes(), sizeof(Pyramid::Vertex));

    shaderProgram = AssetManager::instance().loadShaderProgram("Pyramid");
    shaderProgram->activate();
    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());
    shaderProgram->setInt("tex", 2);

    model = glm::mat4(1.);
    model = glm::scale(model, glm::vec3(0.5));
    model = glm::translate(model, glm::vec3(0, 0, 0));
    model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians((float) (int(glfwGetTime() * 100) % 360)), glm::vec3(0.0, 0.0, 1.0));
    for (int i = 0;i < pyramidsPositions.size();i++) {
        model = glm::mat4(1.);
        model = glm::scale(model, glm::vec3(0.7));
        model = glm::translate(model, pyramidsPositions[i] * glm::vec3(2.1));
        float angle = i * 20.f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        angle = angle * 2.;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-70.f), glm::vec3(1.0f, 0.1f, 0.0f));
        pyramidsModelMatrixes.push_back(model);
    }
}

void Pyramid::update(float dt) {
    view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, -0.4f, -4.f));
    float angle = (int(glfwGetTime() * 5000) % 360000) / 1000.f;
    view = glm::rotate(view, glm::radians(angle), glm::vec3(0.6f, 0.8f * glfwGetTime(), 0.4f));
}

void Pyramid::render() {
    shaderProgram->activate();
    shaderProgram->setFloat("u_time", glfwGetTime());
    shaderProgram->setMat4("projection", projection);
    shaderProgram->setMat4("view", view);
    for (auto model : pyramidsModelMatrixes) {
        shaderProgram->setMat4("model", model);
        vertexArray->renderIndexed();
    }
}

