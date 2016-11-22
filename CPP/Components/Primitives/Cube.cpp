#include "Cube.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"

#ifdef __APPLE__
#define VERTEX_SHADER "basic.vert"
#define FRAGMENT_SHADER "basic.frag"
#else
#define VERTEX_SHADER "shaders/basic.vert"
#define FRAGMENT_SHADER "shaders/basic.frag"
#endif


#include "Time.hpp"


GLfloat  cubeVerts[][3] = {
    -1, -1, 1 , // V0
    -1, 1,  1 , // V1
    1,  1, 1 ,  // V2
    1,  -1,  1 ,// V3
    -1, -1, -1 ,// V4
    -1, 1,  -1 ,// V5
    1,  1, -1 , // V6
    1,  -1,  -1 // V7
};

GLfloat  cubeColors[][3] = {
    {  0,  0,  0 }, //0
    {  0,  0,  1 }, //1
    {  0,  1,  0 }, //2
    {  0,  1,  1 }, //3
    {  1,  0,  0 }, //4
    {  1,  0,  1 }, //5
    {  1,  1,  0 }, //6
    {  1,  1,  1 }, //7
};

GLushort cubeIndices[] = {
    0,3,1, 3,2,1,   // 36 of indices
    7,4,6, 4,5,6,
    4,0,5, 0,1,5,
    3,7,2, 7,6,2,
    1,2,5, 2,6,5,
    3,0,7, 0,4,7};

namespace OME {
    
    Cube::Cube(){
    
    }
    Cube::~Cube(){
    
    }
    
    bool Cube::init(){
        
        program.loadShaders(VERTEX_SHADER, FRAGMENT_SHADER);
        
        
        return false;
    }
    
    void Cube::update(){
        static float rotYAngle = 0;
        rotYAngle += 1 * Time::deltaTime();
        if(rotYAngle > 360) rotYAngle = 0;
        
        go->transform()->mRotation = vec3(0, rotYAngle, 0);
    }
    
    void Cube::draw(){
    
        program.use();
        glEnable(GL_DEPTH_TEST);
        
        glm::mat4 modelMatrix   = go->transform()->getMatrix();
        glm::mat4 viewMat       = Camera::instance()->getViewMatrix();
        glm::mat4 projMatrix    = Camera::instance()->getProjectionMatrix();
        
        program.setUniform("uModelMatrix",      modelMatrix);
        program.setUniform("uViewMatrix",       viewMat);
        program.setUniform("uProjectionMatrix", projMatrix);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, cubeVerts);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, cubeColors);
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, cubeIndices);
    }
}
