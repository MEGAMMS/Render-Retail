#include "Render-Retail/Objects/Table.h"

#include <memory>

#include "Objects/Object.h"

Table::Table() {
    m_body=std::make_shared<Box>();
    m_body->setParent(std::shared_ptr<Object>(this));
    m_body->setPosition(glm::vec3(0.,.75,0.));
    m_body->setSize(glm::vec3(0.75,0.15,1.));
    //m_body->setOrientation(glm::vec3(1.,0.,0.));
    m_body->setTexture("assets/test-textures/Wood1.png");

    for (int i = 0; i <4; ++i) {
            m_legs.push_back(std::make_shared<Box>());
        }

    // Calculate table body extents
    glm::vec3 tableSize = glm::vec3(0.75, 0.15, 1.); // Table top size
    float tableBottomY = 0.75f - tableSize.y / 2.0f; // Bottom edge of the table
    float legHeight = 0.85f;                        // Height of the legs
    float legSize = 0.1f;                            // Thickness of the legs
    float halfWidth = tableSize.x / 2.0f;
    float halfDepth = tableSize.z / 2.0f;

    // Position the legs
    m_legs[0]->setPosition(glm::vec3(0,0,0));
    m_legs[1]->setPosition(glm::vec3(halfWidth - legSize / 2.0f,0, -halfDepth + legSize / 2.0f));
    m_legs[2]->setPosition(glm::vec3(-halfWidth + legSize / 2.0f,0, halfDepth - legSize / 2.0f));
    m_legs[3]->setPosition(glm::vec3(halfWidth - legSize / 2.0f,0, halfDepth - legSize / 2.0f));

    // Set leg sizes and textures
    for (auto& leg : m_legs) {
        leg->setSize(glm::vec3(legSize, legHeight, legSize));
        leg->setParent(std::shared_ptr<Object>(this));
        leg->setTexture("assets/test-textures/Wood1.png");
    }
}

void Table::update(float dt) {}
void Table::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    m_body->render(mvp, lightPos, lightColor, viewPos);
    for (const auto& leg : m_legs) {
                leg->render(mvp, lightPos, lightColor, viewPos);
            }
}
void Table::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Table::onCursorPositionEvent(double x, double y) {}