#pragma once

#include "Graphics/Post/PostEffect.h"

class SepiaEffect : public PostEffect
{
public:
	//initializes framebuffer
	void Init(unsigned width, unsigned height) override;

	void ApplyEffect(PostEffect* buffer) override;

	float GetIntensity() const;

	void SetIntensity(float intensity);

private:
	float _intensity = 0.7f;
};