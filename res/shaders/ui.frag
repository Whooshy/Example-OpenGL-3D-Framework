#version 330 core
out vec4 color;

uniform int draw_mode;

uniform vec4 color_in;

in vec2 tex_coords;

uniform sampler2D tex;

void main()
{
    color = color_in;
    
    switch(draw_mode)
    {
        case 0:
            color = color_in;
        break;
        case 1:
            vec4 t = texture(tex, tex_coords);
            if(t.a == 0) discard;
            color = t;
        break;
    }
}