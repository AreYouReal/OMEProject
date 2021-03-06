#version 300 es


// STRUCTS
struct uTransform{
    mat4 model;
    mat4 view;
    mat4 projection;
    mat3 normal;
};

struct uMaterial{
    vec3    ambient;
    vec3    diffuse;
    vec3    specular;
    float   shininess;
};

struct uLight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//   SHADER

layout(location = 0) in vec4        aPosition;
layout(location = 1) in vec3        aNormal;

uniform uTransform  transform;


out vec3 normalCoord;
out vec3 eyeCoord;
out vec3 objCoord;

void main() {
    normalCoord = vec3(transform.normal * aNormal);
    eyeCoord = vec3(transform.view * transform.model * aPosition);
    objCoord = aPosition.xyz;
    gl_Position   = transform.projection * transform.view *  transform.model * aPosition;
}
