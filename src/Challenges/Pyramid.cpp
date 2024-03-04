#include "Challenges/Pyramid.h"
#include "buffers/EBO.h"
#include "core/Window.h"
#include "Application/Application.h"

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
};

class Img {
public:
    std::vector<unsigned char> data; // Image buffer
    unsigned width, height;
    Img(std::string path) {

        unsigned error = lodepng::decode(data, width, height, path, LCT_RGBA);

        // Check if there's an error
        if (error) {
            std::cerr << "Decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
            exit(1);
        }
        vertical_flip(data, width, height);
    }
private:
    void vertical_flip(std::vector<unsigned char>& image, unsigned& width, unsigned& height) {
        size_t number_of_channels = 4;
        size_t bytes_per_pixel = sizeof(unsigned char) * number_of_channels;
        size_t bytes_per_row = static_cast<size_t>(width) * bytes_per_pixel;

        for (int row = 0; row < (height >> 1); ++row) {
            auto row0 = image.begin() + row * bytes_per_row;
            auto row1 = image.begin() + (height - row - 1) * bytes_per_row;

            std::swap_ranges(row0, row0 + bytes_per_row, row1);
        }
    }
};


Pyramid::Pyramid() {
    static std::array<Vertex, 4> vertices = {
      Vertex{ glm::vec3{-1.,-1.,0.},glm::vec2{0,0} },
      Vertex{ glm::vec3{ 1.,-1.,0.} ,glm::vec2{1.,0}},
      Vertex{ glm::vec3{-1., 1.,0.} ,glm::vec2{0,1.}},
      Vertex{ glm::vec3{ 1., 1.,0.} ,glm::vec2{1,1}}
    };
    static std::array<GLuint, 6> indices = {
        0, 1, 2,
        3, 1, 2
    };

    glActiveTexture(GL_TEXTURE2);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    Img brick("assets/brick.png");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, brick.width, brick.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, brick.data.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    vao = VAO();
    vao.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo((GLfloat*) vertices.data(), sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO ebo((GLuint*) indices.data(), sizeof(indices));

    // Links VBO to VAO
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();


    shaderProgram = std::make_shared<Shader>(
        "assets/shaders/Pyramid.vert",
        "assets/shaders/Pyramid.frag");
    shaderProgram->Activate();
    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());
    shaderProgram->setInt("tex", 2);
    vbo.Delete();
    ebo.Delete();
}

void Pyramid::update(float dt) {
    shaderProgram->Activate();
    shaderProgram->setFloat("u_time", glfwGetTime());

    glm::mat4 trans = glm::mat4(1.);
    trans = glm::scale(trans, glm::vec3(0.5));
    trans = glm::translate(trans, glm::vec3(0, 0, 0));
    trans = glm::rotate(trans, glm::radians(-55.f), glm::vec3(1.0, 0.0, 0.0));
    shaderProgram->setMat4("model", trans);

    Window& window = Window::instance();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) (window.getWindowWidth()) / (float) window.getWindowHeight(), 0.1f, 100.0f);
    shaderProgram->setMat4("projection", projection);

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
    shaderProgram->setMat4("view", view);

    vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void Pyramid::Delete() {
    vao.Delete();
}
void Pyramid::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    bool pressed = action == GLFW_PRESS;
}

