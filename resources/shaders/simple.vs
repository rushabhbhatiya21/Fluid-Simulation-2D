#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

out vec2 uv;

void main()
{
	gl_Position = vec4(aPos, 1.0f, 1.0f);
	uv = aUV;
}