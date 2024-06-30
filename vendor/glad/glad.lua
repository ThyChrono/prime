
project "glad"
    language "C"
    kind "StaticLib"

    targetdir(targetDir)
    objdir(objDir)

    files
    {
        "glad.lua",
        "include/**.h",
        "src/**.c"
    }

    includedirs 
    {
        "include"
    }

    links
    {
        "OpenGL32.lib"
    }