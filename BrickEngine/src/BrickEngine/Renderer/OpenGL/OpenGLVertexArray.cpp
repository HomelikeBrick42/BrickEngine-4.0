#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace BrickEngine {

	static GLenum ShaderDataTypeToGLDataType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
		case ShaderDataType::Bool2:
		case ShaderDataType::Bool3:
		case ShaderDataType::Bool4:
			return GL_BOOL;
		case ShaderDataType::Byte:
		case ShaderDataType::Byte2:
		case ShaderDataType::Byte3:
		case ShaderDataType::Byte4:
			return GL_BYTE;
		case ShaderDataType::UByte:
		case ShaderDataType::UByte2:
		case ShaderDataType::UByte3:
		case ShaderDataType::UByte4:
			return GL_UNSIGNED_BYTE;
		case ShaderDataType::Short:
		case ShaderDataType::Short2:
		case ShaderDataType::Short3:
		case ShaderDataType::Short4:
			return GL_SHORT;
		case ShaderDataType::UShort:
		case ShaderDataType::UShort2:
		case ShaderDataType::UShort3:
		case ShaderDataType::UShort4:
			return GL_UNSIGNED_SHORT;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::UInt:
		case ShaderDataType::UInt2:
		case ShaderDataType::UInt3:
		case ShaderDataType::UInt4:
			return GL_UNSIGNED_INT;
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
			return GL_FLOAT;
		case ShaderDataType::Double:
		case ShaderDataType::Double2:
		case ShaderDataType::Double3:
		case ShaderDataType::Double4:
			return GL_DOUBLE;
		}

		BRICKENGINE_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
		: m_VertexBufferIndex(0)
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(
				m_VertexBufferIndex,
				element.GetElementCount(),
				ShaderDataTypeToGLDataType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset
			);
			m_VertexBufferIndex++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

}
