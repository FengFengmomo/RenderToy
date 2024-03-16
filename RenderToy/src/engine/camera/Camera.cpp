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
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
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

glm::mat4 Camera::GetPersMat()
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

glm::mat4 Camera::GetOrthoMat()
{
	glm::mat4 projOrtho = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthoNear, orthoFar);
	return projOrtho;
}

void Camera::SetPosX(float setPosX)
{
	posX = setPosX;
}

float Camera::GetPosX()
{
	return posX;
}

void Camera::SetPosY(float setPosY)
{
	posY = setPosY;
}

float Camera::GetPosY()
{
	return posY;
}

void Camera::SetPosZ(float setPosZ)
{
	posZ = setPosZ;
}

float Camera::GetPosZ()
{
	return posZ;
}

void Camera::SetPos(float setPosX, float setPosY, float setPosZ)
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

void Camera::SetPitch(float setPitch)
{
	pitch = setPitch;
}

float Camera::GetPitch()
{
	return pitch;
}

void Camera::SetYaw(float setYaw)
{
	yaw = setYaw;
}

float Camera::GetYaw()
{
	return yaw;
}

void Camera::SetRoll(float setRoll)
{
	roll = setRoll;
}

float Camera::GetRoll()
{
	return roll;
}

void Camera::SetRot(float setPitch, float setYaw, float setRoll)
{
	pitch = setPitch;
	yaw = setYaw;
	roll = setRoll;
}

glm::mat4 Camera::GetViewMat()
{
	glm::mat4 cameraPos = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
	glm::mat4 cameraRot = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 view = cameraPos * cameraRot * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	return view;
}

glm::mat4 Camera::GetRotMat()
{
	glm::mat4 cameraRot = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));
	return cameraRot;
}

glm::mat4 Camera::GetCameraMat()
{
	glm::mat4 cameraPos = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
	glm::mat4 cameraRot = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));
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