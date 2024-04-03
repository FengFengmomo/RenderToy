#include "Renderer.h"

Renderer::Renderer()
{
    m_RenderType = 3;
    m_ShowNormal = false;
    m_NormalColor = glm::vec4(1.0f);
    m_NormalMagnitude = 0.5f;
}

Renderer::~Renderer()
{
}

void Renderer::Init(unsigned int width, unsigned int height)
{
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glPointSize(1.5f));
    GLCall(glLineWidth(0.2f));
    m_SkyboxShader.Init("src/engine/shader/shaders/SKYBOX.shader");
    m_LightShader.Init("src/engine/shader/shaders/LIGHT.shader");
    m_FrameShader.Init("src/engine/shader/shaders/FRAME.shader");
    m_DepthShader.Init("src/engine/shader/shaders/DEPTH.shader");
    m_NormalShader.Init("src/engine/shader/shaders/NORMAL.shader");
    if (m_Fb.Init(width, height))
    {
        // Draw a quad on the screen and put framebuffer on it
        float position[] = {
            // positions   // texCoords
             1.0f,  1.0f,  1.0f, 1.0f, //0
            -1.0f,  1.0f,  0.0f, 1.0f, //1
            -1.0f, -1.0f,  0.0f, 0.0f, //2

             1.0f, -1.0f,  1.0f, 0.0f  //3
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        m_FbVa.GenVertexArray();
        m_FbVb.GenVertexBuffer(position, sizeof(position));
        m_FbIb.GenIndexBuffer(indices, 6);
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_FbVa.AddBuffer(m_FbVb, layout);
        SetPostProcess(0);
    }
    else
    {
        abort();
    }
}

