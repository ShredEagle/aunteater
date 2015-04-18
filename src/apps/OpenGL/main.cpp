#include <iostream>
#include <string>

#include "DrawingPolygons.h"
#include "Textures.h"

using namespace tutorial;

int main(int argc, char** argv)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // OS X crashes if this line is not present...
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW test", NULL, NULL);
    glfwMakeContextCurrent(window);

    std::unique_ptr<Section> section = std::make_unique<Textures>();
    section->init();

    while (!glfwWindowShouldClose(window))
    {
        section->render(window);
    }

    glfwTerminate();
}