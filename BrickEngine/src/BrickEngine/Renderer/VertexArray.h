#pragma once

#include "BrickEngine/Core/Base.h"

#include "BrickEngine/Renderer/VertexBuffer.h"
#include "BrickEngine/Renderer/IndexBuffer.h"

namespace BrickEngine {

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers(const Ref<VertexBuffer>& vertexBuffer) const = 0;

		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
		virtual Ref<IndexBuffer> GetIndexBuffer() const = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		static Ref<VertexArray> Create();
	protected:
		VertexArray() = default;
	};

}
