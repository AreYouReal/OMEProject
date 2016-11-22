#include "Primitives.hpp"

#include "Utils.hpp"
#include "GameObject.hpp"
#include "../Transform/Transform.hpp"
#include "Camera.hpp"


#ifdef __APPLE__
#define VERTEX_SHADER "basic.vert"
#define FRAGMENT_SHADER "basic.frag"
#else
#define VERTEX_SHADER "shaders/basic.vert"
#define FRAGMENT_SHADER "shaders/basic.frag"
#endif

using std::ifstream;
using std::ostringstream;


const GLfloat vertices[] = {
    1.0f,  2.0f,
    -1.0f,  2.0f,
    1.0f,  1.0f,
    -1.0f,  1.0f,
    1.0f,  0.0f,
    -1.0f,  0.0f,
    1.0f, -1.0f,
    -1.0f, -1.0f,
    1.0f, -2.0f,
    -1.0f, -2.0f
};

GLfloat  colors[] ={
    0.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0
};

namespace OME {
    Primitives::Primitives(){
        
    }
    
    Primitives::~Primitives(){
        // Remove shader program
    }
    
    bool Primitives::init(){
        program.loadShaders(VERTEX_SHADER, FRAGMENT_SHADER);
        
        return true;
    }
    
    void Primitives::draw(){
        program.use();
        renderPrimitive();
    }

    void Primitives::renderPrimitive(){
        glDisable(GL_CULL_FACE);
        glLineWidth(10.0f);

        glm::mat4 modelMatrix   = go->transform()->getMatrix();
//        glm::mat4 viewMat       = Camera::instance()->getViewMatrix();
//        glm::mat4 projMatrix    = Camera::instance()->getProjectionMatrix();
        
        program.setUniform("uModelMatrix",      modelMatrix);
//        program.setUniform("uViewMatrix",       viewMat);
//        program.setUniform("uProjectionMatrix", projMatrix);
        
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        int primitiveArraySize = sizeof(vertices);
        int vertexSize = (sizeof(float) * 2);
        int numberOfElement = primitiveArraySize / vertexSize;
        
        
                        glDrawArrays(primitive, 0, numberOfElement);
//        switch (primitive) {
//            case GL_POINTS:
//                glDrawArrays(primitive, 0, numberOfElement);
//                break;
//            case GL_LINES:
//                glDrawArrays(primitive, 0, numberOfElement);
//                break;
//            case GL_LINE_LOOP:
//                glDrawArrays(primitive, 0, numberOfElement);
//                break;
//            case GL_LINE_STRIP:
//                glDrawArrays(primitive, 0, numberOfElement);
//                break;
//            case GL_TRIANGLES:
//                glDrawArrays(primitive, 0, numberOfElement);
//                break;
//            case GL_TRIANGLE_STRIP:
//                glDrawArrays(primitive, 0, numberOfElement);
//                break;
//            case GL_TRIANGLE_FAN:
//                glDrawArrays(primitive, 0, numberOfElement);
//                break;
//        }
        
    }
}

