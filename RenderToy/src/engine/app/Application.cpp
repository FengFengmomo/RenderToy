#include "Application.h"

Application::Application()
{
    m_Window = nullptr;
    m_Width = 0;
    m_Height = 0;
}

Application::~Application()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glUseProgram(0));
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Application::Init(unsigned int width, unsigned int height, const char* programName)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        return false;
    }
    // Create a windowed mode window and its OpenGL context
    m_Window = glfwCreateWindow(width, height, programName, nullptr, nullptr);
    if (!m_Window)
    {
        glfwTerminate();
        spdlog::error("Failed to create a GLFW window!");
        return false;
    }
    // Make the window's context current
    glfwMakeContextCurrent(m_Window);
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        spdlog::error("Failed to initialize GLEW library!");
        return false;
    }
    // Get current OpenGL version
    spdlog::info("Driver Verison: {}", (const char*)glGetString(GL_VERSION));
    spdlog::info("OpenGL Initialization successed");

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Init renderer and scene
    m_Width = width;
    m_Height = height;
    m_Renderer.Init(m_Width, m_Height);
    m_Scene.GetCamera().SetRes(width, height);
    return true;
}

void Application::Run()
{
    // Model
    //m_Scene.AddModel("nanosuit", "res/model/nanosuit/nanosuit.obj", "res/shader/Basic.shader");
    m_Scene.AddModel("sponza", "res/model/sponza_glTF/Sponza.gltf", "res/shader/Basic.shader");
    //m_Scene.AddModel("ToyCar", "res/model/ToyCar/glTF/ToyCar.gltf", "res/shader/Basic.shader");
    //m_Scene.AddModel("sponza_hires", "res/model/sponza/sponza.obj", "res/shader/Basic.shader");
    //m_Scene.AddModel("helmet", "res/model/DamagedHelmet/glTF/DamagedHelmet.gltf", "res/shader/Basic.shader");
    // Model

    // Cubemap
    m_Scene.AddSkybox("res/cubemap/skybox/lake");
    // Cubemap
    
    // Camera
    //m_Scene.GetCamera().SetPos(0.0f, -10.0f, -10.0f);
    // Camera

    // Lighting
    m_Scene.AddLight("point", LightType::POINT_LIGHT);
    m_Scene.AddLight("spot", LightType::SPOT_LIGHT);
    m_Scene.AddLight("directional", LightType::DIRECTIONAL_LIGHT);
    // Lighting

    m_Scene.Init();

    // Draw Loop
    while (!glfwWindowShouldClose(m_Window))
    {
        Update();
    }
}

void Application::SetResolution(unsigned int width, unsigned int height)
{
    m_Width = width;
    m_Height = height;
}

void Application::Update()
{
    CameraMove(m_Window);

    //Render scene
    m_Renderer.Draw(m_Scene);

    // Draw UI
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    {
        GetUI();
    }
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //Swap front and back buffers
    glfwSwapBuffers(m_Window);
    //Poll for and process events
    glfwPollEvents();
}

GLFWwindow* Application::GetWindow()
{
    return m_Window;
}

Renderer& Application::GetRenderer()
{
    return m_Renderer;
}

Scene& Application::GetScene()
{
    return m_Scene;
}

void Application::GetUI()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::Begin("RenderToy", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Text("Resulotion: %d * %d", m_Width, m_Height);
    if (ImGui::TreeNode("Draw Mode"))
    {
        ImGui::RadioButton("Triangle", m_Renderer.GetRenderType(), 3); ImGui::SameLine();
        ImGui::RadioButton("Frame", m_Renderer.GetRenderType(), 2); ImGui::SameLine();
        ImGui::RadioButton("Point", m_Renderer.GetRenderType(), 1); ImGui::SameLine();
        ImGui::RadioButton("Depth", m_Renderer.GetRenderType(), 0);
        ImGui::Checkbox("Show Normal", &m_Renderer.GetShowNormal());
        if (m_Renderer.GetShowNormal())
        {
            ImGui::PushItemWidth(60);
            ImGui::InputFloat("Strength", &m_Renderer.GetNormalMagnitude());
            ImGui::PopItemWidth();
            ImGui::ColorEdit4("Color", &m_Renderer.GetNormalColor()[0]);
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Graphics Settings"))
    {
        m_Renderer.GetUI();
        ImGui::TreePop();
    }
    ImGui::End();
    // Show all members' UI
    m_Scene.GetUI();
    m_Scene.GetCamera().GetUI();
}

void Application::CameraMove(GLFWwindow* window)
{
    glm::vec4 move = glm::vec4(0.0f);

    //Camera Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Forward
    {
        move = m_Scene.GetCamera().GetRotMat() * glm::vec4(0.0f, 0.0f, m_Scene.GetCamera().GetMoveSpeed(), 0.0f);
        m_Scene.GetCamera().SetPos(m_Scene.GetCamera().GetPosX() - move[0], m_Scene.GetCamera().GetPosY(), m_Scene.GetCamera().GetPosZ() - move[2]);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Left
    {
        move = m_Scene.GetCamera().GetRotMat() * glm::vec4(m_Scene.GetCamera().GetMoveSpeed(), 0.0f, 0.0f, 0.0f);
        m_Scene.GetCamera().SetPos(m_Scene.GetCamera().GetPosX() - move[0], m_Scene.GetCamera().GetPosY(), m_Scene.GetCamera().GetPosZ() - move[2]);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Backward
    {
        move = m_Scene.GetCamera().GetRotMat() * glm::vec4(0.0f, 0.0f, m_Scene.GetCamera().GetMoveSpeed(), 0.0f);
        m_Scene.GetCamera().SetPos(m_Scene.GetCamera().GetPosX() + move[0], m_Scene.GetCamera().GetPosY(), m_Scene.GetCamera().GetPosZ() + move[2]);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Right
    {
        move = m_Scene.GetCamera().GetRotMat() * glm::vec4(m_Scene.GetCamera().GetMoveSpeed(), 0.0f, 0.0f, 0.0f);
        m_Scene.GetCamera().SetPos(m_Scene.GetCamera().GetPosX() + move[0], m_Scene.GetCamera().GetPosY(), m_Scene.GetCamera().GetPosZ() + move[2]);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) // Up
    {
        m_Scene.GetCamera().SetPosY(m_Scene.GetCamera().GetPosY() + m_Scene.GetCamera().GetMoveSpeed());
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) // Down
    {
        m_Scene.GetCamera().SetPosY(m_Scene.GetCamera().GetPosY() - m_Scene.GetCamera().GetMoveSpeed());
    }
    //Camera Movement

    //Camera Rotation
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) // Tilt left
    {
        m_Scene.GetCamera().SetYaw(m_Scene.GetCamera().GetYaw() + m_Scene.GetCamera().GetRotateSpeed());
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) // Tilt right
    {
        m_Scene.GetCamera().SetYaw(m_Scene.GetCamera().GetYaw() - m_Scene.GetCamera().GetRotateSpeed());
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // Tilt up
    {
        if (m_Scene.GetCamera().GetPitch() < 89.0f)
        {
            m_Scene.GetCamera().SetPitch(m_Scene.GetCamera().GetPitch() + m_Scene.GetCamera().GetRotateSpeed());
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // Tilt down
    {
        if (m_Scene.GetCamera().GetPitch() > -89.0f)
        {
            m_Scene.GetCamera().SetPitch(m_Scene.GetCamera().GetPitch() - m_Scene.GetCamera().GetRotateSpeed());
        }
    }
    //Camera Rotation
}