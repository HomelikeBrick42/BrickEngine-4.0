#pragma once

#include "BrickEngine/Events/Event.h"

namespace BrickEngine {

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
	private:
		uint32_t m_Width, m_Height;
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(int xPos, int yPos)
			: m_XPos(xPos), m_YPos(yPos) {}

		int GetXPos() const { return m_XPos; }
		int GetYPos() const { return m_YPos; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMoveEvent: " << m_XPos << ", " << m_YPos;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowMoved)
	private:
		int m_XPos, m_YPos;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowFocusEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowFocus)
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() = default;

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowLostFocusEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowLostFocus)
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
	};

}
