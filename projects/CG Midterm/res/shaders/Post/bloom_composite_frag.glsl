#version 420

layout(location = 0) in vec2 inUV;

out vec4 FragColor;

layout(binding = 0) uniform sampler2D scene;
layout(binding = 1) uniform sampler2D bloom;

void main() 
{
	vec4 sceneColor = texture(scene, inUV);
	vec4 bloomColor = texture(bloom, inUV);

	FragColor = 1.0 - (1.0 - sceneColor) * (1.0 - bloomColor);
}