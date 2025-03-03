#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

out vec3 vert_pos;
out vec2 vert_uv;

uniform mat4 CamMatrix = mat4(1);

void main()
{
    vert_uv = uv;
    vert_pos = position;
    gl_Position = CamMatrix * vec4(vert_pos, 1);
}