#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
	m_RendererID = 0;
}

FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteFramebuffers(1, &m_RendererID));
}

bool FrameBuffer::Init(unsigned int width, unsigned int height)
{
	GLCall(glGenFramebuffers(1, &m_RendererID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	m_Cb.Init(width, height);
	m_Rb.Init(width, height);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		spdlog::error("Failed to intialize Frame Buffer!");
		return false;
	}
	return true;
}

void FrameBuffer::Bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

void FrameBuffer::Unbind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

ColorBuffer& FrameBuffer::GetColorBuffer()
{
	return m_Cb;
}

RenderBuffer& FrameBuffer::GetRenderBuffer()
{
	return m_Rb;
}
