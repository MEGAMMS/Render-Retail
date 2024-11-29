#pragma once

#include "core.h"

class Scene {
public:
    virtual ~Scene() = default;

    // Virtual methods to be implemented by each scene
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
    virtual void onCursorPositionEvent(double x, double y) {}
};
