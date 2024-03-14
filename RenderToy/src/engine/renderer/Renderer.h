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

class Renderer
{
private:
    

public:
    Renderer();
    ~Renderer();

    Camera camera;

    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};

