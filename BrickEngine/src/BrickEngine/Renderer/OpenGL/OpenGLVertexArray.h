#pragma once

#include "BrickEngine/Renderer/VertexArray.h"

namespace BrickEngine {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers(const Ref<VertexBuffer>& vertexBuffer) const override { return m_VertexBuffers; }

		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		virtual Ref<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }

		virtual void Bind() override;
		virtual void UnBind() override;
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}
