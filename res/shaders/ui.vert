#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;

out vec2 tex_coords;

uniform mat4 transform_static;
uniform mat4 projection;

void main()
{
    tex_coords = tex;
    gl_Position = projection * transform_static * vec4(pos, 1);
}