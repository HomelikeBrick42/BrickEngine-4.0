#include "pch.h"
#include "Time.h"

#include <GLFW/glfw3.h>

namespace BrickEngine {

    float Time::s_LastTime = 0.0f;
    float Time::s_Delta = 0.0f;

    void Time::BeginFrame()
    {
        s_Delta = (float)glfwGetTime() - s_LastTime;
    }

    void Time::EndFrame()
    {
        s_LastTime = (float)glfwGetTime();
    }

    float Time::GetSeconds()
    {
        return (float)glfwGetTime();
    }

    float Time::GetMilliseconds()
    {
        return (float)glfwGetTime() * 1000.0f;
    }

    float Time::GetDelta()
    {
        return s_Delta;
    }

}
