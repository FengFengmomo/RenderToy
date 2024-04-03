/*
* Class:
*	Texture
* Description:
*	This Texture handles anything relate to textures
*/

#pragma once

#include "core/Core.h"

class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    std::string m_TypeName;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP; // BPP stands for Bytes Per Pixel

public:
    Texture(const std::string& path, std::string typeName);
    ~Texture();

    // Tell opengl to generate a texture
    void GenTexture();
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    // Get Texture's members
    unsigned int GetID() const;
    int GetWidth() const;
    int GetHeight() const;
    std::string GetTypeName() const;
    std::string GetFilePath() const;
};