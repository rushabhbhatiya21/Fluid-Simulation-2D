#pragma once

struct GLFWwindow;

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool shouldClose() const;
	void render();
	void upload(const float* data);

//private:
//	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//	void processInput(GLFWwindow* window);

public:
	unsigned int fieldTexture = 0;

private:
	GLFWwindow* window;
};