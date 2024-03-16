#include "Renderer.h"

Renderer::Renderer()
{
    renderType = RenderType::TRIANGLE;
    Camera camera();
    mvp = glm::mat4(0.0f);
}

Renderer::~Renderer()
{
    
}

void Renderer::Init()
{
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_DEPTH_TEST));
}

//public
void Renderer::Draw(Model& model, const Shader& shader) const
{
    shader.Bind();
    model.GetVertexArray().Bind();
    model.GetIndexBuffer().Bind();
    GLCall(glDrawElements((GLenum)renderType, model.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
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

Camera& Renderer::GetCamera()
{
    return camera;
}

glm::mat4 Renderer::GetMVP()
{
    return mvp;
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
