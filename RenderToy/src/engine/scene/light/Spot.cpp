#include "Spot.h"

Spot::Spot()
	: m_Va(), m_Vb(), m_Ib()
{
	m_Position = glm::vec3(0.0f);
	m_Direction = glm::vec3(0.0f, 0.0f, 1.0f);
	m_EulerAngle = glm::vec3(0.0f);
	m_Color = glm::vec4(1.0f);
	m_Angle = 90.0f;
	m_DimAngle = 10.0f;
	m_Ambient = glm::vec4(glm::vec3(0.2f), 1.0f);
	m_Diffuse = glm::vec4(glm::vec3(0.5f), 1.0f);
	m_Specular = glm::vec4(1.0f);
	m_Intensity = 100.0f;
	m_Constant = 1.0f;
	m_Linear = 0.45f;
	m_Quadratic = 0.0075f;
	m_IfDrawCube = false;
}

Spot::~Spot()
{
}

void Spot::Init()
{
	float position[] = {
		0.0f,  0.0f,  0.0f, // 0
		0.5f,  0.5f,  2.5f, // 1
		0.5f, -0.5f,  2.5f, // 2
	   -0.5f, -0.5f,  2.5f, // 3
	   -0.5f,  0.5f,  2.5f  // 4
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

void Spot::SetPosX(float posX)
{
	m_Position.x = posX;
}

float Spot::GetPosX() const
{
	return m_Position.x;
}

void Spot::SetPosY(float posY)
{
	m_Position.y = posY;
}

float Spot::GetPosY() const
{
	return m_Position.y;
}

void Spot::SetPosZ(float posZ)
{
	m_Position.z = posZ;
}

float Spot::GetPosZ() const
{
	return m_Position.z;
}

void Spot::SetPos(float posX, float posY, float posZ)
{
	m_Position = glm::vec3(posX, posY, posZ);
}

glm::vec3 Spot::GetPos()
{
	return m_Position;
}

void Spot::SetPitch(float pitch)
{
	if (abs(pitch) > 360.0f)
	{
		pitch -= pitch;
	}
	m_EulerAngle.x = pitch;
}

float Spot::GetPitch()
{
	return m_EulerAngle.x;
}

void Spot::SetYaw(float yaw)
{
	if (abs(yaw) > 360.0f)
	{
		yaw -= yaw;
	}
	m_EulerAngle.y = yaw;
}

float Spot::GetYaw()
{
	return m_EulerAngle.y;
}

void Spot::SetRoll(float roll)
{
	if (abs(roll) > 360.0f)
	{
		roll -= roll;
	}
	m_EulerAngle.z = roll;
}

float Spot::GetRoll()
{
	return m_EulerAngle.z;
}

void Spot::SetRot(float pitch, float yaw, float roll)
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

glm::vec3 Spot::GetEulerAngle()
{
	return m_EulerAngle;
}

void Spot::SetColor(glm::vec4 color)
{
	m_Color = color;
}

glm::vec4 Spot::GetColor()
{
	return m_Color;
}

void Spot::SetAngle(float angle)
{
	if (angle > 180.0f)
	{
		angle = 180.0f;
	}
	else if (angle < 0.0f)
	{
		angle = 0.0f;
	}
	m_Angle = angle;
}

float Spot::GetAngle()
{
	return m_Angle;
}

void Spot::SetDimAngle(float angle)
{
	if (angle < 0.0f)
	{
		angle = 0.0f;
	}
	else if (angle > 45.0f)
	{
		angle = 45.0f;
	}
	m_DimAngle = angle;
}

float Spot::GetDimAngle()
{
	return m_DimAngle;
}

void Spot::SetAmbient(float ambient)
{
	if (ambient < 0.0f)
	{
		ambient = 0.0f;
	}
	m_Ambient = glm::vec4(glm::vec3(ambient), 1.0f);
}

glm::vec4 Spot::GetAmbient()
{
	return m_Ambient;
}

void Spot::SetDiffuse(float diffuse)
{
	if (diffuse < 0.0f)
	{
		diffuse = 0.0f;
	}
	m_Diffuse = glm::vec4(glm::vec3(diffuse), 1.0f);
}

glm::vec4 Spot::GetDiffuse()
{
	return m_Diffuse;
}

void Spot::SetSpecular(float specular)
{
	if (specular < 0.0f)
	{
		specular = 0.0f;
	}
	m_Specular = glm::vec4(glm::vec3(specular), 1.0f);
}

glm::vec4 Spot::GetSpecular()
{
	return m_Specular;
}

void Spot::SetIntensity(float intensity)
{
	if (intensity < 0.0f)
	{
		m_Intensity = 0.0f;
		m_Constant = 0.0f;
		m_Linear = 0.0f;
		m_Quadratic = 0.0f;
	}
	else
	{
		m_Intensity = intensity;
	}
	if (m_Intensity < 7.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.7f;
		m_Quadratic = 1.8f;
	}
	else if (m_Intensity < 13.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.35f;
		m_Quadratic = 0.44f;
	}
	else if (m_Intensity < 20.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.22f;
		m_Quadratic = 0.20f;
	}
	else if (m_Intensity < 32.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.14f;
		m_Quadratic = 0.07f;
	}
	else if (m_Intensity < 50.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.09f;
		m_Quadratic = 0.032f;
	}
	else if (m_Intensity < 65.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.07f;
		m_Quadratic = 0.017f;
	}
	else if (m_Intensity < 100.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.045f;
		m_Quadratic = 0.0075f;
	}
	else if (m_Intensity < 160.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.027f;
		m_Quadratic = 0.0028f;
	}
	else if (m_Intensity < 200.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.022f;
		m_Quadratic = 0.0019f;
	}
	else if (m_Intensity < 325.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.014f;
		m_Quadratic = 0.0007f;
	}
	else if (m_Intensity < 600.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.007f;
		m_Quadratic = 0.0002f;
	}
	else if (m_Intensity < 3250.0f)
	{
		m_Constant = 1.0f;
		m_Linear = 0.0014f;
		m_Quadratic = 0.000007f;
	}
	else
	{
		m_Constant = 1.0f;
		m_Linear = 0.000001f;
		m_Quadratic = 0.000001f;
	}
}

float Spot::GetConstant()
{
	return m_Constant;
}

float Spot::GetLinear()
{
	return m_Linear;
}

float Spot::GetQuadratic()
{
	return m_Quadratic;
}

glm::vec3 Spot::GetDirection()
{
	glm::qua<float> quaternion = glm::qua<float>(glm::radians(m_EulerAngle));
	glm::mat4 rotate = glm::mat4_cast(quaternion);
	glm::vec4 direction = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	direction = rotate * direction;
	m_Direction = glm::vec3(direction.x, direction.y, direction.z);
	return m_Direction;
}

bool Spot::IfDrawCube()
{
	return m_IfDrawCube;
}

VertexArray& Spot::GetVertexArray()
{
	return m_Va;
}

IndexBuffer& Spot::GetIndexBuffer()
{
	return m_Ib;
}

glm::mat4 Spot::GetModelMat()
{
	glm::vec3 scale = glm::vec3(1.0f);
	if (m_Angle < 90.0f)
	{
		scale = glm::vec3(m_Angle / 90.0f, m_Angle / 90.0f, 1.0f);
	}
	else
	{
		scale = glm::vec3(m_Angle / 90.0f, m_Angle / 90.0f, (180.0f - m_Angle) / 90.0f);
	}
	glm::mat4 modelScale = glm::scale(glm::mat4(1.0f), scale);
	glm::qua<float> quaternion = glm::qua<float>(glm::radians(m_EulerAngle));
	glm::mat4 modelRot = glm::mat4_cast(quaternion);
	glm::mat4 modelTrans = glm::translate(glm::mat4(1.0f), m_Position);
	glm::mat4 modelMat = modelTrans * modelRot * modelScale;
	return modelMat;
}

void Spot::GetUI()
{
	ImGui::PushItemWidth(60);
	ImGui::InputFloat("Pos X", &m_Position.x); ImGui::SameLine();
	ImGui::InputFloat("Pos Y", &m_Position.y); ImGui::SameLine();
	ImGui::InputFloat("Pos Z", &m_Position.z);
	ImGui::PushItemWidth(160);
	ImGui::SliderFloat("Pitch", &m_EulerAngle.x, -360.0f, 360.0f);
	ImGui::SliderFloat("Yaw", &m_EulerAngle.y, -360.0f, 360.0f);
	ImGui::SliderFloat("Beam Angle", &m_Angle, 0.0f, 180.0f);
	ImGui::SliderFloat("Dim Angle", &m_DimAngle, 0.0f, 45.0f);
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
	if (ImGui::InputFloat("Intensity", &m_Intensity))
	{
		SetIntensity(m_Intensity);
	}
	ImGui::ColorEdit4("Color", &m_Color[0]);
	ImGui::Checkbox("Light Cube", &m_IfDrawCube);
	if (ImGui::Button("reset"))
	{
		m_Position = glm::vec3(0.0f);
		m_Direction = glm::vec3(0.0f, 0.0f, 1.0f);
		m_EulerAngle = glm::vec3(0.0f);
		m_Color = glm::vec4(1.0f);
		m_Angle = 90.0f;
		m_DimAngle = 10.0f;
		m_Ambient = glm::vec4(glm::vec3(0.2f), 1.0f);
		m_Diffuse = glm::vec4(glm::vec3(0.5f), 1.0f);
		m_Specular = glm::vec4(1.0f);
		m_IfDrawCube = false;
		SetIntensity(100.0f);
	}
}