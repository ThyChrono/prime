
project "prime"
    language "C++"
    kind "StaticLib"

    targetdir(targetDir)
    objdir(objDir)

    pchheader "pch.h"
    pchsource "src/pch.cpp"

    files
    {
        "prime.lua",
        "src/**.h",
        "src/**.cpp"
    }

    includedirs 
    {
        "src"
    }

    externalincludedirs 
    {
        "%{includeDirs.entt}",
        "%{includeDirs.spdlog}",
        "%{includeDirs.glad}",
        "%{includeDirs.glm}"
    }

    links
    {
        "glad"
    }