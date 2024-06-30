
targetDir = "%{wks.location}/bin/%{prj.name}"
objDir = "%{wks.location}/bin-int"

-- include directories
includeDirs = {}
includeDirs["entt"] = "%{wks.location}/vendor/entt/include"
includeDirs["spdlog"] = "%{wks.location}/vendor/spdlog/include"
includeDirs["glad"] = "%{wks.location}/vendor/glad/include"
includeDirs["glm"] = "%{wks.location}/vendor/glm/include"

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

    group "core"
        include "prime/prime.lua"
        include "prime-editor/prime-editor.lua"
    group ""

    group "vendor"
        include "vendor/glad/glad.lua"
    group ""