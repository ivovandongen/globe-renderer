#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 bltin_model;
uniform mat4 bltin_view;
uniform mat4 bltin_projection;

void main() {
    gl_Position = bltin_projection * bltin_view * bltin_model * vec4(position, 1.0);
}