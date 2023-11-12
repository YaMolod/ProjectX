workspace "ProjectX"
	architecture "x64"
	startproject "ProjectX"
	
	configurations
	{
		"Debug",
		"Release",
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["bx"] = "ThirdParty/bgfx/bx/include"
	IncludeDir["bimg"] = "ThirdParty/bgfx/bimg/include"
	IncludeDir["bgfx"] = "ThirdParty/bgfx/bgfx/include"
	IncludeDir["glfw"] = "ThirdParty/bgfx/glfw/include"
	IncludeDir["imgui"] = "ThirdParty/imgui"

	group "Dependencies"
		include "ThirdParty/bgfx"
		include "ThirdParty/imgui"
	group ""

project "ProjectX"
	location "ProjectX"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/utils/bgfxUtils/**.h",
		"%{prj.name}/utils/bgfxUtils/**.cpp",
		"%{prj.name}/vendor/meshoptimizer/src/**.h",
		"%{prj.name}/vendor/meshoptimizer/src/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/source",
		"%{prj.name}/utils",
		"%{prj.name}/vendor",
		"%{IncludeDir.bx}",
		"%{IncludeDir.bimg}",
		"%{IncludeDir.bgfx}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.imgui}",
	}

	links
	{
		"bx",
		"bimg",
		"bgfx",
		"glfw",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"