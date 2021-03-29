#version 330 core
out vec4 color;

in vec3 o_pos, modelview_pos;

uniform vec3 viewport_pos;

uniform int draw_mode;

void main()
{
    switch(draw_mode)
    {
        case 0:
            vec3 p = o_pos;
            p.x -= floor(p.x);
            p.y -= floor(p.y);
            p.z -= floor(p.z);
            color = vec4(p, 1);
            break;
        case 1:
            vec3 diff = viewport_pos - modelview_pos;
            float length = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
            float distance = length / 25 - 1.5f;
            float distance2 = length / 750;
            color = vec4(1 - distance2, 1 - distance2, 1 - distance2, min(distance, 1));
            if(color.a <= 0) discard;
            break;
    }
}