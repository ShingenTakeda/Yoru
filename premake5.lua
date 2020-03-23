include("conanbuildinfo.premake.lua")

workspace("Yoru")
    conan_basic_setup()
    architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
    }
    
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Yoru"
    location "Yoru"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    linkoptions { conan_exelinkflags }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
    }

    includedirs {"%{prj.name}/src"}

    filter "configurations:Debug"
        defines "Y_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "Y_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "Y_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "ypch.h"
	pchsource "Yoru/src/ypch.cpp"

    
    files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
    }
    
    links
	{
		"Yoru"
    }
    
    filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"