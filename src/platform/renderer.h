#pragma once

struct GLFWwindow;

class Renderer
{
public:
	Renderer();
	~Renderer();

private:
	GLFWwindow* window;
};