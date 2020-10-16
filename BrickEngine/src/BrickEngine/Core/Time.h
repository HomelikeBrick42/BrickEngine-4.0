#pragma once

namespace BrickEngine {

	class Time
	{
	public:
		static void BeginFrame();
		static void EndFrame();
		static float GetSeconds();
		static float GetMilliseconds();
		static float GetDelta();
	private:
		static float s_LastTime;
		static float s_Delta;
	private:
		Time() {}
	};

}
