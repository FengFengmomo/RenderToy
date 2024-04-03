#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	for (unsigned int i = 0; i < m_ModelList.size(); i++)
	{
		m_Models[m_ModelList[i]].Init();
		for (unsigned int j = 0; j < m_Models[m_ModelList[i]].GetMeshes().size(); j++) 
		{
			m_Models[m_ModelList[i]].GetMeshes()[j].Init();
		}
	}
	m_Light.Init();
	m_Skybox.Init();
}

void Scene::AddModel(std::string modelName, std::string modelPath, std::string shaderPath)
{
	spdlog::info("Loading model from {}", modelPath);
	unsigned int rename = 1;
	while (std::find(m_ModelList.begin(), m_ModelList.end(), modelName) != m_ModelList.end())
	{
		modelName = modelName + "(" + std::to_string(rename) + ")";
		rename++;
	}
	if (rename != 1)
	{
		spdlog::warn("Model name already exist! Rename to: {}", modelName);
	}
	Model newModel;
	if (newModel.LoadModel(modelPath, shaderPath))
	{
		m_Models.insert(std::pair<std::string, Model>(modelName, newModel));
		m_Models[modelName].SetModelName(modelName);
		m_ModelList.push_back(modelName);
	}
	else
	{
		abort();
	}
}

void Scene::AddLight(std::string lightName, LightType lightType)
{
	m_Light.AddLight(lightName, lightType);
}

void Scene::AddSkybox(std::string path)
{
	if (!m_Skybox.GenTexture(path))
	{
		abort();
	}
}

glm::mat4 Scene::GetMVP(std::string modelName)
{
	glm::mat4 mvp = m_Camera.GetProjMat() * m_Camera.GetViewMat() * m_Models[modelName].GetModelMat();
	return mvp;
}

Camera& Scene::GetCamera()
{
	return m_Camera;
}

std::vector<std::string>& Scene::GetModelList()
{
	return m_ModelList;
}

std::map<std::string, Model>& Scene::GetModels()
{
	return m_Models;
}

Model& Scene::GetModel(std::string modelName)
{
	return m_Models[modelName];
}

Light& Scene::GetLight()
{
	return m_Light;
}

Cubemap& Scene::GetSkybox()
{
	return m_Skybox;
}

void Scene::GetUI()
{
	ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::TreeNode("Models"))
	{
		for (unsigned int i = 0; i < GetModelList().size(); i++)
		{
			if (ImGui::TreeNode(GetModelList()[i].data()))
			{
				GetModels()[GetModelList()[i]].GetUI();
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Lighting"))
	{
		m_Light.GetUI();
		ImGui::TreePop();
	}
	ImGui::End();
}