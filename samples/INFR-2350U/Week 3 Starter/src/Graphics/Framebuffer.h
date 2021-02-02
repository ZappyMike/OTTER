#pragma once
#include <vector>
#include <Texture2D.h>
#include <Shader.h>

struct DepthTarget
{
	//Deconstructor for Depth Target
	//*Unloads texture
	~DepthTarget();
	//deletes the texture of the depth target
	void Unload();
	//holds the depth texture
	Texture2D _texture;
};

struct ColorTarget
{
	//Deconstructor for Color Target
	//*Unloads all the color targets
	~ColorTarget();
	//Deletes the texture of the colour targets
	void Unload();
	//holds the colour texture
	std::vector<Texture2D> _textures;
	std::vector<GLenum> _formats;
	std::vector<GLenum> _buffers;
	//stores the number of colour attachments this target has
	unsigned int _numAttachments = 0;
};

class Framebuffer
{
public:
	Framebuffer();
	~Framebuffer();

	//Unloads the framebuffer
	void Unload();

	//Initialize framebuffer with size
	virtual void Init(unsigned width, unsigned height);

	//Inialializes frambuffer
	void Init();

	//Adds depth target
	//**ONLY EVER ONE**//
	void AddDepthTarget();

	//Adds a colour target
	//**as many as you want**//
	void AddColorTarget(GLenum format);

	//Binds depthbuffer as texture
	void BindDepthAsTexture(int textureSlot) const;
	//binds depthbuffer as color
	void BindColorAsTexture(unsigned colorBuffer, int textureSlot) const;
	//undinds
	void UnbindTexture(int textureSlot) const;

	//resizes the framebuffer
	void Reshape(unsigned width, unsigned height);
	//sets the size of the framebuffer
	void SetSize(unsigned width, unsigned height);

	//sets the veiwport to fullscreen (using the size of framebuffer)
	void SetVeiwport() const;

	//binds the frame buffer
	void Bind() const;
	//unbinds
	void Unbind() const;

	//renders the framebuffer to our fullscreenquad
	void RenderToFSQ() const;

	//draws the contents of the framebuffer to the back buffer
	void DrawToBackbuffer();

	//Clears the framebuffer
	void Clear();

	bool CheckFBO();

	//Initialize fullscreenquad
	//**create VAO for full screen quad
	//** -1 to 1
	static void InitFullscreenQuad();
	//Draws our fullscreenquad
	static void DrawFullscreenQuad();


	//initial width and height is zero
	unsigned int _width = 0;
	unsigned int _height = 0;

protected:
	//openGL framebuffer handle
	GLuint _FBO;
	//depth attatchment (either one or none)
	DepthTarget _depth;
	//color attachment (1 or above)
	ColorTarget _color;
	
	//Default filter is GL_Nearest
	GLenum _filter = GL_NEAREST;
	//default filter is GL_clamp_to_edge
	GLenum _wrap = GL_CLAMP_TO_EDGE;

	//Clearflag is nothing by default
	GLbitfield _clearFlag = 0;

	//is framebuffer initialized
	bool _isInit = false;

	bool _depthActive = false;

	//fullscreen quad vbo
	static GLuint _fullscreenQuadVBO;
	//vao
	static GLuint _fullscreenQuadVAO;

	//the max amount of color attatchments
	static int _maxColorAttachments;
	//fullscreen quad initiialized?
	static bool _isInitFSQ;

};