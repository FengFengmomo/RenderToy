/*
* Class:
*	Renderer
* Description:
*	This class is responsible for rendering graphics, you need to use this class to draw anything you want
*/

#pragma once

#include "core/Core.h"
#include "gl/VertexArray.h"
#include "gl/IndexBuffer.h"
#include "shader/Shader.h"
#include "camera/Camera.h"

enum class RenderType
{
    POINT = GL_POINTS, TRIANGLE = GL_TRIANGLES, LINE = GL_LINE, LINE_STRIP = GL_LINE_STRIP
};

class Renderer
{
private:
    RenderType renderType;

public:
    Renderer();
    ~Renderer();

    Camera camera;

    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;

    void SetRenderType(RenderType setType);
    RenderType GetRenderType();

    void Enable(GLenum funcName);
    void Disable(GLenum funcName);
    void SetDepthFunc(GLenum depthFuncType);
    void SetBlendFunc(GLenum sfactor, GLenum dfactor);
};

