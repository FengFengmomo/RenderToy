/*
* Class:
*   VertexBuffer
* Description:
*   This class cotains all functions relate to vertex buffer
*/

#pragma once

#include "core/Core.h"

class VertexBuffer
{
private:
    unsigned int m_RendererID;
    
public:
    VertexBuffer();
    ~VertexBuffer();

    // Tell opengl to generate a vertex buffer object
    void GenVertexBuffer(const void* data, unsigned int size);
    void Bind() const;
    void Unbind() const;

    // Get VertexBuffer's members
    unsigned int GetID() const;
};
