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
IncludeDirs["GLAD"] = "Lava/vendor/glad/include"
IncludeDirs["ImGui"] = "Lava/vendor/imgui"
IncludeDirs["glm"] = "Lava/vendor/glm"

include "Lava/vendor/GLFW/premake5.lua"
include "Lava/vendor/glad/premake5.lua"
include "Lava/vendor/imgui/premake5.lua"

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
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.GLAD}",
        "%{IncludeDirs.ImGui}",
        "%{IncludeDirs.glm}"
    }

    links {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "LV_PLATFORM_WINDOWS",
            "LV_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
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
        "%{prj.name}/src",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.ImGui}"
    }
    
    links {
        "Lava",
        "ImGui"
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
