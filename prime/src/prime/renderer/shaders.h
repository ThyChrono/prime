#pragma once

namespace prime::renderer {
    static const char* s_sprite_vertexshader = {

        R"(
    #version 330 core
    
    layout(location = 0) in vec3 a_position;
    layout(location = 1) in vec4 a_color;

    out vec4 v_color;

    void main()
    {
        v_color = a_color;
        gl_Position = vec4(a_position, 1.0);
    }
)"
    };

    static const char* s_sprite_fragmentshader = {

        R"(
    #version 330 core
    
    layout(location = 0) out vec4 color;

    in vec4 v_color;

    void main()
    {
        color = v_color;
    }
)"
    };
}