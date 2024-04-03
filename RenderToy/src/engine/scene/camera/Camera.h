/*
* Class:
*	Camera
* Description:
*	Just a camera, I'm sure you know what this class can do
*/

#pragma once

#include "core/Core.h"

class Camera
{
private:
	// True: ORTHO False: PERS
	bool m_CameraType;
	float m_Fov;
	int m_Width;
	int m_Height;
	float m_NearPlane;
	float m_FarPlane;
	float m_OrthoLeft;
	float m_OrthoRight;
	float m_OrthoBottom;
	float m_OrthoTop;
	float m_OrthoNear;
	float m_OrthoFar;
	glm::vec3 m_Position;
	glm::vec3 m_EulerAngle;
	float m_MoveSpeed;
	float m_RotateSpeed;
	
public:
	Camera();
	~Camera();

	// True: ORTHO False: PERS
	void SetCameraType(bool type);
	bool GetCameraType();

	// Set Camera's Perpective projection matrix
	void SetFov(float fov);
	
	bool SetRes(int width, int height);
	void SetPersPlane(float nearPlane, float farPlane);
	void SetPers(float fov, int width, int height, float nearPlane, float farPlane);

	// Set Camera's Ortho projection matrix
	bool SetOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane);
	
	// Set Camera's position
	void SetPosX(float posX);
	float GetPosX();
	void SetPosY(float posY);
	float GetPosY();
	void SetPosZ(float posZ);
	float GetPosZ();
	void SetPos(float posX, float posY, float posZ);
	
	// Set Camera's Euler Angle
	void SetPitch(float pitch);
	float GetPitch();
	void SetYaw(float yaw);
	float GetYaw();
	void SetRoll(float roll);
	float GetRoll();
	void SetRot(float pitch, float yaw, float roll);

	// Set Camera's move and rotate speed
	void SetMoveSpeed(float moveSpeed);
	float GetMoveSpeed();
	void SetRotateSpeed(float rotateSpeed);
	float GetRotateSpeed();

	// Get Camera's matrices
	float GetFov();
	float GetNearPlane();
	float GetFarPlane();
	glm::vec3 GetPos();
	glm::vec3 GetEulerAngle();
	glm::mat4 GetRotMat();
	glm::mat4 GetPosMat();
	glm::mat4 GetProjMat();
	glm::mat4 GetViewMat();

	// Get Camera's UI
	void GetUI();
};

