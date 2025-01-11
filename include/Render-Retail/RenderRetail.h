#pragma once

#include "Application/Scene.h"
#include "Challenges/Cubes/LightCube.h"
#include "Render-Retail/Mall.h"
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

    glm::mat4 m_VP = glm::mat4(1.);
};
