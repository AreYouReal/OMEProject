#version 300 es
in vec4        VertexPosition;
in vec4        VertexColor;
uniform float  RadianAngle;

out vec4       TriangleColor;

void main() {
    mat2 rotation = mat2(cos(RadianAngle),sin(RadianAngle),
                         -sin(RadianAngle),cos(RadianAngle));
    gl_Position   = mat4(rotation)*VertexPosition;
    TriangleColor = VertexColor;
}
