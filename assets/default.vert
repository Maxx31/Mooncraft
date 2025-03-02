#version 450 core

layout(location = 0) in vec3 position;
out vec3 vert_pos;

uniform mat4 CamMatrix = mat4(1);

void main() {
    vert_pos = position;
    gl_Position = CamMatrix * vec4(vert_pos, 1);
}