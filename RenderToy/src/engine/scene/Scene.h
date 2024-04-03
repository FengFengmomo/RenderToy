/*
* Class:
*	Scene
* Description:
*	This class contains all models and lights, and a camera
*/

#pragma once

#include "core/Core.h"
#include "model/Model.h"
#include "camera/Camera.h"
#include "light/Light.h"
#include "texture/Cubemap.h"
#include "shader/Shader.h"

class Scene
{
private:
	Camera m_Camera;
	std::map<std::string, Model> m_Models;
	std::vector<std::string> m_ModelList;
	Light m_Light;
	Cubemap m_Skybox;
	

public:
	Scene();
	~Scene();

	// Set up scene, tell opengl to gen vaos and ibos, etc.
	void Init();

	// Add model, light and skybox to the scene, can't you see?
	void AddModel(std::string modelName, std::string modelPath, std::string shaderPath = "src/engine/shader/shaders/DEFAULT.shader");
	void AddLight(std::string lightName, LightType lightType);
	void AddSkybox(std::string path);

	// Get Scene's matrices
	glm::mat4 GetMVP(std::string modelName);

	// Get Scene's members
	Camera& GetCamera();
	std::vector<std::string>& GetModelList();
	std::map<std::string, Model>& GetModels();
	Model& GetModel(std::string modelName);
	Light& GetLight();
	Cubemap& GetSkybox();	

	// Get Scene's UI
	void GetUI();
};