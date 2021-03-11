#version 410

layout (location = 0) in vec3 inPosition;

//out lightspace matrix
uniform mat4 u_LightSpaceMatrix;
uniform mat4 u_Model;

void main()
{ 
	gl_Position = u_LightSpaceMatrix * u_Model * vec4(inPosition, 1.0);
}