#include "Camera.h"

Camera::Camera()
{
	m_CameraType = false;
	m_Fov = 80.0f;
	m_Width = 0;
	m_Height = 0;
	m_NearPlane = 0.1f;
	m_FarPlane = 3000.0f;
	m_OrthoLeft = 0.0f;
	m_OrthoRight = 0.0f;
	m_OrthoBottom = 0.0f;
	m_OrthoTop = 0.0f;
	m_OrthoNear = 0.0f;
	m_OrthoFar = 0.0f;
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_EulerAngle = glm::vec3(0.0f, 0.0f, 0.0f);
	m_MoveSpeed = 0.5f;
	m_RotateSpeed = 1.0f;
}

Camera::~Camera()
{
}

void Camera::SetCameraType(bool type)
{
	m_CameraType = type;
}

bool Camera::GetCameraType()
{
	return m_CameraType;
}

void Camera::SetFov(float fov)
{
	m_Fov = fov;
}

bool Camera::SetRes(int width, int height)
{
	if (width<=0 || height<=0)
	{
		return false;
	}
	if (width < height)
	{
		m_Height = width;
		m_Width = height;
		return true;
	}
	GLCall(glViewport(0, 0, width, height));
	m_Width = width;
	m_Height = height;
	return true;
}

void Camera::SetPersPlane(float nearPlane, float farPlane)
{
	m_NearPlane = nearPlane;
	m_FarPlane = farPlane;
}

void Camera::SetPers(float fov, int width, int height, float nearPlane, float farPlane)
{
	m_Fov = fov;
	m_Width = width;
	m_Height = height;
	m_NearPlane = nearPlane;
	m_FarPlane = farPlane;
}

bool Camera::SetOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	if (left > right || bottom > top || farPlane > nearPlane)
	{
		return false;
	}
	m_OrthoLeft = left;
	m_OrthoRight = right;
	m_OrthoBottom = bottom;
	m_OrthoTop = top;
	m_OrthoNear = nearPlane;
	m_OrthoFar = farPlane;
	return true;
}

void Camera::SetPosX(float posX)
{
	m_Position.x = posX;
}

float Camera::GetPosX()
{
	return m_Position.x;
}

void Camera::SetPosY(float posY)
{
	m_Position.y = posY;
}

float Camera::GetPosY()
{
	return m_Position.y;
}

void Camera::SetPosZ(float posZ)
{
	m_Position.z = posZ;
}

float Camera::GetPosZ()
{
	return m_Position.z;
}

void Camera::SetPos(float posX, float posY, float posZ)
{
	m_Position = glm::vec3(posX, posY, posZ);
}

void Camera::SetPitch(float pitch)
{
	if (abs(pitch) > 360.0f)
	{
		pitch -= pitch;
	}
	m_EulerAngle.x = pitch;
}

float Camera::GetPitch()
{
	return m_EulerAngle.x;
}

void Camera::SetYaw(float yaw)
{
	if (abs(yaw) > 360.0f)
	{
		yaw -= yaw;
	}
	m_EulerAngle.y = yaw;
}

float Camera::GetYaw()
{
	return m_EulerAngle.y;
}

void Camera::SetRoll(float roll)
{
	if (abs(roll) > 360.0f)
	{
		roll -= roll;
	}
	m_EulerAngle.z = roll;
}

float Camera::GetRoll()
{
	return m_EulerAngle.z;
}

void Camera::SetRot(float pitch, float yaw, float roll)
{

	if (abs(pitch) > 360.0f)
	{
		pitch -= pitch;
	}
	if (abs(yaw) > 360.0f)
	{
		yaw -= yaw;
	}
	if (abs(roll) > 360.0f)
	{
		roll -= roll;
	}
	m_EulerAngle = glm::vec3(pitch, yaw, roll);
}

void Camera::SetMoveSpeed(float moveSpeed)
{
	m_MoveSpeed = moveSpeed;
}

