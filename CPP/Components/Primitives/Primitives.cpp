#include "Primitives.hpp"

#include "Utils.hpp"

#ifdef __APPLE
#define VERTEX_SHADER "primitiveVertex.glsl"
#define FRAGMENT_SHADER "primitiveFragment.glsl"
#else
#define VERTEX_SHADER "shaders/primitiveVertex.glsl"
#define FRAGMENT_SHADER "shaders/primitiveFragment.glsl"
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
    Primitives::Primitives(GameObject *const gameObject) : Mesh(gameObject){
        
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
        
    }
    
    
    
    void Primitives::renderPrimitive(){
        glDisable(GL_CULL_FACE);
        glLineWidth(10.0f);
        
        
        
        
        
    }
}

