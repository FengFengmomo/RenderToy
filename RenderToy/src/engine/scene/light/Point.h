/*
* Class:
*	Point
* Description:
*	This class represents point light, it's included in Light.h
*/

#pragma once

#include "core/Core.h"
#include "gl/VertexArray.h"
#include "gl/VertexBuffer.h"
#include "gl/IndexBuffer.h"

class Point
{
private:
	glm::vec3 m_Position;
	glm::vec4 m_Color;
	glm::vec4 m_Ambient;
	glm::vec4 m_Diffuse;
	glm::vec4 m_Specular;
	float m_Intensity; // The intensity of the point light
	float m_Constant;
	float m_Linear;
	float m_Quadratic;

	bool m_IfDrawCube;
	VertexArray m_Va;
	VertexBuffer m_Vb;
	IndexBuffer m_Ib;

public:
	Point();
	~Point();

	void Init();

	// Set Position;
	void SetPosX(float posX);
	float GetPosX() const;
	void SetPosY(float posY);
	float GetPosY() const;
	void SetPosZ(float posZ);
	float GetPosZ() const;
	void SetPos(float posX, float posY, float posZ);
	glm::vec3 GetPos();

	// Set Light effects
	void SetColor(glm::vec4 color);
	glm::vec4 GetColor();
	void SetAmbient(float ambient);
	glm::vec4 GetAmbient();
	void SetDiffuse(float diffuse);
	glm::vec4 GetDiffuse();
	void SetSpecular(float specular);
	glm::vec4 GetSpecular();
	void SetIntensity(float intensity);
	float GetConstant();
	float GetLinear();
	float GetQuadratic();

	// Get LightCube
	bool IfDrawCube();
	VertexArray& GetVertexArray();
	IndexBuffer& GetIndexBuffer();

	// Get Point's matrices
	glm::mat4 GetModelMat();

	// Get Point's UI
	void GetUI();
};

