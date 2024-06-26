
project "prime-editor"
    language "C++"
    kind "ConsoleApp"

    targetdir(targetDir)
    objdir(objDir)

    files
    {
        "prime-editor.lua",
        "src/**.h",
        "src/**.cpp"
    }

    includedirs 
    {
        "src",
        "%{wks.location}/prime/src"
    }

    externalincludedirs 
    {
        "%{includeDirs.entt}",
        "%{includeDirs.spdlog}",
        "%{includeDirs.glm}"
    }

    links
    {
        "prime"
    }