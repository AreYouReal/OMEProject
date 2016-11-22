#include "GameObject.hpp"
#include "Camera.hpp"

#include "../../3dPart/glm/gtx/transform.hpp"

using vec3 = glm::vec3;
using mat4 = glm::mat4;

namespace OME {
    
    Camera::Camera(){
        OME::Utils::LOG("Camera constructor\n");
    }
    
    Camera::~Camera(){
        OME::Utils::LOG("Camera destructor\n");
    }
    
    void Camera::camInit(float width, float height, float fov, float near, float far){
        mWidth      = width;
        mHeight     = height;
        mFOV        = fov;
        mNearPlane  = near;
        mFarPlane   = far;
        OME::Utils::LOG("Camera init done.\n");
    }
    
    mat4 Camera::getViewMatrix(){
        vec3 target = transform->mFront + transform->mPosition;
        return glm::lookAt(transform->mPosition, target, transform->mUp);
    }

    mat4 Camera::getProjectionMatrix(){
        return glm::perspective(mFOV, mWidth/mHeight, mNearPlane, mFarPlane);
    }
    
    void Camera::setWindthAndHeight(const int width, const int height){
        mWidth = width;
        mHeight = height;
    }
    
    
#pragma mark IComponent Interface
    bool Camera::init(){
        transform = static_cast<Transform*>(go->getComponent(typeid(Transform).name()));
        if(transform == nullptr){
            OME::Utils::LOG("Camera initialization failed!\n");
            return false;
        }else{
            return true;
        }
        return true;
    }
    
    void Camera::update(){
    
    }
    
    void Camera::draw(){
    
    }
    
    void Camera::destroy(){
        
    }


}


