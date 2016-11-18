#pragma once

#include "IComponent.hpp"

#include "glm.hpp"

using vec3 = glm::vec3;
using mat4 = glm::mat4;

namespace OME {
    
    class Transform : public IComponent{
    public:
        Transform(GameObject * const gameObject);
        virtual ~Transform();
        
        
        glm::mat4 getMatrix();
        
        glm::vec3 mPosition;
        glm::vec3 mScale;
        glm::vec3 mRotation;
        glm::vec3 mFront;
        glm::vec3 mUp;
        glm::vec3 mRight;
    };
}


