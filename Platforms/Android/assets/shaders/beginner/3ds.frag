#version 300 es
precision mediump float;

uniform vec4 Ka;
uniform vec4 Kd;
uniform vec4 Ks;
uniform float Ksh;

out vec4 finalColor;

void main() {
    finalColor = Ka;
}
