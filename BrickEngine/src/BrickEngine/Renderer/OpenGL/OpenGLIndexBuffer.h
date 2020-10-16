#pragma once

#include "BrickEngine/Renderer/IndexBuffer.h"

namespace BrickEngine {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* data, uint32_t count);
		OpenGLIndexBuffer(uint32_t count);
		~OpenGLIndexBuffer();

		virtual void SetData(uint32_t* data, uint32_t count) override;
		virtual uint32_t GetCount() const override { return m_Count; }

		virtual void Bind() override;
		virtual void UnBind() override;
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
		uint32_t m_Type;
	};

}
