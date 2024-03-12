#include "Camera.h"

Camera::Camera()
{
	cameraType = false;
	fov = 80.0f;
	width = 0;
	height = 0;
	nearPlane = 0.0f;
	farPlane = 0.0f;
	orthoLeft = 0.0f;
	orthoRight = 0.0f;
	orthoBottom = 0.0f;
	orthoTop = 0.0f;
	orthoNear = 0.0f;
	orthoFar = 0.0f;
	posX = 0;
	posY = 0;
	posZ = 0;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
}

Camera::~Camera()
{
}

void Camera::SetCameraType(bool type)
{
	cameraType = type;
}

bool Camera::GetCameraType()
{
	return cameraType;
}

void Camera::SetFov(float setFov)
{
	fov = setFov;
}

float Camera::GetFov()
{
	return fov;
}

bool Camera::SetRes(int setWidth, int setHeight)
{
	if (setWidth<=0 || setHeight<=0)
	{
		return false;
	}
	width = setWidth;
	height = setHeight;
	return true;
}

void Camera::SetPersPlane(float setNearPlane, float setFarPlane)
{
	nearPlane = setNearPlane;
	farPlane = setFarPlane;
}

void Camera::SetPers(float setFov, int setWidth, int setHeight, float setNearPlane, float setFarPlane)
{
	fov = setFov;
	width = setWidth;
	height = setHeight;
	nearPlane = setNearPlane;
	farPlane = setFarPlane;
}

glm::mat4 Camera::GetPers()
{
	glm::mat4 projPers = glm::perspective(glm::radians(fov), (float)(width/height), nearPlane, farPlane);
	return projPers;
}

void Camera::SetOrtho(float setLeft, float setRight, float setBottom, float setTop, float setNear, float setFar)
{
	orthoLeft = setLeft;
	orthoRight = setRight;
	orthoBottom = setBottom;
	orthoTop = setTop;
	orthoNear = setNear;
	orthoFar = setFar;
}

glm::mat4 Camera::GetOrtho()
{
	glm::mat4 projOrtho = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthoNear, orthoFar);
	return projOrtho;
}

void Camera::SetPosX(int setPosX)
{
	posX = setPosX;
}

int Camera::GetPosX()
{
	return posX;
}

void Camera::SetPosY(int setPosY)
{
	posY = setPosY;
}

int Camera::GetPosY()
{
	return posY;
}

void Camera::SetPosZ(int setPosZ)
{
	posZ = setPosZ;
}

int Camera::GetPosZ()
{
	return posZ;
}

void Camera::SetPos(int setPosX, int setPosY, int setPosZ)
{
	posX = setPosX;
	posY = setPosY;
	posZ = setPosZ;
}

glm::mat4 Camera::GetPos()
{
	glm::mat4 cameraPos = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
	return cameraPos;
}

void Camera::SetRotX(float setRotX)
{
	rotX = setRotX;
}

float Camera::GetRotX()
{
	return rotX;
}

void Camera::SetRotY(float setRotY)
{
	rotY = setRotY;
}

float Camera::GetRotY()
{
	return rotY;
}

void Camera::SetRotZ(float setRotZ)
{
	rotZ = setRotZ;
}

float Camera::GetRotZ()
{
	return rotZ;
}

void Camera::SetRot(float setRotX, float setRotY, float setRotZ)
{
	rotX = setRotX;
	rotY = setRotY;
	rotZ = setRotZ;
}

glm::mat4 Camera::GetView()
{
	glm::mat4 cameraPos = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
	glm::mat4 cameraRot = glm::rotate(glm::mat4(1.0f), glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 view = cameraPos * cameraRot * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	return view;
}

glm::mat4 Camera::GetRot()
{
	glm::mat4 cameraRot = glm::rotate(glm::mat4(1.0f), glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
	return cameraRot;
}

glm::mat4 Camera::GetCamera()
{
	glm::mat4 cameraPos = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
	glm::mat4 cameraRot = glm::rotate(glm::mat4(1.0f), glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 view = cameraRot * cameraPos * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 cameraMat;
	if (cameraType)
	{
		glm::mat4 projOrtho = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthoNear, orthoFar);
		cameraMat = projOrtho * view;
		return cameraMat;
	}
	else
	{
		glm::mat4 projPers = glm::perspective(glm::radians(fov), (float)(width/height), nearPlane, farPlane);
		cameraMat = projPers * view;
		return cameraMat;
	}
}