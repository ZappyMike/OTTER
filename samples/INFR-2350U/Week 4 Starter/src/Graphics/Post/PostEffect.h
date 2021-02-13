#pragma once

#include "Graphics/Framebuffer.h"
#include "Shader.h"

class PostEffect
{
public:
	//Initialize this effects (will be overriden in each derived class)
	virtual void Init(unsigned width, unsigned height);

	//Applies the effect
	virtual void ApplyEffect(PostEffect* previousBuffer);
	virtual void DrawToScreen();

	//Reshapes the buffer
	virtual void Reshape(unsigned width, unsigned height);

	//Clear the buffer
	void Clear();

	//Unloads the buffers
	void Unload();

	//binds buffers
	void BindBuffer(int index);
	void UnbindBuffer();

	//Bind Textures
	void BindColorAsTexture(int index, int colorbuffer, int textureSlot);
	void BindDepthAsTexture(int index, int textureSlot);
	void UnbindTexture(int textureSlot);

	//Bind shaders
	void BindShader(int index);
	void UnbindShader();

protected:
	//holds all our buffers for the effects
	std::vector<Framebuffer*> _buffers;

	//holds shaders for the effects
	std::vector<Shader::sptr> _shaders;
};