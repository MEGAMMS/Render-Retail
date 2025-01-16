#include "Render-Retail/Objects/Books.h"

#include <memory>

#include "Objects/Object.h"

Books::Books(unsigned int books) {
    std::array textures{"assets/test-textures/Blue.png", "assets/test-textures/Green.png", "assets/test-textures/Yellow.png"};
    for (int i = 0; i < books; i++) {
        auto m_book = std::make_shared<Box>();
        m_book->setParent(std::shared_ptr<Object>(this));
        m_book->setPosition(glm::vec3(0 + (i), 0, 0));
        m_book->setOrientation(glm::vec3(0., 0., 1));
        m_book->setSize(glm::vec3(0.3, 1, 0.5));
        m_book->setTexture(textures[std::rand()%3]);
        m_books.push_back(m_book);
    }
}

void Books::update(float dt) {}
void Books::render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos) {
    for (const auto& book : m_books) {
        book->render(mvp, lightPos, lightColor, viewPos);
    }
}
void Books::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {}
void Books::onCursorPositionEvent(double x, double y) {}