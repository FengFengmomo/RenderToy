/*
* Class:
*	Directional
* Description:
*	This class represents directional light, it's included in Light.h
*/

#pragma once

#include "core/Core.h"
#include "gl/VertexArray.h"
#include "gl/VertexBuffer.h"
#include "gl/IndexBuffer.h"

class Directional
{
private:
	glm::vec3 m_Direction;
	glm::vec3 m_EulerAngle;
	glm::vec4 m_Color;
	glm::vec4 m_Ambient;
	glm::vec4 m_Diffuse;
	glm::vec4 m_Specular;

	bool m_IfDrawCube;
	VertexArray m_Va;
	VertexBuffer m_Vb;
	IndexBuffer m_Ib;

public:
	Directional();
	~Directional();

	void Init();

	// Set direction;
	void SetPitch(float pitch);
	float GetPitch();
	void SetYaw(float yaw);
	float GetYaw();
	void SetRoll(float roll);
	float GetRoll();
	glm::vec3 GetDirection();

	// Set Light effects
	void SetColor(glm::vec4 color);
	glm::vec4 GetColor();
	void SetAmbient(float ambient);
	glm::vec4 GetAmbient();
	void SetDiffuse(float diffuse);
	glm::vec4 GetDiffuse();
	void SetSpecular(float specular);
	glm::vec4 GetSpecular();

	// Get LightCube
	bool IfDrawCube();
	VertexArray& GetVertexArray();
	IndexBuffer& GetIndexBuffer();

	// Get Point's matrices
	glm::mat4 GetModelMat();

	// Get Point's UI
	void GetUI();
};