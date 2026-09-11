#version 460 core

in vec2 uv;

uniform sampler2D fieldTexture;

out vec4 FragColor;

void main()
{
	float value = texture(fieldTexture, uv).r;;
	FragColor = vec4(value, value, value, 1.0f);
	// FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}