//public
void Renderer::Draw(Scene& scene)
{
    m_Fb.Bind();
    Clear();
    // Draw Models
    for (unsigned int i = 0; i < scene.GetModelList().size(); i++)
    {
        for (unsigned int j = 0; j < scene.GetModels()[scene.GetModelList()[i]].GetMeshes().size(); j++) 
        {
            unsigned int glDrawMode = 4;
            switch (m_RenderType)
            {
            case 0: // depth
                GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
                glDrawMode = 4;
                break;
            case 1: // point
                GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
                glDrawMode = 0;
                break;
            case 2: // frame
                GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
                glDrawMode = 4;
                break;
            case 3: // triangle
                GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
                glDrawMode = 4;
                break;
            }
            if (m_RenderType == 3)
            {
                scene.GetModels()[scene.GetModelList()[i]].GetShader().Bind();
                scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformMat4f("u_MVP", scene.GetMVP(scene.GetModelList()[i]));
                scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformMat4f("u_ModelMat", scene.GetModels()[scene.GetModelList()[i]].GetModelMat());
                scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec3f("u_ViewPos", scene.GetCamera().GetPos());
                // Bind appropriate textures
                unsigned int diffuseNr = 1;
                unsigned int specularNr = 1;
                unsigned int normalNr = 1;
                for (unsigned int k = 0; k < scene.GetModels()[scene.GetModelList()[i]].GetMeshes()[j].GetTextures().size(); k++)
                {
                    // Retrieve texture number (the N in diffuse_textureN)
                    std::string number;
                    std::string name = scene.GetModels()[scene.GetModelList()[i]].GetMeshes()[j].GetTextures()[k].GetTypeName();
                    if (name == "tex_diffuse")
                    {
                        number = std::to_string(diffuseNr++);
                    }
                    else if (name == "tex_specular")
                    {
                        number = std::to_string(specularNr++);

                    }
                    else if (name == "tex_normal")
                    {
                        number = std::to_string(normalNr++);

                    }
                    // now set the sampler to the correct texture unit
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniform1i(("u_Material."+name), k);
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniform1f("u_Material.shininess", 64.0f);
                    scene.GetModels()[scene.GetModelList()[i]].GetMeshes()[j].GetTextures()[k].Bind(k);
                }
                // Set Point's uniforms
                for (unsigned int k = 0; k < scene.GetLight().GetPointList().size(); k++)
                {
                    std::string lightName = "u_PointLight[" + std::to_string(k) + "].";
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec3f(lightName + "position", scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[k]].GetPos());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "color", scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[k]].GetColor());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "ambient", scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[k]].GetAmbient());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "diffuse", scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[k]].GetDiffuse());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "specular", scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[k]].GetSpecular());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniform1f(lightName + "constant", scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[k]].GetConstant());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniform1f(lightName + "linear", scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[k]].GetLinear());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniform1f(lightName + "quadratic", scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[k]].GetQuadratic());
                }
                // Set Spot's uniforms
                for (unsigned int  k = 0; k < scene.GetLight().GetSpotList().size(); k++)
                {
                    std::string lightName = "u_SpotLight[" + std::to_string(k) + "].";
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec3f(lightName + "position", scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetPos());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec3f(lightName + "direction", scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetDirection());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniform1f(lightName + "angle", glm::radians(scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetAngle()));
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniform1f(lightName + "dimAngle", glm::radians(scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetDimAngle()));
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "color", scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetColor());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "ambient", scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetAmbient());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "diffuse", scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetDiffuse());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "specular", scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetSpecular());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniform1f(lightName + "constant", scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetConstant());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniform1f(lightName + "linear", scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetLinear());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniform1f(lightName + "quadratic", scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[k]].GetQuadratic());
                }
                // Set Directional's uniforms
                for (unsigned int  k = 0; k < scene.GetLight().GetDirectionalList().size(); k++)
                {
                    std::string lightName = "u_DirLight[" + std::to_string(k) + "].";
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec3f(lightName + "direction", scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[k]].GetDirection());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "color", scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[k]].GetColor());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "ambient", scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[k]].GetAmbient());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "diffuse", scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[k]].GetDiffuse());
                    scene.GetModels()[scene.GetModelList()[i]].GetShader().SetUniformVec4f(lightName + "specular", scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[k]].GetSpecular());
                }
            }
            else if (m_RenderType == 2 || m_RenderType == 1)
            {
                m_FrameShader.Bind();
                m_FrameShader.SetUniformMat4f("u_MVP", scene.GetMVP(scene.GetModelList()[i]));
            }
            else
            {
                m_DepthShader.Bind();
                m_DepthShader.SetUniformMat4f("u_MVP", scene.GetMVP(scene.GetModelList()[i]));
                m_DepthShader.SetUniformMat4f("u_ModelMat", scene.GetModels()[scene.GetModelList()[i]].GetModelMat());
                m_DepthShader.SetUniform1f("u_NearPlane", scene.GetCamera().GetNearPlane());
                m_DepthShader.SetUniform1f("u_FarPlane", scene.GetCamera().GetFarPlane());
            }
            scene.GetModels()[scene.GetModelList()[i]].GetMeshes()[j].GetVertexArray().Bind();
            scene.GetModels()[scene.GetModelList()[i]].GetMeshes()[j].GetIndexBuffer().Bind();
            GLCall(glDrawElements((GLenum)glDrawMode, scene.GetModels()[scene.GetModelList()[i]].GetMeshes()[j].GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
            // Draw Normals
            if (m_ShowNormal)
            {
                m_NormalShader.Bind(); 
                m_NormalShader.SetUniformMat4f("u_ViewMat", scene.GetCamera().GetViewMat());
                m_NormalShader.SetUniformMat4f("u_ModelMat", scene.GetModels()[scene.GetModelList()[i]].GetModelMat());
                m_NormalShader.SetUniform1f("u_Magnitude", m_NormalMagnitude);
                m_NormalShader.SetUniformMat4f("u_ProjMat", scene.GetCamera().GetProjMat());
                m_NormalShader.SetUniformVec4f("u_Color", m_NormalColor);
                scene.GetModels()[scene.GetModelList()[i]].GetMeshes()[j].GetVertexArray().Bind();
                scene.GetModels()[scene.GetModelList()[i]].GetMeshes()[j].GetIndexBuffer().Bind();
                GLCall(glDrawElements(GL_TRIANGLES, scene.GetModels()[scene.GetModelList()[i]].GetMeshes()[j].GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
            }
        }
    }
    
    // Draw Skybox
    if (m_RenderType == 3)
    {
        GLCall(glDepthFunc(GL_LEQUAL));
        m_SkyboxShader.Bind();
        m_SkyboxShader.SetUniform1i("skybox", 0);
        m_SkyboxShader.SetUniformMat4f("u_ProjMat", scene.GetCamera().GetProjMat());
        // Remove translation from view matrix
        m_SkyboxShader.SetUniformMat4f("u_ViewMat", glm::mat4(glm::mat3(scene.GetCamera().GetViewMat())));
        scene.GetSkybox().GetVertexArray().Bind();
        scene.GetSkybox().GetIndexBuffer().Bind();
        scene.GetSkybox().Bind();
        GLCall(glDrawElements(GL_TRIANGLES, scene.GetSkybox().GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
        GLCall(glDepthFunc(GL_LESS)); // set depth function back to default
    }
    // Draw Light Cubes
    for (unsigned int i = 0; i < scene.GetLight().GetPointList().size(); i++)
    {
        if (scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[i]].IfDrawCube())
        {
            GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
            m_LightShader.Bind();
            m_LightShader.SetUniformMat4f("u_MVP", scene.GetCamera().GetProjMat() * scene.GetCamera().GetViewMat() * scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[i]].GetModelMat());
            m_LightShader.SetUniformVec3f("u_ViewPos", scene.GetCamera().GetPos());
            m_LightShader.SetUniformVec4f("u_Color", scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[i]].GetColor());
            scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[i]].GetVertexArray().Bind();
            scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[i]].GetIndexBuffer().Bind();
            GLCall(glDrawElements(GL_TRIANGLES, scene.GetLight().GetPoints()[scene.GetLight().GetPointList()[i]].GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
        }
    }
    for (unsigned int i = 0; i < scene.GetLight().GetSpotList().size(); i++)
    {
        if (scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[i]].IfDrawCube())
        {
            GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
            m_LightShader.Bind();
            m_LightShader.SetUniformMat4f("u_MVP", scene.GetCamera().GetProjMat()* scene.GetCamera().GetViewMat()* scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[i]].GetModelMat());
            m_LightShader.SetUniformVec3f("u_ViewPos", scene.GetCamera().GetPos());
            m_LightShader.SetUniformVec4f("u_Color", scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[i]].GetColor());
            scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[i]].GetVertexArray().Bind();
            scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[i]].GetIndexBuffer().Bind();
            GLCall(glDrawElements(GL_TRIANGLES, scene.GetLight().GetSpots()[scene.GetLight().GetSpotList()[i]].GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
        }
    }
    for (unsigned int i = 0; i < scene.GetLight().GetDirectionalList().size(); i++)
    {
        if (scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[i]].IfDrawCube())
        {
            GLCall(glDepthFunc(GL_ALWAYS));
            GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
            m_LightShader.Bind();
            m_LightShader.SetUniformMat4f("u_MVP", scene.GetCamera().GetProjMat()* scene.GetCamera().GetViewMat()* scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[i]].GetModelMat());
            m_LightShader.SetUniformVec3f("u_ViewPos", scene.GetCamera().GetPos());
            m_LightShader.SetUniformVec4f("u_Color", scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[i]].GetColor());
            scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[i]].GetVertexArray().Bind();
            scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[i]].GetIndexBuffer().Bind();
            GLCall(glDrawElements(GL_TRIANGLES, scene.GetLight().GetDirectionals()[scene.GetLight().GetDirectionalList()[i]].GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
            GLCall(glDepthFunc(GL_LESS));
        }
    }
    GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    // After draw everything into the frame buffer, call this function to draw framebuffer on screen
    m_Fb.Unbind();
    GLCall(glDisable(GL_DEPTH_TEST));
    Clear();
    m_ScreenShader.Bind();
    m_Fb.GetColorBuffer().Bind();
    m_FbVa.Bind();
    m_FbIb.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, m_FbIb.GetCount(), GL_UNSIGNED_INT, nullptr));
    GLCall(glEnable(GL_DEPTH_TEST));
}

