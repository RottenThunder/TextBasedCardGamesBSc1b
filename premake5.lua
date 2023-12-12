workspace "TextBasedCardGamesBSc1b"
	architecture "x86_64"
	startproject "TextBasedCardGamesBSc1b"

	configurations
	{
		"Debug",
		"Release"
	}

project "TextBasedCardGamesBSc1b"
	location "TextBasedCardGamesBSc1b"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	targetdir ("Bin/%{cfg.buildcfg}-%{cfg.architecture}-%{cfg.system}/%{prj.name}")
	objdir ("Bin-Int/%{cfg.buildcfg}-%{cfg.architecture}-%{cfg.system}/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CONFIG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CONFIG_RELEASE"
		runtime "Release"
		optimize "On"
