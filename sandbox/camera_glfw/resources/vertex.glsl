#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 bltin_model;
uniform mat4 bltin_view;
uniform mat4 bltin_projection;

out vec3 f_color;

void main() {
    gl_Position = bltin_projection * bltin_view * bltin_model * vec4(position, 1.0);
    f_color = color;
}