#pragma once

#include "IComponent.hpp"
#include "glm.hpp"
#include "quaternion.hpp"

using vec3 = glm::vec3;
using mat4 = glm::mat4;

struct Transform : public IComponent{

    Transform(GameObject * const gameObject);
    virtual ~Transform();
    
    vec3 mPosition;
    vec3 mScale;
    vec3 mRotation;
    vec3 mFront;
    vec3 mUp;
    vec3 mRight;
    
    mat4 mMatrix;
};
