#version 300 es

layout(location = 0) in vec3        aPosition;
layout(location = 1) in vec3        aColor;


uniform TransformMatrices{
    mat4 model;
    mat4 view;
    mat4 projection;
};

out vec4       vColor;

void main() {
    gl_Position   = projection * view *  model * vec4(aPosition, 1.0);
    vColor = vec4(aColor, 1.0);
}
