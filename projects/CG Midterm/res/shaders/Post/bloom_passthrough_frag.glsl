#version 420

layout(location = 0) in vec2 inUV;

out vec4 FragColor;

layout (binding = 0) uniform sampler2D u_FinishedFrame;

void main() 
{
	vec4 color = texture(u_FinishedFrame, inUV);

	FragColor.rgb = color.rgb; 
	FragColor.a = color.a; 
}