#include "pch.h"
#include "Window.h"

#include "BrickEngine/Events/ApplicationEvent.h"
#include "BrickEngine/Events/MouseEvent.h"
#include "BrickEngine/Events/KeyEvent.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace BrickEngine {

	static uint32_t s_WindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		std::cout << "(" << error << ")" << ": " << description << std::endl;
	}

	Window::Window(EventCallbackFn eventCallback, const std::string& title, uint32_t width, uint32_t height)
		: m_Data({width, height, title, eventCallback})
	{
		if (s_WindowCount == 0)
		{
			int result = glfwInit();
			BRICKENGINE_CORE_ASSERT(result, "Failed to initalize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		m_WindowHandle = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		BRICKENGINE_CORE_ASSERT(m_WindowHandle, "Failed to create window!");
		s_WindowCount++;

		glfwSetWindowUserPointer(m_WindowHandle, &m_Data);

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BRICKENGINE_CORE_ASSERT(status, "Failed to initalize glad!");

		glfwSwapInterval(1);

		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event((KeyCode)key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event((KeyCode)key, 1);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event((KeyCode)key);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_WindowHandle, [](GLFWwindow* window, uint32_t character)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(character);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event((MouseButton)button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event((MouseButton)button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

		glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, double scrollX, double scrollY)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)scrollX, (float)scrollY);
				data.EventCallback(event);
			});

		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowPosCallback(m_WindowHandle, [](GLFWwindow* window, int xPos, int yPos)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowMoveEvent event(xPos, yPos);
				data.EventCallback(event);
			});

		glfwSetWindowFocusCallback(m_WindowHandle, [](GLFWwindow* window, int focused)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (focused)
				{
					case GLFW_TRUE:
					{
						WindowFocusEvent event;
						data.EventCallback(event);
						break;
					}
					case GLFW_FALSE:
					{
						WindowLostFocusEvent event;
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
			{
				WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallback(event);
			});
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_WindowHandle);
		s_WindowCount--;
		if (s_WindowCount == 0)
			glfwTerminate();
	}

	void Window::SetTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_WindowHandle, title.c_str());
		m_Data.Title = title;
	}

	void Window::Update()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
