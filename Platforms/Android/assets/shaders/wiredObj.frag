#version 300 es
precision mediump float;

uniform mediump vec3 ambient;

out vec4 finalColor;

void main() {
    finalColor = vec4(0.5, 0.5, 0.5, 1.0);
}
