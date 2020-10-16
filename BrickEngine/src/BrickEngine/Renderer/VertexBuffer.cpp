#include "pch.h"
#include "VertexBuffer.h"

#include "BrickEngine/Renderer/Renderer.h"
#include "BrickEngine/Renderer/OpenGL/OpenGLVertexBuffer.h"

namespace BrickEngine {

    Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size)
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::Unknown:
			BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
			return nullptr;
		case BrickEngine::RendererAPI::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(data, size);
		}

		BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
		return nullptr;
    }

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::Unknown:
			BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
			return nullptr;
		case BrickEngine::RendererAPI::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
		}

		BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
		return nullptr;
	}

}
