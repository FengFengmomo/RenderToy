#include "Point.h"

Point::Point()
	: m_Va(), m_Vb(), m_Ib()
{
	m_Position = glm::vec3(0.0f);
	m_Color = glm::vec4(1.0f);
	m_Ambient = glm::vec4(glm::vec3(0.2f), 1.0f);
	m_Diffuse = glm::vec4(glm::vec3(0.7f), 1.0f);
	m_Specular = glm::vec4(1.0f);
	m_IfDrawCube = false;
	m_Intensity = 100.0f;
	m_Constant = 1.0f;
	m_Linear = 0.45f;
	m_Quadratic = 0.0075f;
}

Point::~Point()
{
}

void Point::Init()
{
	float position[] = {
		0.0f,  0.5f,  0.0f, // 0
		0.5f,  0.0f, -0.5f, // 1
		0.5f,  0.0f,  0.5f, // 2
	   -0.5f,  0.0f,  0.5f, // 3
	   -0.5f,  0.0f, -0.5f, // 4
		0.0f, -0.5f,  0.0f  // 5
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		5, 1, 2,
		5, 2, 3,
		5, 3, 4,
		5, 4, 1
	};
	m_Va.GenVertexArray();
	m_Vb.GenVertexBuffer(position, sizeof(position));
	m_Ib.GenIndexBuffer(indices, 24);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	m_Va.AddBuffer(m_Vb, layout);
}

void Point::SetPosX(float posX)
{
	m_Position.x = posX;
}

float Point::GetPosX() const
{
	return m_Position.x;
}

void Point::SetPosY(float posY)
{
	m_Position.y = posY;
}

float Point::GetPosY() const
{
	return m_Position.y;
}

void Point::SetPosZ(float posZ)
{
	m_Position.z = posZ;
}

float Point::GetPosZ() const
{
	return m_Position.z;
}

void Point::SetPos(float posX, float posY, float posZ)
{
	m_Position = glm::vec3(posX, posY, posZ);
}

glm::vec3 Point::GetPos()
{
	return m_Position;
}

void Point::SetColor(glm::vec4 color)
{
	m_Color = color;
}

glm::vec4 Point::GetColor()
{
	return m_Color;
}

void Point::SetAmbient(float ambient)
{
	if (ambient < 0.0f)
	{
		ambient = 0.0f;
	}
	m_Ambient = glm::vec4(glm::vec3(ambient), 1.0f);
}

glm::vec4 Point::GetAmbient()
{
	return m_Ambient;
}

void Point::SetDiffuse(float diffuse)
{
	if (diffuse < 0.0f)
	{
		diffuse = 0.0f;
	}
	m_Diffuse = glm::vec4(glm::vec3(diffuse), 1.0f);
}

glm::vec4 Point::GetDiffuse()
{
	return m_Diffuse;
}

void Point::SetSpecular(float specular)
{
	if (specular < 0.0f)
	{
		specular = 0.0f;
	}
	m_Specular = glm::vec4(glm::vec3(specular), 1.0f);
}

glm::vec4 Point::GetSpecular()
{
	return m_Specular;
}

void Point::SetIntensity(float intensity)
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

float Point::GetConstant()
{
	return m_Constant;
}

float Point::GetLinear()
{
	return m_Linear;
}

float Point::GetQuadratic()
{
	return m_Quadratic;
}

bool Point::IfDrawCube()
{
	return m_IfDrawCube;
}

VertexArray& Point::GetVertexArray()
{
	return m_Va;
}

IndexBuffer& Point::GetIndexBuffer()
{
	return m_Ib;
}

glm::mat4 Point::GetModelMat()
{
	glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), m_Position);
	return modelMat;
}

void Point::GetUI()
{
	ImGui::PushItemWidth(60);
	ImGui::InputFloat("Pos X", &m_Position.x); ImGui::SameLine();
	ImGui::InputFloat("Pos Y", &m_Position.y); ImGui::SameLine();
	ImGui::InputFloat("Pos Z", &m_Position.z);
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
	ImGui::InputFloat("Intensity", &m_Intensity);
	SetIntensity(m_Intensity);
	ImGui::ColorEdit4("Color", &m_Color[0]);
	ImGui::Checkbox("Light Cube", &m_IfDrawCube);
	if (ImGui::Button("reset"))
	{
		m_Position = glm::vec3(0.0f);
		m_Color = glm::vec4(1.0f);
		m_Ambient = glm::vec4(glm::vec3(0.2f), 1.0f);
		m_Diffuse = glm::vec4(glm::vec3(0.7f), 1.0f);
		m_Specular = glm::vec4(1.0f);
		SetIntensity(100.0f);
	}
}