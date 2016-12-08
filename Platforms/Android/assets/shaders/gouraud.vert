#version 300 es


// STRUCTS
struct uTransform{
    mat4 model;
    mat4 view;
    mat4 projection;
    mat4 normal;
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

layout(location = 0) in vec3        aPosition;
layout(location = 1) in vec3        aNormal;
layout(location = 2) in vec2        aTexCoord;

uniform uTransform  transform;
uniform uMaterial   material;
uniform uLight      light;

out vec4 finalColor;

vec3 gouraud(){
    vec3 normal = normalize(vec3(transform.normal * vec4(aNormal, 0.0)));
    vec3 eye = vec3( transform.model * transform.view * vec4(aPosition, 1.0));

    vec3 lightDir = normalize(light.position - eye);
    
    float cosAngle = max(0.0, dot(normal, lightDir));
    
    vec3 V = normalize(-eye);
    vec3 R = reflect(-lightDir, normal);
    float intensity = pow( max(0.0, dot(V, R)), material.shininess);

    vec3 ambient = material.ambient * light.ambient;
    vec3 diffuse = cosAngle * material.diffuse * light.diffuse;
    vec3 specular = intensity * material.specular * light.specular;
    
    return ambient + diffuse + specular;
}

void main() {
    
    finalColor = vec4(gouraud(), 1.0);
    
    gl_Position   = transform.projection * transform.view *  transform.model * vec4(aPosition, 1.0);
    gl_PointSize = 5.0;
}
