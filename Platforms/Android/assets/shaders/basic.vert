#version 300 es
in vec2        aPosition;
in vec3        aColor;

uniform mat4        uModelMatrix;
uniform mat4        uViewMatrix;
uniform mat4        uProjectionMatrix;


out vec4       vColor;

void main() {
    gl_Position   = vec4(aPosition, 0.0, 0.0) * uModelMatrix;
    vColor = vec4(aColor, 1.0);
}
