#pragma once

struct GLFWwindow;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void run();

private:
	GLFWwindow* window;
};