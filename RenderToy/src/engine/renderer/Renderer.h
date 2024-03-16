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
#include "model/Model.h"

enum class RenderType
{
    POINT = GL_POINTS, TRIANGLE = GL_TRIANGLES, LINE = GL_LINE, LINE_STRIP = GL_LINE_STRIP
};

class Renderer
{
private:
    RenderType renderType;
    Camera camera;
    glm::mat4 mvp;

public:
    Renderer();
    ~Renderer();

    void Init();

    void Draw(Model& model, const Shader& shader) const;
    void Clear() const;

    void SetRenderType(RenderType setType);
    RenderType GetRenderType();
    Camera& GetCamera();

    glm::mat4 GetMVP();

    void Enable(GLenum funcName);
    void Disable(GLenum funcName);
    void SetDepthFunc(GLenum depthFuncType);
    void SetBlendFunc(GLenum sfactor, GLenum dfactor);
};

