workspace "Lava"
    architecture "x64"

    configurations {
        "Release",
        "Debug",
        "Dist"
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "Lava/vendor/GLFW/include"
include "Lava/vendor/GLFW/premake5.lua"

project "Lava"
    location "Lava"
    kind "SharedLib"
    language "C++"
    systemversion "latest"    

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lvpch.h"
    pchsource "Lava/src/lvpch.cpp"

    files {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDirs.GLFW}"
    }

    links {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "LV_PLATFORM_WINDOWS",
            "LV_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

        filter { "configurations:Debug" }
        defines { "LV_DEBUG" }
        symbols "On"
        buildoptions "/MDd"
        
        filter { "configurations:Release" }
        defines { "LV_RELEASE" }
        optimize "On"
        buildoptions "/MD"

        filter { "configurations:Dist" }
        defines { "LV_DIST" }
        optimize "On"
        buildoptions "/MD"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    systemversion "latest"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }
    
    includedirs {
        "Lava/vendor/spdlog/include",
        "Lava/src",
        "%{prj.name}/src"
    }
    
    links {
        "Lava"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0"
    
        defines {
            "LV_PLATFORM_WINDOWS"
        }
    
    filter { "configurations:Debug" }
        defines { "LV_DEBUG" }
        symbols "On"
        buildoptions "/MDd"
    
    filter { "configurations:Release" }
        defines { "LV_RELEASE" }
        optimize "On"
        buildoptions "/MD"    

    filter { "configurations:Dist" }
        defines { "LV_DIST" }
        optimize "On"
        buildoptions "/MD"        
