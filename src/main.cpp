#include "Application/Application.h"

int main() {
    std::unique_ptr<Application> app = std::make_unique<Application>();
    app->run();
    return 0;
}

