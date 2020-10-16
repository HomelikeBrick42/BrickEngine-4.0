#include "pch.h"
#include "Shader.h"

#include "BrickEngine/Renderer/Renderer.h"
#include "BrickEngine/Renderer/OpenGL/OpenGLShader.h"

namespace BrickEngine {

    Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::Unknown:
			BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
			return nullptr;
		case BrickEngine::RendererAPI::OpenGL:
			return CreateRef<OpenGLShader>(vertexSource, fragmentSource);
		}

		BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
		return nullptr;
    }

}
