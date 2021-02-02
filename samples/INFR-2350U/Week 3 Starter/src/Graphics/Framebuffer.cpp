#include "Framebuffer.h"

GLuint Framebuffer::_fullscreenQuadVBO = 0;
GLuint Framebuffer::_fullscreenQuadVAO = 0;

int Framebuffer::_maxColorAttachments = 0;
bool Framebuffer::_isInitFSQ = false;

DepthTarget::~DepthTarget()
{
	//unloads depth target
	Unload();
}

void DepthTarget::Unload()
{
	//deletes the texture at the specific handle
	glDeleteTextures(1, &_texture.GetHandle());
}

ColorTarget::~ColorTarget()
{
	//Unloads the color target
	Unload();
}

void ColorTarget::Unload()
{
	glDeleteTextures(_numAttachments, &_textures[0].GetHandle());
}

Framebuffer::Framebuffer()
{
}

Framebuffer::~Framebuffer()
{
	Unload();
}


void Framebuffer::Init(unsigned width, unsigned height)
{
	//Sets the size to width and height
	SetSize(width, height);

