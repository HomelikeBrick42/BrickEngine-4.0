workspace "BrickEngine"
	architecture "x64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["stb_image"] = "vendor/stb_image"
IncludeDir["entt"] = "vendor/entt/include"

-- Projects
group "Dependencies"
	include "BrickEngine/vendor/GLFW"
	include "BrickEngine/vendor/Glad"
	include "BrickEngine/vendor/imgui"
group ""

include "BrickEngine"
include "Game"
