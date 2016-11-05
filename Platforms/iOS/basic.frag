#version 330 core

in vec2 fTexCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

out vec4 frag_Color;

void main(){
    frag_Color = texture(uTexture1, fTexCoord);
    
    frag_Color = mix(texture(uTexture1, fTexCoord), texture(uTexture2, fTexCoord), 0.5);
}
