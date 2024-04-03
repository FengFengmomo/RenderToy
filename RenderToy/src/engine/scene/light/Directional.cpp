#include "Directional.h"

Directional::Directional()
	: m_Va(), m_Vb(), m_Ib()
{
	m_Direction = glm::vec3(0.0f, 0.0f, 1.0f);
	m_EulerAngle = glm::vec3(0.0f);
	m_Color = glm::vec4(1.0f);
	m_Ambient = glm::vec4(glm::vec3(0.2f), 1.0f);
	m_Diffuse = glm::vec4(glm::vec3(0.5f), 1.0f);
	m_Specular = glm::vec4(1.0f);
	m_IfDrawCube = false;
}

Directional::~Directional()
{
}

void Directional::Init()
{
	float position[] = {
		0.0f,  0.0f,   0.0f, // 0
		0.5f,  0.5f,  -2.5f, // 1
		0.5f, -0.5f,  -2.5f, // 2
	   -0.5f, -0.5f,  -2.5f, // 3
	   -0.5f,  0.5f,  -2.5f  // 4
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 1
	};
	m_Va.GenVertexArray();
	m_Vb.GenVertexBuffer(position, sizeof(position));
	m_Ib.GenIndexBuffer(indices, 12);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	m_Va.AddBuffer(m_Vb, layout);
}

void Directional::SetPitch(float pitch)
{
	if (abs(pitch) > 360.0f)
	{
		pitch -= pitch;
	}
	m_EulerAngle.x = pitch;
}

float Directional::GetPitch()
{
	return m_EulerAngle.x;
}

void Directional::SetYaw(float yaw)
{
	if (abs(yaw) > 360.0f)
	{
		yaw -= yaw;
	}
	m_EulerAngle.y = yaw;
}

float Directional::GetYaw()
{
	return m_EulerAngle.y;
}

void Directional::SetRoll(float roll)
{
	if (abs(roll) > 360.0f)
	{
		roll -= roll;
	}
	m_EulerAngle.z = roll;
}

float Directional::GetRoll()
{
	return m_EulerAngle.z;
}

glm::vec3 Directional::GetDirection()
{
	glm::qua<float> quaternion = glm::qua<float>(glm::radians(m_EulerAngle));
	glm::mat4 rotate = glm::mat4_cast(quaternion);
	glm::vec4 direction = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	direction = rotate * direction;
	m_Direction = glm::vec3(direction.x, direction.y, direction.z);
	return m_Direction;
}

void Directional::SetColor(glm::vec4 color)
{
	m_Color = color;
}

glm::vec4 Directional::GetColor()
{
	return m_Color;
}

void Directional::SetAmbient(float ambient)
{
	if (ambient < 0.0f)
	{
		ambient = 0.0f;
	}
	m_Ambient = glm::vec4(glm::vec3(ambient), 1.0f);
}

glm::vec4 Directional::GetAmbient()
{
	return m_Ambient;
}

void Directional::SetDiffuse(float diffuse)
{
	if (diffuse < 0.0f)
	{
		diffuse = 0.0f;
	}
	m_Diffuse = glm::vec4(glm::vec3(diffuse), 1.0f);
}

glm::vec4 Directional::GetDiffuse()
{
	return m_Diffuse;
}

void Directional::SetSpecular(float specular)
{
	if (specular < 0.0f)
	{
		specular = 0.0f;
	}
	m_Specular = glm::vec4(glm::vec3(specular), 1.0f);
}

glm::vec4 Directional::GetSpecular()
{
	return m_Specular;
}

bool Directional::IfDrawCube()
{
	return m_IfDrawCube;
}

VertexArray& Directional::GetVertexArray()
{
	return m_Va;
}

IndexBuffer& Directional::GetIndexBuffer()
{
	return m_Ib;
}

glm::mat4 Directional::GetModelMat()
{
	glm::qua<float> quaternion = glm::qua<float>(glm::radians(m_EulerAngle));
	glm::mat4 modelRot = glm::mat4_cast(quaternion);
	return modelRot;
}

void Directional::GetUI()
{
	ImGui::PushItemWidth(160);
	ImGui::SliderFloat("Pitch", &m_EulerAngle.x, -360.0f, 360.0f);
	ImGui::SliderFloat("Yaw", &m_EulerAngle.y, -360.0f, 360.0f);
	ImGui::PushItemWidth(60);
	if (ImGui::InputFloat("Ambient", &m_Ambient.x))
	{
		SetAmbient(m_Ambient.x);
	} ImGui::SameLine();
	if (ImGui::InputFloat("Diffuse", &m_Diffuse.x))
	{
		SetDiffuse(m_Diffuse.x);
	} ImGui::SameLine();
	if (ImGui::InputFloat("Specular", &m_Specular.x))
	{
		SetSpecular(m_Specular.x);
	}
	ImGui::PopItemWidth();
	ImGui::ColorEdit4("Color", &m_Color[0]);
	ImGui::Checkbox("Light Cube", &m_IfDrawCube);
	if (ImGui::Button("reset"))
	{
		m_EulerAngle = glm::vec3(0.0f);
		m_Color = glm::vec4(1.0f);
		m_Ambient = glm::vec4(glm::vec3(0.2f), 1.0f);
		m_Diffuse = glm::vec4(glm::vec3(0.5f), 1.0f);
		m_Specular = glm::vec4(1.0f);
		m_IfDrawCube = false;
	}
}