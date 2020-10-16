#include "pch.h"
#include "IndexBuffer.h"

#include "BrickEngine/Renderer/Renderer.h"
#include "BrickEngine/Renderer/OpenGL/OpenGLIndexBuffer.h"

namespace BrickEngine {

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t count)
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::Unknown:
			BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
			return nullptr;
		case BrickEngine::RendererAPI::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(data, count);
		}

		BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
		return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t count)
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::Unknown:
			BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
			return nullptr;
		case BrickEngine::RendererAPI::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(count);
		}

		BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
		return nullptr;
    }

}
