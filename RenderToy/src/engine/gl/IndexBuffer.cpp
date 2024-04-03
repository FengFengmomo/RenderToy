#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
    m_RendererID = 0;
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

//public
void IndexBuffer::GenIndexBuffer(const unsigned int* data, unsigned int count)
{
    m_Count = count;
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::GetID() const
{
    return m_RendererID;
}

unsigned int IndexBuffer::GetCount() const
{
    return m_Count;
}