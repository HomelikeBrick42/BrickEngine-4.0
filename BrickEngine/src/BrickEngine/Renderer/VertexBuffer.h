#pragma once

#include "BrickEngine/Core/Base.h"
#include "BrickEngine/Renderer/BufferLayout.h"

namespace BrickEngine {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		static Ref<VertexBuffer> Create(void* data, uint32_t size);
		static Ref<VertexBuffer> Create(uint32_t size);
	protected:
		VertexBuffer() = default;
	};

}
