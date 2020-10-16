#include "pch.h"
#include "Application.h"

#include "BrickEngine/Events/ApplicationEvent.h"

#include "BrickEngine/Core/Time.h"
#include "BrickEngine/Input/Input.h"

#include "BrickEngine/Renderer/Renderer.h"

namespace BrickEngine {

	Application::Application(const std::string& name)
	{
		Log::Init();
		m_Window = CreateScope<Window>(BRICKENGINE_BIND_EVENT_FN(Application::EventCallback), name);
		Input::Init(m_Window.get());
		Renderer::Init();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->Update();
			Time::BeginFrame();
			OnUpdate();
			Time::EndFrame();
			Input::EndFrame();
			m_Window->SwapBuffers();
		}
	}

	void Application::EventCallback(Event& e)
	{
		OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent&)
			{
				m_Running = false;
				return false;
			});

		Input::OnEvent(e);
	}

}
