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

uniform uLight      light[4];
uniform uMaterial   material;
uniform float       directionLight;

out vec4 fragColor;

vec3 phongShading(int i){
    vec3 nNorm = normalize(normalCoord);
    vec3 nEyeCoord = normalize(eyeCoord);
    
    vec3 nLightVec;
    if(directionLight > 0.0f){
        nLightVec = normalize( light[i].position - eyeCoord);
    }else{
        nLightVec = normalize( light[i].position );
    }
    
    
        
    // Diffuse intensity
    float cosAngle = max(0.0, dot( nNorm, nLightVec));

    // Specular intensity
    vec3 V = -nEyeCoord;
    vec3 R = reflect(-nLightVec, nNorm);
    float sIntensity = pow( max(0.0, dot(R, V)), material.shininess);
    
    vec3 ambient = material.ambient * light[i].ambient;
    vec3 diffuse = cosAngle * material.diffuse * light[i].diffuse;
    vec3 specular = sIntensity * material.specular * light[i].specular;
    
    return ambient + diffuse + specular;

}

void main() {
    
    vec3 multiLightColor = vec3(0.0);
    
    for(int i = 0; i < 4; ++i){
        multiLightColor += phongShading(i);
    }
    
    fragColor = vec4(multiLightColor, 1.0);
}
