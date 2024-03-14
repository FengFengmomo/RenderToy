#include "Renderer.h"

Renderer::Renderer()
{
    renderType = RenderType::TRIANGLE;
    camera = Camera();

    GLCall(glEnable(GL_DEPTH_TEST));
}

Renderer::~Renderer()
{

}

//public
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements((GLenum)renderType, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::SetRenderType(RenderType setType)
{
    renderType = setType;
}

RenderType Renderer::GetRenderType()
{
    return renderType;
}

void Renderer::Enable(GLenum funcName)
{
    GLCall(glEnable(funcName));
}

void Renderer::Disable(GLenum funcName)
{
    GLCall(glDisable(funcName));
}

void Renderer::SetDepthFunc(GLenum depthFuncType)
{
    GLCall(glDepthFunc(depthFuncType));
}

void Renderer::SetBlendFunc(GLenum sfactor, GLenum dfactor)
{
    GLCall(glBlendFunc(sfactor, dfactor));
}
