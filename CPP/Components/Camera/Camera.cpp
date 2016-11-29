#include "GameObject.hpp"
#include "Camera.hpp"

#include "../../3dPart/glm/gtx/transform.hpp"

#include "OMConstants.h"

using vec2 = glm::vec2;
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
    
    const mat4& Camera::getViewMatrix() const{
        return mViewMatrix;
    }

    const mat4& Camera::getProjectionMatrix() const{
        return mProjectinoMatrix;
    }
    
    void Camera::setWindthAndHeight(const int width, const int height){
        mWidth = width;
        mHeight = height;
    }
    
    void Camera::onTouch(const int x, const int y, const int event){
        TOUCH_EVENT touchEvent = (TOUCH_EVENT)event;
        switch (touchEvent) {
            case TOUCH_EVENT::DOWN :
                mPrevTouch.x = x;
                mPrevTouch.y = y;
                break;
            case TOUCH_EVENT::MOVED :
                mDeltaTouch.x = (x - mPrevTouch.x)/100;
                mDeltaTouch.y = (y - mPrevTouch.y) * mTouchSensetivity;
                mPrevTouch.x = x;
                mPrevTouch.y = y;
                
                Utils::LOG("Delta: [%f, %f]", mDeltaTouch.x, mDeltaTouch.y);
                break;
            case TOUCH_EVENT::UP :
                mPrevTouch = mDeltaTouch = vec2(0.0f);
                break;
                
            default:
                break;
        }
    
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
        
        if(mDeltaTouch.x != 0.0f){
            vec3 newRotation = transform->mRotation;
            newRotation.y += mDeltaTouch.x;
            transform->mRotation = newRotation;
            transform->mFront = vec3(cosf(newRotation.y), 0.0f, sinf(newRotation.y));
        }
        
        if(mDeltaTouch.y != 0.0f){
            transform->mPosition += (transform->mFront * mDeltaTouch.y);
        }
        
        
        vec3 target = transform->mFront + transform->mPosition;
        mViewMatrix = glm::lookAt(transform->mPosition, target, transform->mUp);
        
        mProjectinoMatrix = glm::perspective(mFOV, mWidth/mHeight, mNearPlane, mFarPlane);
    }
    
    void Camera::draw(){
        glViewport(0, 0, mWidth, mHeight);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
    }
    
    void Camera::destroy(){
        
    }


}


