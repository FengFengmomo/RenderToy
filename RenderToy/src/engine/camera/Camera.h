#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
	int posX;
	int posY;
	int posZ;
	float rotX;
	float rotY;
	float rotZ;
	
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
	glm::mat4 GetPers();

	void SetOrtho(float setLeft, float setRight, float setBottom, float setTop, float setNear, float setFar);
	glm::mat4 GetOrtho();
	
	void SetPosX(int setPosX);
	int GetPosX();
	
	void SetPosY(int setPosY);
	int GetPosY();
	
	void SetPosZ(int setPosZ);
	int GetPosZ();

	void SetPos(int setPosX, int setPosY, int setPosZ);
	glm::mat4 GetPos();

	void SetRotX(float setRotX);
	float GetRotX();

	void SetRotY(float setRotX);
	float GetRotY();

	void SetRotZ(float setRotX);
	float GetRotZ();

	void SetRot(float setRotX, float setRotY, float setRotZ);
	glm::mat4 GetRot();

	glm::mat4 GetView();

	glm::mat4 GetCamera();
};

