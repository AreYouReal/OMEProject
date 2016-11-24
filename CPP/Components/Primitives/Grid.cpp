#include "Grid.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Time.hpp"

#ifdef __APPLE__
#define VERTEX_SHADER "grid.vert"
#define FRAGMENT_SHADER "grid.frag"
#else
#define VERTEX_SHADER "shaders/grid.vert"
#define FRAGMENT_SHADER "shaders/grid.frag"
#endif

namespace OME {
    
    bool Grid::init(){
    
        program.loadShaders(VERTEX_SHADER, FRAGMENT_SHADER);
        
        createGrid(xDimension, zDimension, xDivision, zDivision);
        
        return true;
    }
    
    void Grid::update(){
        static float rotYAngle = 0;
        rotYAngle += 1 * Time::deltaTime();
        if(rotYAngle > 360) rotYAngle = 0;
        
        go->transform()->mRotation = vec3(0, rotYAngle, 0);
    }
    
    void Grid::draw(){
        program.use();
        glDisable(GL_CULL_FACE);
        glLineWidth(10.0f);
        
        glm::mat4 modelMatrix   = go->transform()->getMatrix();
        glm::mat4 viewMat       = Camera::instance()->getViewMatrix();
        glm::mat4 projMatrix    = Camera::instance()->getProjectionMatrix();
        
        program.setUniform("model",      modelMatrix);
        program.setUniform("view",       viewMat);
        program.setUniform("projection", projMatrix);
        
        glBindVertexArray(vao);
        glDrawElements(GL_LINES, ((xDivision + 1) + (zDivision + 1)) * 2, GL_UNSIGNED_SHORT, 0 );

    }
    
    
    void Grid::createGrid(float xDim, float zDim, int xDiv, int zDiv){
        unsigned int vertexNum = 3 * (xDiv + 1) * (zDiv + 1) * 2;
        unsigned int indexNum = ((xDiv + 1) + (zDiv + 1)) * 2;
        
        float *gridVertices = new float[vertexNum];
        unsigned short *gridIndices = new unsigned short[indexNum];
        
        float xInterval = xDim/xDiv;
        float zInterval = zDim/zDiv;
        float xHalf     = xDim/2;
        float zhalf     = zDim/2;
        int     i       = 0;
        
        for(int j = 0; j < xDiv+1; ++j){
            gridVertices[i++] = j * xInterval - xHalf; gridVertices[i++] = 0.0f; gridVertices[i++] = zhalf;
            gridVertices[i++] = j * xInterval - xHalf; gridVertices[i++] = 0.0f; gridVertices[i++] = -zhalf;
        }
        
        for(int j = 0; j < zDiv + 1; ++j){
            gridVertices[i++] = -xHalf; gridVertices[i++] = 0.0f; gridVertices[i++] = j * zInterval - zhalf;
            gridVertices[i++] = xHalf; gridVertices[i++] = 0.0f; gridVertices[i++] = j * zInterval - zhalf;
        }
        
        i = 0;
        
        for(int j = 0; j < xDiv + 1; ++j){
            gridIndices[i++] = 2 * j;
            gridIndices[i++] = 2 * j + 1;
        }
        
        for(int j = 0; j < zDiv + 1; ++j){
            gridIndices[i++] = ((xDiv + 1)* 2) + (2 * j);
            gridIndices[i++] = ((xDiv + 1)* 2) + (2 * j + 1);
        }
        
        unsigned int size = vertexNum * sizeof(float);
        glGenBuffers(1, &vertexBuffer);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, gridVertices);
        
        unsigned int indicesSize = sizeof(unsigned short) * indexNum;
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, 0, GL_STATIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indicesSize, gridIndices);
        
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        
        glBindVertexArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        delete[] gridVertices;
        delete[] gridIndices;
    }
    
}
