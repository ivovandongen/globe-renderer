#version 330 core
out vec4 fragColor;

in vec3 worldPosition;

uniform sampler2D bltin_texture0;

// TODO Gather common mathematical constants in a pre-amble
#define M_PI 3.1415926535897932384626433832795

const float oneOver2PI = 1.0 / (2.0 * M_PI);
const float oneOverPI = 1.0 / M_PI;

vec2 computeTextureCoordinates(vec3 normal) {
    return vec2(
        atan(normal.y, normal.x) * oneOver2PI + 0.5,
        asin(normal.z) * oneOverPI + 0.5
    );
}


void main() {
    vec3 normal = normalize(worldPosition);
    fragColor = texture(bltin_texture0, computeTextureCoordinates(normal));
}