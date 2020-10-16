#pragma once

#include "BrickEngine/Core/Base.h"

#include "BrickEngine/Events/KeyEvent.h"
#include "BrickEngine/Events/MouseEvent.h"

#include "BrickEngine/Core/Window.h"

namespace BrickEngine {

	class Input
	{
	public:
		static void Init(Window* window);
		static void EndFrame();

		static bool GetKey(KeyCode key);
		static bool GetKeyDown(KeyCode key);
		static bool GetKeyUp(KeyCode key);

		static glm::vec2 GetMousePosition();
		static glm::vec2 GetMouseDelta();

		static bool GetMouseButton(MouseButton button);
		static bool GetMouseButtonDown(MouseButton button);
		static bool GetMouseButtonUp(MouseButton button);

		static void SetCursorState(CursorState state);

		static void OnEvent(Event& e);
	private:
		Input() = default;
	};

}
