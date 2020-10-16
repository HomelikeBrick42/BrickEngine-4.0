#include "pch.h"
#include "VertexArray.h"

#include "BrickEngine/Renderer/Renderer.h"
#include "BrickEngine/Renderer/OpenGL/OpenGLVertexArray.h"

namespace BrickEngine {

    Ref<VertexArray> VertexArray::Create()
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::Unknown:
			BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
			return nullptr;
		case BrickEngine::RendererAPI::OpenGL:
			return CreateRef<OpenGLVertexArray>();
		}

		BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
		return nullptr;
    }

}
