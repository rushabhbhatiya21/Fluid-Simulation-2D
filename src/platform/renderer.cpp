#include "renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

Renderer::Renderer()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(1280, 720, "Simulation", nullptr, nullptr);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// temp moved here to avoid ordering problem
	// texture
	fieldTexture = 0;
	glGenTextures(1, &fieldTexture);
	glBindTexture(GL_TEXTURE_2D, fieldTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 128, 128, 0, GL_RED, GL_FLOAT, nullptr);

	float vertices[] = {
		// position    // uv
		-1.0f, 1.0f,   0.0f, 0.0f,
		 1.0f, 1.0f,   1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	while (glGetError());

	int success;
	char infoLog[512];

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexCode;
	std::ifstream vShaderFile;
	vShaderFile.open(RESOURCES_PATH "shaders/simple.vs");
	std::stringstream vShaderStream;
	vShaderStream << vShaderFile.rdbuf();
	vShaderFile.close();
	vertexCode = vShaderStream.str();
	const char* vShaderCode = vertexCode.c_str();
	glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragCode;
	std::ifstream fShaderFile;
	fShaderFile.open(RESOURCES_PATH "shaders/simple.fs");
	std::stringstream fShaderStream;
	fShaderStream << fShaderFile.rdbuf();
	fShaderFile.close();
	fragCode = fShaderStream.str();
	const char* fShaderCode = fragCode.c_str();
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);

	GLint program = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	std::cout << "Current program: " << program << '\n';

	int profile;
	glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
	std::cout << "Profile: " << profile << '\n';

	// vbo
	unsigned int VBO = 0;
	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (void*)vertices, GL_STATIC_DRAW);

	// vao
	unsigned int VAO = 0;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ebo
	unsigned int EBO = 0;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), (void*)indices, GL_STATIC_DRAW);

	std::cout << "Error Code: " << glGetError() << std::endl;

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fieldTexture);
	int location = glGetUniformLocation(shaderProgram, "fieldTexture");
	glUseProgram(shaderProgram);
	glUniform1i(location, 0);
}

Renderer::~Renderer()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Renderer::shouldClose() const
{
	return glfwWindowShouldClose(window);
}

void Renderer::render()
{
	// input
	// -----
	processInput(window);

	// render
	// ------
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Renderer::upload(const float* data)
{
	glBindTexture(GL_TEXTURE_2D, fieldTexture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 128, 128, GL_RED, GL_FLOAT, (void*)data);
}
