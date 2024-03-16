#pragma once

#include "core/Core.h"

/*
* Class:
*	IndexBuffer
* Description:
*	OpenGL Index buffer
*
* Functions:
*	Bind()
*	--Bind the index buffer
*
*	Unbind()
*	--Unbind index buffer
*
*	GetCount()
*	--Get the count of this index buffer
*
*/
class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;

public:
	IndexBuffer();
	~IndexBuffer();

	void GenIndexBuffer(const unsigned int* data, unsigned int count);
	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const;
};
