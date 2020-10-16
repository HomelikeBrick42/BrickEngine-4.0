#pragma once

#include "BrickEngine/Renderer/VertexBuffer.h"

namespace BrickEngine {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* data, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		~OpenGLVertexBuffer();

		virtual void SetData(void* data, uint32_t size) override;
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

		virtual void Bind() override;
		virtual void UnBind() override;
	private:
		uint32_t m_RendererID;
		uint32_t m_Type;
		BufferLayout m_Layout;
	};

}
