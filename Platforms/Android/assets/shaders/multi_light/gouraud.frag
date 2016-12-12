#version 300 es
precision mediump float;

in vec4 finalColor;

out vec4 fragColor;

void main() {
    fragColor = finalColor;
}
