#pragma once

namespace BrickEngine {

	enum class MouseButton
	{
		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
		Button4 = 3,
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,

		Left = Button1,
		Right = Button2,
		Middle = Button3
	};

	enum class CursorState
	{
		Normal = 0x00034001,
		Hidden = 0x00034002,
		Locked = 0x00034003
	};

}
