#pragma once

#include "BrickEngine/Core/Base.h"

namespace BrickEngine {

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void SetData(uint32_t* data, uint32_t count) = 0;
		virtual uint32_t GetCount() const = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		static Ref<IndexBuffer> Create(uint32_t* data, uint32_t count);
		static Ref<IndexBuffer> Create(uint32_t count);
	protected:
		IndexBuffer() = default;
	};

}
