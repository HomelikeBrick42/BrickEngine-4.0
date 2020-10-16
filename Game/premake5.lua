project "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"
	
	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"../BrickEngine/vendor/spdlog/include",
		"../BrickEngine/src",
		"../BrickEngine/vendor",
		"../BrickEngine/%{IncludeDir.glm}",
		"../BrickEngine/%{IncludeDir.Glad}",
		"../BrickEngine/%{IncludeDir.ImGui}",
		"../BrickEngine/%{IncludeDir.entt}"
	}

	links
	{
		"BrickEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BRICKENGINE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BRICKENGINE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BRICKENGINE_RELEASE"
		runtime "Release"
        optimize "on"
