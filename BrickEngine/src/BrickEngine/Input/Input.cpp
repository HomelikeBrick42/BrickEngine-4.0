#include "pch.h"
#include "Input.h"

#include <GLFW/glfw3.h>

namespace BrickEngine {

	struct InputData
	{
		Window* s_Window;

		glm::vec2 s_MousePos;
		glm::vec2 s_LastMousePos;

		std::array<bool, 512> s_KeysPressed;
		std::array<bool, 512> s_NewKeysPressed;
		std::array<bool, 512> s_KeysReleased;

		std::array<bool, 16> s_MouseButtonsPressed;
		std::array<bool, 16> s_NewMouseButtonsPressed;
		std::array<bool, 16> s_MouseButtonsReleased;
	};
	static Scope<InputData> s_Data = nullptr;

	void Input::Init(Window* window)
	{
		s_Data = CreateScope<InputData>();

		s_Data->s_Window = window;

		double xPos, yPos;
		glfwGetCursorPos((GLFWwindow*)s_Data->s_Window->GetNativeWindowHandle(), &xPos, &yPos);
		s_Data->s_MousePos = glm::vec2((float)xPos, (float)yPos);
		s_Data->s_LastMousePos = glm::vec2((float)xPos, (float)yPos);

		for (uint32_t i = 0; i < 350; i++)
		{
			s_Data->s_KeysPressed[i] = false;
			s_Data->s_NewKeysPressed[i] = false;
			s_Data->s_KeysReleased[i] = false;
		}

		for (uint32_t i = 0; i < 8; i++)
		{
			s_Data->s_MouseButtonsPressed[i] = false;
			s_Data->s_NewMouseButtonsPressed[i] = false;
			s_Data->s_MouseButtonsReleased[i] = false;
		}
	}

	void Input::EndFrame()
	{
		for (uint32_t i = 0; i < 350; i++)
		{
			s_Data->s_NewKeysPressed[i] = false;
			s_Data->s_KeysReleased[i] = false;
		}

		for (uint32_t i = 0; i < 8; i++)
		{
			s_Data->s_NewMouseButtonsPressed[i] = false;
			s_Data->s_MouseButtonsReleased[i] = false;
		}

		s_Data->s_LastMousePos = s_Data->s_MousePos;
	}

	bool Input::GetKey(KeyCode key)
	{
		return s_Data->s_KeysPressed[(int)key];
	}

	bool Input::GetKeyDown(KeyCode key)
	{
		return s_Data->s_NewKeysPressed[(int)key];
	}

	bool Input::GetKeyUp(KeyCode key)
	{
		return s_Data->s_KeysReleased[(int)key];
	}

	glm::vec2 Input::GetMousePosition()
	{
		return s_Data->s_MousePos;
	}

	glm::vec2 Input::GetMouseDelta()
	{
		return s_Data->s_MousePos - s_Data->s_LastMousePos;
	}

	bool Input::GetMouseButton(MouseButton button)
	{
		return s_Data->s_MouseButtonsPressed[(int)button];
	}

	bool Input::GetMouseButtonDown(MouseButton button)
	{
		return s_Data->s_NewMouseButtonsPressed[(int)button];
	}

	bool Input::GetMouseButtonUp(MouseButton button)
	{
		return s_Data->s_MouseButtonsReleased[(int)button];
	}

	void Input::SetCursorState(CursorState state)
	{
		glfwSetInputMode((GLFWwindow*)s_Data->s_Window->GetNativeWindowHandle(), GLFW_CURSOR, (int)state);
	}

	void Input::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e)
			{
				if ((int)e.GetKeyCode() == -1)
				{
					Log::Error("Unknown Keycode!");
					return false;
				}
				if (!s_Data->s_KeysPressed[(int)e.GetKeyCode()])
					s_Data->s_NewKeysPressed[(int)e.GetKeyCode()] = true;
				s_Data->s_KeysPressed[(int)e.GetKeyCode()] = true;
				return false;
			});
		dispatcher.Dispatch<KeyReleasedEvent>([](KeyReleasedEvent& e)
			{
				if ((int)e.GetKeyCode() == -1)
				{
					Log::Error("Unknown Keycode!");
					return false;
				}
				s_Data->s_KeysPressed[(int)e.GetKeyCode()] = false;
				s_Data->s_KeysReleased[(int)e.GetKeyCode()] = true;
				return false;
			});

		dispatcher.Dispatch<MouseButtonPressedEvent>([](MouseButtonPressedEvent& e)
			{
				if ((int)e.GetMouseButton() == -1)
				{
					Log::Error("Unknown Mousecode!");
					return false;
				}
				if (!s_Data->s_MouseButtonsPressed[(int)e.GetMouseButton()])
					s_Data->s_NewMouseButtonsPressed[(int)e.GetMouseButton()] = true;
				s_Data->s_MouseButtonsPressed[(int)e.GetMouseButton()] = true;
				return false;
			});
		dispatcher.Dispatch<MouseButtonReleasedEvent>([](MouseButtonReleasedEvent& e)
			{
				if ((int)e.GetMouseButton() == -1)
				{
					Log::Error("Unknown Mousecode!");
					return false;
				}
				s_Data->s_MouseButtonsPressed[(int)e.GetMouseButton()] = false;
				s_Data->s_MouseButtonsReleased[(int)e.GetMouseButton()] = true;
				return false;
			});

		dispatcher.Dispatch<MouseMovedEvent>([](MouseMovedEvent& e)
			{
				s_Data->s_MousePos = glm::vec2(e.GetX(), e.GetY());
				return false;
			});
	}

}
