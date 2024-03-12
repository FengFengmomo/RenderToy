#include "Model.h"

Model::Model(VertexArray* setVA, IndexBuffer* setIB)
{
	model = glm::mat4(1.0f);
	ib = setIB;
	va = setVA;
}

Model::~Model()
{
}

VertexArray Model::GetVertexArray()
{
	return *va;
}

IndexBuffer Model::GetIndexBuffer()
{
	return *ib;
}

glm::mat4 Model::GetModelMat()
{
	return model;
}
