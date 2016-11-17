#include "Transform.hpp"

#include "matrix_transform.hpp"

namespace OME {
    Transform::Transform(GameObject * const gameObject) : IComponent(gameObject){
        
    }
    
    Transform::~Transform(){}
    
    
    mat4 Transform::getMatrix(){
        mat4 returnValue;
        return glm::translate(returnValue, mPosition) * glm::scale(returnValue, mScale)
        * glm::rotate(returnValue, mRotation.x, vec3(1, 0, 0))
        * glm::rotate(returnValue, mRotation.y, vec3(0, 1, 0))
        * glm::rotate(returnValue, mRotation.z, vec3(0, 0, 1));
    }
    
}


