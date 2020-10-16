#include "pch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace BrickEngine {

	OpenGLVertexBuffer::OpenGLVertexBuffer(void* data, uint32_t size)
		: m_Type(GL_STATIC_DRAW)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, m_Type);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
		: m_Type(GL_DYNAMIC_DRAW)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, m_Type);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::SetData(void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, m_Type);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}
