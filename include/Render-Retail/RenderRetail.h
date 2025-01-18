#pragma once

#include "Application/Scene.h"
#include "Challenges/Cubes/LightCube.h"
#include "Objects/Cone.h"
#include "Objects/Sphere.h"
#include "Objects/Model.h"
#include "Render-Retail/Mall.h"
#include "Render-Retail/Objects/Door.h"
#include "Render-Retail/Objects/Elevator.h"
#include "core.h"
#include "core/Camera.h"

class RenderRetail : public Scene {
public:
    RenderRetail();
    void update(float dt) override;
    void render() override;
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) override;
    void onCursorPositionEvent(double x, double y) override;

private:
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<LightCube> m_cube;
    std::shared_ptr<Mall> m_mall;
    std::shared_ptr<Cone> m_cone;
    std::shared_ptr<Sphere> m_sphere;
    std::shared_ptr<Model> m_rock;
    std::shared_ptr<Model> m_plane;
    std::shared_ptr<Box> m_street;
    std::shared_ptr<Box> m_grass;
    std::shared_ptr<Elevator> m_elevator;
    std::shared_ptr<Door> m_door;
    
    std::vector<std::shared_ptr<Model>> m_trees;
    glm::mat4 m_VP = glm::mat4(1.);
};