float Camera::GetMoveSpeed()
{
	return m_MoveSpeed;
}

void Camera::SetRotateSpeed(float rotateSpeed)
{
	m_RotateSpeed = rotateSpeed;
}

float Camera::GetRotateSpeed()
{
	return m_RotateSpeed;
}

float Camera::GetFov()
{
	return m_Fov;
}

float Camera::GetNearPlane()
{
	return m_NearPlane;
}

float Camera::GetFarPlane()
{
	return m_FarPlane;
}

glm::vec3 Camera::GetPos()
{
	return m_Position;
}

glm::vec3 Camera::GetEulerAngle()
{
	return m_EulerAngle;
}

glm::mat4 Camera::GetRotMat()
{
	glm::mat4 cameraRot = glm::rotate(glm::mat4(1.0f), glm::radians(m_EulerAngle.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_EulerAngle.y), glm::vec3(0, 1, 0));
	glm::vec4 axis = cameraRot * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	cameraRot = core::GetRodrigue(glm::normalize(axis), m_EulerAngle.z) * cameraRot;
	return cameraRot;
}

glm::mat4 Camera::GetPosMat()
{
	glm::mat4 cameraPos = glm::translate(glm::mat4(1.0f), m_Position);
	return cameraPos;
}

glm::mat4 Camera::GetProjMat()
{
	if (m_CameraType)
	{
		glm::mat4 projOrtho = glm::ortho(m_OrthoLeft, m_OrthoRight, m_OrthoBottom, m_OrthoTop, m_OrthoNear, m_OrthoFar);
		return projOrtho;
	}
	else
	{
		glm::mat4 projPers = glm::perspective(glm::radians(m_Fov), (float)m_Width / (float)m_Height, m_NearPlane, m_FarPlane);
		return projPers;
	}
}

glm::mat4 Camera::GetViewMat()
{
	glm::mat4 cameraPos = glm::translate(glm::mat4(1.0f), m_Position);
	glm::mat4 cameraRot = glm::rotate(glm::mat4(1.0f), glm::radians(m_EulerAngle.y), glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_EulerAngle.x), glm::vec3(1, 0, 0));
	glm::vec4 axis = cameraRot * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	cameraRot = core::GetRodrigue(glm::normalize(axis), m_EulerAngle.z) * cameraRot;
	cameraRot = glm::inverse(cameraRot);
	cameraPos = glm::inverse(cameraPos);
	glm::mat4 view = cameraRot * cameraPos;
	return view;
}

void Camera::GetUI()
{
	ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text("Pos X:"); ImGui::SameLine();
		ImGui::PopStyleColor(1);
		ImGui::Text("%.3f", m_Position.x); ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text("Pos Y:"); ImGui::SameLine();
		ImGui::PopStyleColor(1);
		ImGui::Text("%.3f", m_Position.y); ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text("Pos Z:"); ImGui::SameLine();
		ImGui::PopStyleColor(1);
		ImGui::Text("%.3f", m_Position.z);
	}
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text("Pitch:"); ImGui::SameLine();
		ImGui::PopStyleColor(1);
		ImGui::Text("%.3f", m_EulerAngle.x); ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text("Yaw:"); ImGui::SameLine();
		ImGui::PopStyleColor(1);
		ImGui::Text("%.3f", m_EulerAngle.y); ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text("Roll:"); ImGui::SameLine();
		ImGui::PopStyleColor(1);
		ImGui::Text("%.3f", m_EulerAngle.z);
	}
	ImGui::PushItemWidth(60);
	ImGui::SliderFloat("Move Speed", &m_MoveSpeed, 0.0f, 10.0f);
	ImGui::SliderFloat("Rotate Speed", &m_RotateSpeed, 0.0f, 10.0f);
	if (ImGui::Button("reset"))
	{
		m_MoveSpeed = 1.0f;
		m_RotateSpeed = 1.0f;
		m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_EulerAngle = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Fov = 80.0f;
	}
	ImGui::End();
}