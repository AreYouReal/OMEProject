#version 300 es
precision mediump float;


struct uMaterial{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct uLight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

in vec3 normalCoord;
in vec3 eyeCoord;
in vec3 objCoord;

uniform uLight      light;
uniform uMaterial   material;
uniform float       directionLight;

uniform vec3    modelColor;
uniform vec3    dotColor;
uniform float   side;
uniform float   radianAngle;


float dotSize = side * 0.25;
vec2 square = vec2(side, side);

out vec4 fragColor;

vec3 phongShading(){
    vec3 nNorm = normalize(normalCoord);
    vec3 nEyeCoord = normalize(eyeCoord);
    
    vec3 nLightVec;
    if(directionLight > 0.0f){
        nLightVec = normalize( light.position - eyeCoord);
    }else{
        nLightVec = normalize( light.position );
    }
        
    // Diffuse intensity
    float cosAngle = max(0.0, dot( nNorm, nLightVec));

    // Specular intensity
    vec3 V = -nEyeCoord;
    vec3 R = reflect(-nLightVec, nNorm);
    float sIntensity = pow( max(0.0, dot(R, V)), material.shininess);
    
    vec3 ambient = material.ambient * light.ambient;
    vec3 diffuse = cosAngle * material.diffuse * light.diffuse;
    vec3 specular = sIntensity * material.specular * light.specular;
    
    return ambient + diffuse + specular;
}

void main() {
    
    float cos = cos(radianAngle);
    float sin = sin(radianAngle);
    
    mat2 rotation = mat2(cos, -sin, sin, cos);

    vec2 position = mod(rotation * gl_FragCoord.xy, square) - square * 0.5;
    float length = length(position);
    float inside = step(length, dotSize);
    fragColor = vec4(mix(modelColor, dotColor, inside), 1.0);
    
    fragColor = fragColor * vec4(phongShading(), 1.0);
}