void Renderer::Clear() const
{
    GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::SetRenderType(GLenum type)
{
    m_RenderType = (int)type;
}

int* Renderer::GetRenderType()
{
    return &m_RenderType;
}

bool& Renderer::GetShowNormal()
{
    return m_ShowNormal;
}

void Renderer::SetNormalColor(glm::vec4 color)
{
    m_NormalColor = color;
}

glm::vec4& Renderer::GetNormalColor()
{
    return m_NormalColor;
}

void Renderer::SetNormalMagnitude(float magnitude)
{
    if (magnitude < 0.0f)
    {
        magnitude = 0.0f;
    }
    m_NormalMagnitude = magnitude;
}

float& Renderer::GetNormalMagnitude()
{
    return  m_NormalMagnitude;
}

void Renderer::Resize(unsigned int width, unsigned int height)
{
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
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

void Renderer::GetUI()
{
    const char* ppEffects[] = {
        "None",
        "Inverse",
        "Blur",
        "Gray Scale",
        "Edge" };
    static int postProcess = 0;
    ImGui::PushItemWidth(100);
    if (ImGui::Combo("Post-Processing", &postProcess, ppEffects, IM_ARRAYSIZE(ppEffects)))
    {
        SetPostProcess(postProcess);
    }
    ImGui::PopItemWidth();
}

void Renderer::SetPostProcess(int postProcess)
{
    switch (postProcess)
    {
    case PostProcess::NONE:
        m_ScreenShader.Init("src/engine/shader/shaders/post_process/DEFAULT.shader");
        break;
    case PostProcess::INVERSE:
        m_ScreenShader.Init("src/engine/shader/shaders/post_process/INVERSE.shader");
        break;
    case PostProcess::BLUR:
        m_ScreenShader.Init("src/engine/shader/shaders/post_process/BLUR.shader");
        break;
    case PostProcess::GRAYSCALE:
        m_ScreenShader.Init("src/engine/shader/shaders/post_process/GRAYSCALE.shader");
        break;
    case PostProcess::EDGE:
        m_ScreenShader.Init("src/engine/shader/shaders/post_process/EDGE.shader");
        break;
    default:
        m_ScreenShader.Init("src/engine/shader/shaders/post_process/DEFAULT.shader");
        break;
    }
}