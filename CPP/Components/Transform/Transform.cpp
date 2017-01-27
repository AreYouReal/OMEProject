#include "Transform.hpp"

#include "matrix_transform.hpp"

namespace OME {
    
    
    glm::vec3 OME::Transform::WORLD_UP = vec3(0, 1, 0);
    
    Transform::Transform(){
        mPosition   = vec3(0, 0, 0);
        mScale      = vec3(1, 1, 1);
        mRotation   = vec3(0, 0, 0);
        mFront      = vec3(0, 0, -1);
        mUp         = vec3(0, 1, 0);
        mRight      = vec3(1, 0, 0);
    }
    
    Transform::~Transform(){}   
    
    mat4 Transform::getMatrix(){
        mat4 returnValue;
        returnValue = glm::translate(returnValue, mPosition) * glm::scale(returnValue, mScale)
        * glm::rotate(returnValue, mRotation.x, vec3(1, 0, 0))
        * glm::rotate(returnValue, mRotation.y, vec3(0, 1, 0))
        * glm::rotate(returnValue, mRotation.z, vec3(0, 0, 1));
        return returnValue;
    }
    
    
    void Transform::rotate(vec3 eulerAngles){
        mRotation += eulerAngles;
        mat4 rotMatrix;
        rotMatrix = (glm::rotate(rotMatrix, eulerAngles.x, vec3(1, 0, 0))
                              * glm::rotate(rotMatrix, eulerAngles.y, vec3(0, 1, 0))
                                            *glm::rotate(rotMatrix, eulerAngles.z, vec3(0, 0, 1)));
        
        mFront =vec3( glm::vec4(mFront, 1.0f) * rotMatrix);
        mRight = vec3(glm::vec4(mRight, 1.0f) * rotMatrix);
    
    }
    
    void Transform::translate(vec3 offset){
        mPosition += offset;
    }
    
    void Transform::scale(vec3 scale){
    
    }
}


