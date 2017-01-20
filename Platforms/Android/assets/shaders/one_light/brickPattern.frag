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

uniform vec3 brickColor;
uniform vec3 mortarColor;
uniform vec2 rectangularSize;
uniform vec2 brickPercent;

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


vec3 color;
vec2 position;
vec2 useBrick;

void main() {

    position = objCoord.xy / rectangularSize;
    if(fract(position.y * 0.5) > 0.5){
        position.x += 0.5;
    }
    
    position = fract(position);
    useBrick = step(position, brickPercent);
    color = mix(mortarColor, brickColor, useBrick.x * useBrick.y);

    fragColor = vec4(color * phongShading(), 1.0);
}
