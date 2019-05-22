#version 330 core
out vec4 fragColor;

in vec3 f_color;

void main() {
    fragColor = vec4(1., 0.5, 0.5, 1) * vec4(f_color, 1);
}