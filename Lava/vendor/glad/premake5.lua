project "GLAD"
    kind "StaticLib"
    language "C"
    staticruntime "off"
    warnings "off"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/glad/gl.h",
        "include/KHR/khrplatform.h",
        "src/gl.c"
    }

    includedirs {
        "include"
    }
    
    filter "system:linux"
        pic "On"
        systemversion "latest"
    
    filter "system:macosx"
        pic "On"

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "speed"
    
    filter "configurations:Dist"
        runtime "Release"
        optimize "speed"
        symbols "off"