
targetDir = "%{wks.location}/bin/%{prj.name}"
objDir = "%{wks.location}/bin-int"

includeDirs = {}
includeDirs["entt"] = "%{wks.location}/vendor/entt/include"
includeDirs["spdlog"] = "%{wks.location}/vendor/spdlog/include"

workspace "prime"
    startproject "prime-editor"

    configurations
    {
        "Debug",
        "Release"
    }

    flags 
    {
        "MultiProcessorCompile"
    }

    externalwarnings "off"
    characterset "ASCII"

    filter {"system:windows", "configurations:*"}
        architecture "x64"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "on"

    filter "configurations:Debug"
        symbols "on"
        runtime "Debug"

        defines
        {
            "PCONFIG_DEBUG"
        }

    filter "configurations:Release"
        symbols "off"
        runtime "Release"
        optimize "full"

        defines
        {
            "PCONFIG_RELEASE"
        }

    include "prime/prime.lua"
    include "prime-editor/prime-editor.lua"