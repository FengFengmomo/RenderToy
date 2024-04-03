#include "Cubemap.h"

#include <stb/stb_image.h>

Cubemap::Cubemap()
	: m_RendererID(0), m_LocalBuffer(nullptr), m_Va(), m_Vb(), m_Ib()
{
    for (unsigned int i = 0; i < 6; i++)
    {
        m_Widths.push_back(0);
        m_Heights.push_back(0);
        m_BPPs.push_back(0);
    }
    m_FilePath = "";
}

Cubemap::~Cubemap()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Cubemap::Init()
{
    float position[] = {
        // positions          
        -1.0f,  1.0f, -1.0f, //0
        -1.0f, -1.0f, -1.0f, //1
         1.0f, -1.0f, -1.0f, //2
         1.0f,  1.0f, -1.0f, //3
        -1.0f, -1.0f,  1.0f, //4
        -1.0f,  1.0f,  1.0f, //5
         1.0f, -1.0f,  1.0f, //6
         1.0f,  1.0f,  1.0f  //7
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
        4, 1, 0,
        0, 5, 4,
        2, 6, 7,
        7 ,3, 2,
        4, 5, 7,
        7, 6, 4,
        0, 3, 7,
        7, 5, 0,
        1, 4, 2,
        2, 4, 6
    };
    m_Va.GenVertexArray();
    m_Vb.GenVertexBuffer(position, sizeof(position));
    m_Ib.GenIndexBuffer(indices, 36);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    m_Va.AddBuffer(m_Vb, layout);
}

bool Cubemap::GenTexture(std::string path)
{
    m_FilePath = path;

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

    std::vector<std::string> fileName;
    fileName.push_back("/right.jpg");
    fileName.push_back("/left.jpg");
    fileName.push_back("/top.jpg");
    fileName.push_back("/bottom.jpg");
    fileName.push_back("/front.jpg");
    fileName.push_back("/back.jpg");
    stbi_set_flip_vertically_on_load(0);
    for (unsigned int i = 0; i < 6; i++)
    {
        m_LocalBuffer = stbi_load((m_FilePath + fileName[i]).c_str(), &m_Widths[i], &m_Heights[i], &m_BPPs[i], 0);
        if (m_LocalBuffer)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Widths[i], m_Heights[i], 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);
            stbi_image_free(m_LocalBuffer);
        }
        else
        {
            std::string errorMsg = "Cubemap texture failed to load at path: " + m_FilePath + fileName[i];
            spdlog::error(errorMsg);
            stbi_image_free(m_LocalBuffer);
            return false;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return true;
}

void Cubemap::Bind() const
{
    glActiveTexture(GL_TEXTURE0);
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
}

void Cubemap::Unbind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

unsigned int Cubemap::GetID() const
{
	return m_RendererID;
}

int Cubemap::GetWidth(unsigned int i) const
{
	return m_Widths[i];
}

int Cubemap::GetHeight(unsigned int i) const
{
	return m_Heights[i];
}

std::string Cubemap::GetFilePath() const
{
	return m_FilePath;
}

VertexArray& Cubemap::GetVertexArray()
{
    return m_Va;
}

IndexBuffer& Cubemap::GetIndexBuffer()
{
    return m_Ib;
}
