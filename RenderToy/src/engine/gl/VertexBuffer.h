#pragma once

#include "core/Core.h"

class VertexBuffer
{
private:
    unsigned int m_RendererID;
    
public:
    VertexBuffer();
    ~VertexBuffer();

    void GenVertexBuffer(const void* data, unsigned int size);
    void Bind() const;
    void Unbind() const;
};
