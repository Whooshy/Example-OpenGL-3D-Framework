#version 330 core
layout(location = 0) in vec3 pos;

uniform mat4 projection, viewport, transform_static;
out vec3 o_pos, modelview_pos;

void main()
{
    o_pos = pos;
    vec4 mvp = transform_static * vec4(pos, 1);
    modelview_pos = mvp.xyz;
    gl_Position = projection * viewport * mvp;
}