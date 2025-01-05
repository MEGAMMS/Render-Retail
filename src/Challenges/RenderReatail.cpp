#include "Challenges/RenderRetail.h"
#include "core.h"
#include "core/Window.h"
#include "AssetManager/AssetManager.h"
#include "Application/Scene.h"

RenderRetail::RenderRetail()
{
    std::vector<RenderRetail::Vertex> vertices
    {
        Vertex{glm::vec3{ 0.0f,  0.5f, 0.0f,},glm::vec3{ 0.0f,  0.5f, 0.0f,}},
        Vertex{glm::vec3{-0.5f, -0.5f, 0.0f},glm::vec3{-0.5f, -0.5f, 0.0f}},
        Vertex{glm::vec3{ 0.0f,  0.5f, 0.0f},glm::vec3{0.5f, -0.5f, 0.0f }}
    };

    std::vector<unsigned int > indices
    {
        0,1,2 
    };
    camera = std::make_shared<Camera>();

    cube = std::make_shared<LightCube>(glm::vec3(1.),glm::vec3(1.));
    vertexArray = std::make_shared<VertexArray>(vertices, indices);
    vertexArray->addVertexAttributes(RenderRetail::Vertex::vertexAttributes(), sizeof(RenderRetail::Vertex));
    shaderProgram = AssetManager::instance().loadShaderProgram("thi");
}
void RenderRetail::update(float dt)
{
    cube->update(dt);
    camera->update(dt);
}

void RenderRetail::render()
{
    shaderProgram->activate();
    shaderProgram->setMat4("u_projection", projection);
    shaderProgram->setMat4("u_view", camera->getViewMatrix());
    shaderProgram->setMat4("u_model", glm::mat4(1.));
    cube->render(projection*camera->getViewMatrix());
    vertexArray->renderIndexed();
}

void RenderRetail::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode)
{
    camera->onKeyEvent(key,scancode,action,mode);
}

void RenderRetail::onCursorPositionEvent(double x, double y)
{
    camera->onCursorPositionEvent(x,y);
}



