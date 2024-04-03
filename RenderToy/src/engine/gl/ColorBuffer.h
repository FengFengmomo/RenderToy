/*
* Class:
*	ColorBuffer
* Description:
*	Actually it's a texture, but use it as a color buffer
*/

#pragma once

#include "core/Core.h"

class ColorBuffer
{
private:
	unsigned int m_RendererID;

public:
	ColorBuffer();
	~ColorBuffer();

	void Init(unsigned int width, unsigned height);

	void Bind() const;
	void Unbind() const;
};

