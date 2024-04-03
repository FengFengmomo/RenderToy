#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : m_Va(), m_Vb(), m_Ib()
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Textures = textures;
}

Mesh::~Mesh()
{

}

void Mesh::Init()
{
    //Create buffers/arrays
    m_Va.GenVertexArray();
    m_Vb.GenVertexBuffer(&m_Vertices[0], m_Vertices.size()*sizeof(Vertex));
    m_Ib.GenIndexBuffer(&m_Indices[0], m_Indices.size());
    VertexBufferLayout layout;
    //vertex positions
    layout.Push<float>(3);
    //vertex normals
    layout.Push<float>(3);
    //vertex texture coords
    layout.Push<float>(2);
    //vertex tanget
    //layout.Push<float>(3);
    //vertex bitanget
    //layout.Push<float>(3);
    //ids
    //layout.Push<int>(4);
    //weights
    //layout.Push<float>(4);
    m_Va.AddBuffer(m_Vb, layout);
    //Create textures
    for (unsigned int i = 0; i < m_Textures.size(); i++)
    {
        m_Textures[i].GenTexture();
    }
}

std::vector<Vertex>& Mesh::GetVertices()
{
    return m_Vertices;
}

std::vector<unsigned int>& Mesh::GetIndices()
{
    return m_Indices;
}

std::vector<Texture>& Mesh::GetTextures()
{
    return m_Textures;
}

VertexArray& Mesh::GetVertexArray()
{
    return m_Va;
}

IndexBuffer& Mesh::GetIndexBuffer()
{
    return m_Ib;
}