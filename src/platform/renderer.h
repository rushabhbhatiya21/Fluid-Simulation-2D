#pragma once

struct GLFWwindow;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void run();
	void upload(const float* data);

public:
	unsigned int texture = 0;

private:
	GLFWwindow* window;
};