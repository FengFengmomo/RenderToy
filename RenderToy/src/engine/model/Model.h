#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

