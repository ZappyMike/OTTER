#pragma once

#include "Graphics/Post/PostEffect.h"
#include "Graphics/LUT.h"

class ColorCorrection : public PostEffect
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
	LUT3D GetCube() const;

	//setters
	void SetCube(LUT3D cube);

private:
	LUT3D _testcube;
};
