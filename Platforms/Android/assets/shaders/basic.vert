#version 300 es

layout(location = 0) in vec3        aPosition;
layout(location = 1) in vec3        aColor;

uniform mat4        uModelMatrix;
uniform mat4        uViewMatrix;
uniform mat4        uProjectionMatrix;

out vec4       vColor;

void main() {
    gl_Position   = uProjectionMatrix * uViewMatrix *  uModelMatrix * vec4(aPosition, 1.0);
    vColor = vec4(aColor, 1.0);
}
