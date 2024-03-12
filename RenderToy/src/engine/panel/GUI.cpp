#include "GUI.h"

namespace gui
{
    void Init(GLFWwindow* window, const char* glVersion)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glVersion);
    }

    void NewFrame()
    {
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
    }

    void EndFrame()
    {
        ImGui::EndFrame();
    }

    void Destroy()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void SameLine()
    {
        ImGui::SameLine();
    }

    void Begin(const char* label)
    {
        ImGui::Begin(label);
    }

    bool SliderInt(const char* label, int* var, int min, int max)
    {
        if (ImGui::SliderInt(label, var, min, max))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool SliderFloat(const char* label, float* var, float min, float max)
    {
        if (ImGui::SliderFloat(label, var, min, max))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Button(const char* label)
    {
        if (ImGui::Button(label))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Checkbox(const char* label, bool* value)
    {
        if (ImGui::Checkbox(label, value))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void End()
    {
        ImGui::End();
    }

    void Draw()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}