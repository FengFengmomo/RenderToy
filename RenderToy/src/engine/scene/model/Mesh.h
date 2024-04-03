/*
* Class:
*   Mesh
* Description:
*   When reading model by Assimp, this class stores mesh info
*/

#pragma once

#include "core/Core.h"

#include "scene/texture/Texture.h"
#include "gl/VertexArray.h"
#include "gl/IndexBuffer.h"
#include "gl/VertexBuffer.h"
#include "gl/VertexBufferLayout.h"

struct Vertex {
    glm::vec3 m_Position;
    glm::vec3 m_Normal;
    glm::vec2 m_TexCoords;
};

class Mesh
{
private:
    VertexArray m_Va;
    VertexBuffer m_Vb;
    IndexBuffer m_Ib;
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();

    // Set up mesh, like tell opengl to gen vao, ibo and vbo
    void Init();

    // Get Mesh's members
    std::vector<Vertex>& GetVertices();
    std::vector<unsigned int>& GetIndices();
    std::vector<Texture>& GetTextures();
    VertexArray& GetVertexArray();
    IndexBuffer& GetIndexBuffer();
};

