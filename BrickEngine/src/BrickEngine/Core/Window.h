#pragma once

#include "BrickEngine/Core/Base.h"
#include "BrickEngine/Events/Event.h"

struct GLFWwindow;

namespace BrickEngine {

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
	public:
		struct WindowData
		{
			uint32_t Width, Height;
			std::string Title;

			EventCallbackFn EventCallback;
		};
	public:
		Window(EventCallbackFn eventCallback, const std::string& title, uint32_t width = 1280, uint32_t height = 720);
		~Window();

		inline uint32_t GetWidth() const { return m_Data.Width; }
		inline uint32_t GetHeight() const { return m_Data.Height; }
		inline const std::string& GetTitle() const { return m_Data.Title; }

		inline void* GetNativeWindowHandle() const { return m_WindowHandle; }

		void SetTitle(const std::string& title);
		void Update();
		void SwapBuffers();
	private:
		GLFWwindow* m_WindowHandle;
		WindowData m_Data;
	};

}
