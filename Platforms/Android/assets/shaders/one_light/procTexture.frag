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
    
    if(objCoord.x > 0.0 && objCoord.z > 0.0){
        fragColor = vec4(1.0f, 0.0, 0.0, 1.0);
    }else if(objCoord.x > 0.0 && objCoord.z < 0.0){
        fragColor = vec4(0.0f, 1.0, 0.0, 1.0);
    }else if(objCoord.x < 0.0 && objCoord.z > 0.0){
        fragColor = vec4(0.0f, 1.0, 1.0, 1.0);
    }else{
        fragColor = vec4(1.0f, 0.0, 1.0, 1.0);
    }
    
    
    fragColor = fragColor * vec4(phongShading(), 1.0);
}
