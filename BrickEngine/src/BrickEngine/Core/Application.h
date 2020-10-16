#pragma once

#include "BrickEngine/Core/Base.h"

#include "BrickEngine/Events/Event.h"
#include "BrickEngine/Core/Window.h"

namespace BrickEngine {

	class Application
	{
	public:
		virtual ~Application();

		void Run();
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;
	protected:
		Application(const std::string& name = "BrickEngine Game");
	protected:
		Scope<Window> m_Window;
	private:
		bool m_Running = true;
	private:
		void EventCallback(Event& e);
	};

}
