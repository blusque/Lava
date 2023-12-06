workspace "Lava"
    architecture "x64"

    configurations {
        "Release",
        "Debug",
        "Dist"
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Lava"
    location "Lava"
    kind "SharedLib"
    language "C++"
    systemversion "latest"    

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
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
        
        filter { "configurations:Release" }
        defines { "LV_RELEASE" }
        optimize "On"

        filter { "configurations:Dist" }
        defines { "LV_DIST" }
        optimize "On"

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
    
    filter { "configurations:Release" }
        defines { "LV_RELEASE" }
        optimize "On"
    
    filter { "configurations:Dist" }
        defines { "LV_DIST" }
        optimize "On"
        