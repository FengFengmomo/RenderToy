/*
* Class:
*	Renderer
* Description:
*	This class is responsible for rendering graphics, you need to 
*   use this class to draw anything you want
*/

#pragma once

#include "core/Core.h"
#include "scene/Scene.h"
#include "gl/FrameBuffer.h"

enum PostProcess
{
    NONE = 0,
    INVERSE = 1,
    BLUR = 2,
    GRAYSCALE = 3,
    EDGE = 4
};

class Renderer
{
private:
    // Render status
    int m_RenderType;
    // Frame Buffer
    FrameBuffer m_Fb;
    VertexArray m_FbVa;
    VertexBuffer m_FbVb;
    IndexBuffer m_FbIb;
    Shader m_ScreenShader;
    // Normal attributes
    bool m_ShowNormal;
    glm::vec4 m_NormalColor;
    float m_NormalMagnitude;
    // Use this shader to draw skybox
    Shader m_SkyboxShader;
    // When light cube is on, use this shader
    Shader m_LightShader;
    // When draw mode is set to line and point, use this shader
    Shader m_FrameShader;
    // When draw mode is set to depth, use this shader
    Shader m_DepthShader;
    // Use this shader to draw normals
    Shader m_NormalShader;

    void SetPostProcess(int postProcess);

public:
    Renderer();
    ~Renderer();

    // Set up renderer
    void Init(unsigned int width, unsigned int height);

    // Draw every model in the scene on the screen
    void Draw(Scene& scene);
    void Clear() const;

    // Set OpenGL's render mode, like GL_TRIANGLE or GL_LINE
    void SetRenderType(GLenum type);
    int* GetRenderType();

    // Set Normal status
    bool& GetShowNormal();
    void SetNormalColor(glm::vec4 color);
    glm::vec4& GetNormalColor();
    void SetNormalMagnitude(float magnitude);
    float& GetNormalMagnitude();

    void Resize(unsigned int width, unsigned int height);

    // Enable and disable OpenGL function
    void Enable(GLenum funcName);
    void Disable(GLenum funcName);
    // Set OpenGL's depth test mode
    void SetDepthFunc(GLenum depthFuncType);
    // Set OpenGL's blend function
    void SetBlendFunc(GLenum sfactor, GLenum dfactor);

    // Get Renderer's UI
    void GetUI();
};