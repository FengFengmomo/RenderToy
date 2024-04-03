/*
* Class:
*	RenderBuffer
* Description:
*	Render Buffer, use it for both depth buffer and stencil buffer
*/

#pragma once

#include "core/Core.h"

class RenderBuffer
{
private:
	unsigned int m_RendererID;

public:
	RenderBuffer();
	~RenderBuffer();

	void Init(unsigned int width, unsigned int height);
};

