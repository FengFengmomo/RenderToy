#include "ColorBuffer.h"

ColorBuffer::ColorBuffer()
{
	m_RendererID = 0;
}

ColorBuffer::~ColorBuffer()
{
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void ColorBuffer::Init(unsigned int width, unsigned height)
{
    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RendererID, 0));
    
}

void ColorBuffer::Bind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void ColorBuffer::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
