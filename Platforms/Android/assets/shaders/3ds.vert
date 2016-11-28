#version 300 es

layout(location = 0) in vec3        aPosition;
layout(location = 1) in vec3        aNormal;
layout(location = 2) in vec2        aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position   = projection * view *  model * vec4(aPosition, 1.0);
    gl_PointSize = 5.0;
}
