/*
* Class:
*   Cubemap
* Description:
*   A cubemap, what else can it be?
*/

#pragma once

#include "core/Core.h"
#include "gl/VertexArray.h"
#include "gl/VertexBuffer.h"
#include "gl/IndexBuffer.h"

class Cubemap
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    std::vector<int> m_Widths, m_Heights, m_BPPs;
    VertexArray m_Va;
    VertexBuffer m_Vb;
    IndexBuffer m_Ib;

public:
    Cubemap();
    ~Cubemap();

    void Init();

    // Tell opengl to generate a texture
    bool GenTexture(std::string path);
    void Bind() const;
    void Unbind() const;

    // Get Texture's members
    unsigned int GetID() const;
    int GetWidth(unsigned int i) const;
    int GetHeight(unsigned int i) const;
    std::string GetFilePath() const;
    VertexArray& GetVertexArray();
    IndexBuffer& GetIndexBuffer();
};