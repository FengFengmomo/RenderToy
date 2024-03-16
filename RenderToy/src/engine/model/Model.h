/*
* Class:
*	Model
* Description:
*	You know what this class can do, just as its name says
*/

#pragma once

#include "core/Core.h"
#include "gl/IndexBuffer.h"
#include "gl/VertexArray.h"
#include "gl/VertexBuffer.h"
#include "gl/VertexBufferLayout.h"

class Model
{
private:
	glm::mat4 model;
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
	float posX;
	float posY;
	float posZ;
	float pitch;
	float yaw;
	float roll;

public:
	Model();
	~Model();

	void Init();

	VertexArray& GetVertexArray();
	IndexBuffer& GetIndexBuffer();
	glm::mat4 GetModelMat();

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
};

