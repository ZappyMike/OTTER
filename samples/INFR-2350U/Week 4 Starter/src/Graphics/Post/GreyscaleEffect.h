#pragma once

#include "Graphics/Post/PostEffect.h"

class GreyscaleEffect : public PostEffect
{
public:
	//initialize framebuffer
	//override post effect init
	void Init(unsigned width, unsigned height) override;

	//applies effect to this buffer
	void ApplyEffect(PostEffect* buffer) override;

	//applies the effect to the screen
	void DrawToScreen() override;

	//Getters
	float GetIntensity() const;

	//setters
	void SetIntensity(float intensity);

private:
	float _intensity = 1.0f;
};