/*
* Class:
*	Model
* Description:
*	You know what this class can do, just as its name says
*/

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/Core.h"
#include "Mesh.h"
#include "shader/Shader.h"

class Model
{
private:
	std::vector<Texture> m_Textures;
	std::vector<Mesh> m_Meshes;
	std::string m_Directory;
	std::string m_ShaderPath;
	std::string m_Name;
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_EulerAngle;
	Shader m_Shader;

	// After Assimp read in the file, process each assimp node
	void ProcessNode(aiNode* node, const aiScene* scene);
	// Process each mesh in each node
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	// Load material textures
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

public:
	Model();
	~Model();

	void Init();

	// Load model file
	bool LoadModel(std::string modelPath, std::string shaderPath);

	// Set model's position
	void SetPosX(float posX);
	float GetPosX() const;
	void SetPosY(float posY);
	float GetPosY() const;
	void SetPosZ(float posZ);
	float GetPosZ() const;
	void SetPos(float posX, float posY, float posZ);

	// Set model's scale
	void SetScaleX(float scaleX);
	float GetScaleX();
	void SetScaleY(float scaleY);
	float GetScaleY();
	void SetScaleZ(float scaleZ);
	float GetScaleZ();
	void SetScale(float scaleX, float scaleY, float scaleZ);

	// Set model's Euler angle
	void SetPitch(float pitch);
	float GetPitch() const;
	void SetYaw(float yaw);
	float GetYaw() const;
	void SetRoll(float roll);
	float GetRoll() const;
	void SetRot(float pitch, float yaw, float roll);

	void SetModelName(std::string modelName);

	// Get Model's matrices
	glm::mat4 GetPosMat();
	glm::mat4 GetScaleMat();
	glm::mat4 GetRotMat();
	glm::mat4 GetModelMat();
	
	// Get Model's members
	std::vector<Mesh>& GetMeshes();
	std::string GetDirectory();
	Shader& GetShader();

	//Get Model's UI
	void GetUI();
};

