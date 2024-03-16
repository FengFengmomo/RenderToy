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
	bool cameraType;
	float fov;
	int width;
	int height;
	float nearPlane;
	float farPlane;
	float orthoLeft;
	float orthoRight;
	float orthoBottom;
	float orthoTop;
	float orthoNear;
	float orthoFar;
	float posX;
	float posY;
	float posZ;
	float pitch;
	float yaw;
	float roll;
	
public:
	Camera();
	~Camera();

	// True: ORTHO False: PERS
	void SetCameraType(bool type);
	bool GetCameraType();

	void SetFov(float setFov);
	float GetFov();
	bool SetRes(int setWidth, int setHeight);
	void SetPersPlane(float setNearPlane, float setFarPlane);
	void SetPers(float setFov, int setWidth, int setHeight, float setNearPlane, float setFarPlane);
	glm::mat4 GetPersMat();

	void SetOrtho(float setLeft, float setRight, float setBottom, float setTop, float setNear, float setFar);
	glm::mat4 GetOrthoMat();
	
	void SetPosX(float setPosX);
	float GetPosX();
	
	void SetPosY(float setPosY);
	float GetPosY();
	
	void SetPosZ(float setPosZ);
	float GetPosZ();

	void SetPos(float setPosX, float setPosY, float setPosZ);
	glm::mat4 GetPos();

	void SetPitch(float setPitch);
	float GetPitch();

	void SetYaw(float setYaw);
	float GetYaw();

	void SetRoll(float setRoll);
	float GetRoll();

	void SetRot(float setPitch, float setYaw, float setRoll);
	glm::mat4 GetRotMat();

	glm::mat4 GetViewMat();

	glm::mat4 GetCameraMat();
};

