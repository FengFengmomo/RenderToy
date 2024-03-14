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
#include "gl/VertexBufferLayout.h"

class Model
{
private:
	glm::mat4 model;
	VertexArray* va;
	IndexBuffer* ib;
	

public:
	Model(VertexArray* setVA, IndexBuffer* setIB);
	~Model();

	VertexArray GetVertexArray();
	IndexBuffer GetIndexBuffer();
	glm::mat4 GetModelMat();
};

