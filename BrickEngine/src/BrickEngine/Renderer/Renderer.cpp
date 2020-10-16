#include "pch.h"
#include "Renderer.h"

#include "BrickEngine/Renderer/OpenGL/OpenGLRenderer.h"

namespace BrickEngine {

	RendererAPI Renderer::s_RendererAPI = RendererAPI::Unknown;
	Scope<Renderer> Renderer::s_Renderer = nullptr;

	void Renderer::Init(RendererAPI api)
	{
		switch (api)
		{
		case BrickEngine::RendererAPI::Unknown:
			BRICKENGINE_CORE_ASSERT(false, "Renderer doesn't not support no API!");
			break;
		case BrickEngine::RendererAPI::OpenGL:
			s_Renderer = CreateScope<OpenGLRenderer>();
			break;
		}
		s_RendererAPI = api;
	}

}
