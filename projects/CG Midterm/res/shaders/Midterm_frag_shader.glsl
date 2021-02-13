#version 410

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUV;

uniform sampler2D s_Diffuse;

uniform vec3  u_AmbientCol;
uniform float u_AmbientStrength;

uniform vec3  u_LightPos;
uniform vec3  u_LightCol;
uniform float u_AmbientLightStrength;
uniform float u_Shininess;

uniform vec3  u_CamPos;

uniform int u_DiffuseBool;
uniform int u_AmbientBool;
uniform int u_SpecularBool;
uniform int u_NoLighting;
uniform int u_AllLighting;
uniform int u_ToonLighting;

out vec4 frag_color;

const int toonBands = 15;
const float scale = 1.0/toonBands;

void main() {
	//ambient
	vec3 ambient = ((u_AmbientLightStrength * u_LightCol) + (u_AmbientCol * u_AmbientStrength));

	// Diffuse
	vec3 N = normalize(inNormal);
	vec3 lightDir = normalize(u_LightPos - inPos);

	float dif = max(dot(N, lightDir), 0.0);
	vec3 diffuse = dif * u_LightCol;

	//float dist = length(u_LightPos - inPos);
	//diffuse = diffuse / dist;

	//Toon shading
	float outline = (dot(lightDir, N) < 0.2) ? 0.0 : 1.0;

	// Specular
	vec3 camPos = u_CamPos;
	float specularStrength = 1.0; 
	vec3 camDir = normalize(camPos - inPos);
	vec3 reflectDir = reflect(-lightDir, N);
	float spec = pow(max(dot(camDir, reflectDir), 0.0), u_Shininess); 
	vec3 specular = specularStrength * spec * u_LightCol; 

	//Texture 
	vec4 textureColor = texture(s_Diffuse, inUV);

	vec3 result = (ambient + diffuse + specular) * inColor * textureColor.rgb;

	if(u_AllLighting == 1)
	{
		result = (ambient + diffuse + specular) * inColor * textureColor.rgb;
	}

	if(u_NoLighting == 1)
	{
		result = inColor * textureColor.rgb;
	}

	if(u_AmbientBool == 1)
	{
		result = ambient * inColor * textureColor.rgb;
	}

	if(u_SpecularBool == 1)
	{
		result = specular * inColor * textureColor.rgb;
	}
	if(u_ToonLighting == 1)
	{
		diffuse = floor(diffuse * toonBands) * scale;
		diffuse *= outline;

		result = (ambient + diffuse + specular) * inColor * textureColor.rgb;
	}

	frag_color = vec4(result, 1.0);
}