/*
* Class:
*	FrameBuffer
* Description:
*	Just Frame Buffer, I'm tired of writing comments :(
*/

#pragma once

#include "core/Core.h"
#include "ColorBuffer.h"
#include "RenderBuffer.h"

class FrameBuffer
{
private:
	unsigned int m_RendererID;
	ColorBuffer m_Cb;
	RenderBuffer m_Rb;


public:
	FrameBuffer();
	~FrameBuffer();

	bool Init(unsigned int width, unsigned int height);

	void Bind() const;
	void Unbind() const;

	ColorBuffer& GetColorBuffer();
	RenderBuffer& GetRenderBuffer();
};