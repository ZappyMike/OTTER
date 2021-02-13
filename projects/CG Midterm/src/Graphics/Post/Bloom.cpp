#include "Bloom.h"

void Bloom::Init(unsigned width, unsigned height)
{
	//initialize buffers
	int index = int(_buffers.size());
	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->Init(width, height);
	index++;
	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->Init(width / 2.0f, height / 2.0f);
	index++;
	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->Init(width / 2.0f, height / 2.0f);
	index++;
	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->Init(width, height);

	//initializing shaders
	index = int(_shaders.size());
	_shaders.push_back(Shader::Create());
	_shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index]->LoadShaderPartFromFile("shaders/Post/bloom_passthrough_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index]->Link();
	index++;
	_shaders.push_back(Shader::Create());
	_shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index]->LoadShaderPartFromFile("shaders/Post/bloom_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index]->Link();
	index++;
	_shaders.push_back(Shader::Create());
	_shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index]->LoadShaderPartFromFile("shaders/Post/blur_Hori_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index]->Link();
	index++;
	_shaders.push_back(Shader::Create());
	_shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index]->LoadShaderPartFromFile("shaders/Post/blur_Vert_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index]->Link();
	index++;
	_shaders.push_back(Shader::Create());
	_shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index]->LoadShaderPartFromFile("shaders/Post/bloom_composite_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index]->Link();

	//get the size of one pixel here
	_pixelSize = glm::vec2(1.0 / width, 1.0 / height);
}

void Bloom::ApplyEffect(PostEffect* buffer)
{
	//pass through
	BindShader(0);
	
	buffer->BindColorAsTexture(0, 0, 0);

	_buffers[0]->RenderToFSQ();

	buffer->UnbindTexture(0);

	UnbindShader();

	//bloom brightness
	BindShader(1);

	_shaders[1]->SetUniform("BrightnessThreshold", _brightnessThreshold);

	BindColorAsTexture(0, 0, 0);

	_buffers[1]->RenderToFSQ();

	UnbindTexture(0);

	UnbindShader();

	//blur
	for (int i = 0; i < _pass; i++)
	{
		//horizontal
		BindShader(2);
		_shaders[2]->SetUniform("pixelSize", _pixelSize.x);

		BindColorAsTexture(1, 0, 0);

		_buffers[2]->RenderToFSQ();

		UnbindTexture(0);

		UnbindShader();

		//vertical
		BindShader(3);
		_shaders[3]->SetUniform("pixelSize", _pixelSize.y);

		BindColorAsTexture(2, 0, 0);

		_buffers[1]->RenderToFSQ();

		UnbindTexture(0);

		UnbindShader();
	}

	//composition
	BindShader(4);

	buffer->BindColorAsTexture(0, 0, 0);
	BindColorAsTexture(1, 0, 1);

	_buffers[0]->RenderToFSQ();

	UnbindTexture(1);
	UnbindTexture(0);

	UnbindShader();
	
}

float Bloom::GetBrightness() const
{
	return _brightnessThreshold;
}

void Bloom::SetBrightness(float brightness)
{
	_brightnessThreshold = brightness;
}
