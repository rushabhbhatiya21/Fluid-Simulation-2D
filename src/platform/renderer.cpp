#include "renderer.h"
#include <GLFW/glfw3.h>

Renderer::Renderer()
{
	glfwInit();
	window = glfwCreateWindow(1280, 720, "Simulation", nullptr, nullptr);
}

Renderer::~Renderer()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}