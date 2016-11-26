#include "Cube.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"

#include "type_ptr.hpp"

#ifdef __APPLE__
#define VERTEX_SHADER "uBlock.vert"
#define FRAGMENT_SHADER "uBlock.frag"
#else
#define VERTEX_SHADER "shaders/uBlock.vert"
#define FRAGMENT_SHADER "shaders/uBlock.frag"
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
        glDeleteBuffers(1, &vertexColorBuffer);
        glDeleteBuffers(1, &indexBuffer);
    }
    
    bool Cube::init(){
        
        program.loadShaders(VERTEX_SHADER, FRAGMENT_SHADER);
        
        int size = 24 * sizeof(float);
        
        glGenBuffers(1, &vertexColorBuffer);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexColorBuffer);
        glBufferData(GL_ARRAY_BUFFER, size + size, 0, GL_STATIC_DRAW );
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, cubeVerts);
        glBufferSubData(GL_ARRAY_BUFFER, size, size, cubeColors);
        
        unsigned int indexSize = sizeof(unsigned short) * 36;
        
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, 0, GL_STATIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexSize, cubeIndices);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        uniformBufferObject();
        
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
        
        glBindBuffer(GL_UNIFORM_BUFFER, UBO);
        

        
        
        glm::mat4 modelMatrix   = go->transform()->getMatrix();
        glm::mat4 viewMat       = Camera::instance()->getViewMatrix();
        glm::mat4 projMatrix    = Camera::instance()->getProjectionMatrix();
        
        glm::mat4* matrixBuff = (glm::mat4*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4*) * (3), GL_MAP_WRITE_BIT);
        
        OME::Utils::LOG_GL_ERROR();
        
        matrixBuff[0] = modelMatrix;
        matrixBuff[1] = viewMat;
        matrixBuff[2] = projMatrix;
        glUnmapBuffer(GL_UNIFORM_BUFFER);
        
//        program.setUniform("uModelMatrix",      modelMatrix);
//        program.setUniform("uViewMatrix",       viewMat);
//        program.setUniform("uProjectionMatrix", projMatrix);
        

        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexColorBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        
        glVertexAttribPointer(ShaderProgram::VERTEX_ATTRIB_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glVertexAttribPointer(ShaderProgram::NORMAL_ATTRIB_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, (void*)(24*sizeof(float)));
        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    
    
    void Cube::uniformBufferObject(){
        char blockIdx = glGetUniformBlockIndex(program.id, "TransformMatrices");
        GLint blockSize;
        glGetActiveUniformBlockiv(program.id, blockIdx, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
        GLint bindingPoint = 0;
        glUniformBlockBinding(program.id, blockIdx, bindingPoint);
        
        glGenBuffers(1, &UBO );
        glBindBuffer(GL_UNIFORM_BUFFER, UBO);
        glBufferData(GL_UNIFORM_BUFFER, blockSize, 0, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, UBO);
        
        
        
    
    }
}
