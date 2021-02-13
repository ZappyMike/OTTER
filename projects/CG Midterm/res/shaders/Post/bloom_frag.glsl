#version 420

layout(location = 0) in vec2 inUV;

uniform float BrightnessThreshold;

layout(binding = 0) uniform sampler2D u_FinishedFrame;

out vec4 FragColor;

void main() 
{
	vec4 color = texture(u_FinishedFrame, inUV);

	//get brightness of the screen
	float brightness = (color.r + color.g + color.b) / 3.0;

	//anything above the threshold is sent to frag color
	if(brightness > BrightnessThreshold)
	{
		FragColor = color;
	}
	else
	{
		FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
}