#include "Light.h"

Light::Light()
{
}

Light::~Light()
{
}

void Light::Init()
{
    for (unsigned int i = 0; i < m_PointList.size(); i++)
    {
        m_Points[m_PointList[i]].Init();
    }
    for (unsigned int i = 0; i < m_SpotList.size(); i++)
    {
        m_Spots[m_SpotList[i]].Init();
    }
    for (unsigned int i = 0; i < m_DirectionalList.size(); i++)
    {
        m_Directionals[m_DirectionalList[i]].Init();
    }
}

void Light::AddLight(std::string name, LightType lightType)
{
    unsigned int rename = 1;
    switch (lightType)
    {
    case POINT_LIGHT:
        while (std::find(m_PointList.begin(), m_PointList.end(), name) != m_PointList.end())
        {
            name = name + "(" + std::to_string(rename) + ")";
            rename++;
        }
        if (rename != 1)
        {
            spdlog::warn("PointLight name already exist! Rename to: {}", name);
        }
        break;

    case SPOT_LIGHT:
        while (std::find(m_SpotList.begin(), m_SpotList.end(), name) != m_SpotList.end())
        {
            name = name + "(" + std::to_string(rename) + ")";
            rename++;
        }
        if (rename != 1)
        {
            spdlog::warn("SpotLight name already exist! Rename to: {}", name);
        }
        break;

    case DIRECTIONAL_LIGHT:
        while (std::find(m_DirectionalList.begin(), m_DirectionalList.end(), name) != m_DirectionalList.end())
        {
            name = name + "(" + std::to_string(rename) + ")";
            rename++;
        }
        if (rename != 1)
        {
            spdlog::warn("DirectionalLight name already exist! Rename to: {}", name);
        }
        break;
    }
    switch (lightType)
    {
    case POINT_LIGHT:
        AddPoint(name);
        break;

    case SPOT_LIGHT:
        AddSpot(name);
        break;

    case DIRECTIONAL_LIGHT:
        AddDirectional(name);
        break;
    }
}

std::map<std::string, Point>& Light::GetPoints()
{
    return m_Points;
}

std::vector<std::string>& Light::GetPointList()
{
    return m_PointList;
}

std::map<std::string, Spot>& Light::GetSpots()
{
    return m_Spots;
}

std::vector<std::string>& Light::GetSpotList()
{
    return m_SpotList;
}

std::map<std::string, Directional>& Light::GetDirectionals()
{
    return m_Directionals;
}
    
std::vector<std::string>& Light::GetDirectionalList()
{
    return m_DirectionalList;
}

void Light::GetUI()
{
    if (ImGui::TreeNode("Point Lights"))
    {
        for (unsigned int i = 0; i < m_PointList.size(); i++)
        {
            if (ImGui::TreeNode(m_PointList[i].data()))
            {
                m_Points[m_PointList[i]].GetUI();
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Spot Lights"))
    {
        for (unsigned int i = 0; i < m_SpotList.size(); i++)
        {
            if (ImGui::TreeNode(m_SpotList[i].data()))
            {
                m_Spots[m_SpotList[i]].GetUI();
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Directional Lights"))
    {
        for (unsigned int i = 0; i < m_DirectionalList.size(); i++)
        {
            if (ImGui::TreeNode(m_DirectionalList[i].data()))
            {
                m_Directionals[m_DirectionalList[i]].GetUI();
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
}

void Light::AddPoint(std::string name)
{
    Point newPointLight;
    m_Points.insert(std::pair<std::string, Point>(name, newPointLight));
    m_PointList.push_back(name);
}

void Light::AddSpot(std::string name)
{
    Spot newSpotLight;
    m_Spots.insert(std::pair<std::string, Spot>(name, newSpotLight));
    m_SpotList.push_back(name);
}

void Light::AddDirectional(std::string name)
{
    Directional newDirectionalLight;
    m_Directionals.insert(std::pair<std::string, Directional>(name, newDirectionalLight));
    m_DirectionalList.push_back(name);
}