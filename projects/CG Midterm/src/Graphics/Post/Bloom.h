#pragma once

#include "Graphics/Post/PostEffect.h"

class Bloom : public PostEffect
{
public:
	//initialize framebuffer
	//override post effect init
	void Init(unsigned width, unsigned height) override;

	//applies effect to this buffer
	void ApplyEffect(PostEffect* buffer) override;

	//applies the effect to the screen
	//void DrawToScreen() override;

	//Getters
	float GetBrightness() const;

	//setters
	void SetBrightness(float brightness);

private:
	float _brightnessThreshold = 1.f;
	int _pass = 10;
	glm::vec2 _pixelSize;
};
