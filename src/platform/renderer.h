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

public:
	unsigned int fieldTexture = 0;

private:
	GLFWwindow* window;
};