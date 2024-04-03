/*
* Class:
*	VertexArray
* Description:
*	This class contains all functions relate to vertex array object
*/

#pragma once

#include "core/Core.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray
{
private:
    unsigned int m_RendererID;

public:
    VertexArray();
    ~VertexArray();

    // Tell opengl to generate a vertex array object
    void GenVertexArray();
    // Add a vertex buffer object to vertex array
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void Unbind() const;

    // Get VertexArray's members
    unsigned int GetID() const;
};