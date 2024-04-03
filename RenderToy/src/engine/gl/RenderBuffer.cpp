#include "RenderBuffer.h"

RenderBuffer::RenderBuffer()
{
	m_RendererID = 0;
}

RenderBuffer::~RenderBuffer()
{
	GLCall(glDeleteRenderbuffers(1, &m_RendererID));
}

void RenderBuffer::Init(unsigned int width, unsigned int height)
{
    GLCall(glGenRenderbuffers(1, &m_RendererID));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
    // use a single renderbuffer object for both a depth AND stencil buffer.
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RendererID));
}
