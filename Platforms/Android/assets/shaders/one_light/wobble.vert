#version 300 es

#define AMPLITUDE 1.2

// STRUCTS
struct uTransform{
    mat4 model;
    mat4 view;
    mat4 projection;
    mat3 normal;
};

//   SHADER

layout(location = 0) in vec4        aPosition;
layout(location = 1) in vec3        aNormal;

uniform float time;
uniform uTransform  transform;


out vec3 normalCoord;
out vec3 eyeCoord;

void main() {
    normalCoord = vec3(transform.normal * aNormal);
    eyeCoord = vec3(transform.view * transform.model * aPosition);
    vec4 vertexCoord = aPosition;
    vertexCoord.y += sin(vertexCoord.x + time) * AMPLITUDE;
    gl_Position   = transform.projection * transform.view *  transform.model * vertexCoord;
}
