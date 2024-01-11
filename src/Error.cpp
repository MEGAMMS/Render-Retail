#include "core.h"
#include "Error.h"
int Error::exitWithMassage(std::string msg) {
    std::cout << msg << std::endl;
    glfwTerminate();
    exit(-1);
}