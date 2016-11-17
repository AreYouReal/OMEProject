#pragma once

#include "IComponent.hpp"

#include "glm.hpp"

using vec3 = glm::vec3;
using mat4 = glm::mat4;

namespace OME {
    
    class Transform : public IComponent{
        
        Transform(GameObject * const gameObject);
        virtual ~Transform();
        
        
        mat4 getMatrix();
        
        vec3 mPosition;
        vec3 mScale;
        vec3 mRotation;
        vec3 mFront;
        vec3 mUp;
        vec3 mRight;
    };
}


