/*
* Class:
*	Spot
* Description:
*	This class represents spot light, it's included in Light.h
*/

#pragma once

#include "core/Core.h"
#include "gl/VertexArray.h"
#include "gl/VertexBuffer.h"
#include "gl/IndexBuffer.h"

class Spot
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_EulerAngle;
	glm::vec4 m_Color;
	// Beam angle of the spot light, when smaller than this angle, light's on its full intensity
	float m_Angle; 
	// The total angle of the light cone is m_Angle + m_DimAngle, 
	// when greater than m_Anlge but smaller than the total angle, light would dim out
	float m_DimAngle; 
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
	Spot();
	~Spot();

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

	// Set Euler Angle
	void SetPitch(float pitch);
	float GetPitch();
	void SetYaw(float yaw);
	float GetYaw();
	void SetRoll(float roll);
	float GetRoll();
	void SetRot(float pitch, float yaw, float roll);
	glm::vec3 GetEulerAngle();

	// Set Light effects
	void SetColor(glm::vec4 color);
	glm::vec4 GetColor();
	void SetAngle(float angle);
	float GetAngle();
	void SetDimAngle(float angle);
	float GetDimAngle();
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

	// Get SpotLight's members
	glm::vec3 GetDirection();

	// Get LightCube
	bool IfDrawCube();
	VertexArray& GetVertexArray();
	IndexBuffer& GetIndexBuffer();

	// Get Point's matrices
	glm::mat4 GetModelMat();

	// Get Point's UI
	void GetUI();
};