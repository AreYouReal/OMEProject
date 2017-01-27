#include "GameObject.hpp"
#include "Camera.hpp"

#include "../../3dPart/glm/gtx/transform.hpp"

#include "matrix_inverse.hpp"

#include "OMConstants.h"

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using mat3 = glm::mat3;
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
    
    const mat3& Camera::getNormalMatrix(){
        mat4 modelM(1.0f);
        if(!mMStack.empty()){
            modelM = mMStack.top();
        }
        mNormalMatrix = glm::inverseTranspose(mat3( mViewMatrix * modelM));
        return mNormalMatrix;
    }
    
    void Camera::setWindthAndHeight(const int width, const int height){
        mWidth = width;
        mHeight = height;
    }
    
    void Camera::onTouch(const int count, const int id, const int event, const int x, const int y){
        TOUCH_EVENT touchEvent = (TOUCH_EVENT)event;
        
        if(id >= mPrevTouch.size()) return;
        
            switch (touchEvent) {
                case TOUCH_EVENT::DOWN :
                    mCurrentTouch[id].x = x;
                    mCurrentTouch[id].y = y;
                    mPrevTouch[id].x = x;
                    mPrevTouch[id].y = y;
                    break;
                case TOUCH_EVENT::MOVED :
                    mCurrentTouch[id].x = x;
                    mCurrentTouch[id].y = y;
                    mDeltaTouch[id].x = (x - mPrevTouch[id].x) * mTouchSensetivity;
                    mDeltaTouch[id].y = (y - mPrevTouch[id].y) * mTouchSensetivity;
                    mPrevTouch[id].x = x;
                    mPrevTouch[id].y = y;
                    break;
                case TOUCH_EVENT::UP :
                    mCurrentTouch[id] = mPrevTouch[id] = mDeltaTouch[id] = vec2(0.0f);
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
        
        
        if(mDeltaTouch[0].x != 0.0f){
            transform->rotate(vec3(0.0f, mDeltaTouch[0].x, 0.0f));
        }
        
        if(mDeltaTouch[0].y != 0.0f){
            transform->rotate(vec3(mDeltaTouch[0].y, 0.0f, 0.0f));
        }
        
        if(mCurrentTouch[1].x != 0.0f && mPrevTouch[1].x != 0.0f){
            vec3 offset = vec3((mCurrentTouch[0] - mCurrentTouch[1]) - (mPrevTouch[0] - mPrevTouch[1]), 0.0f);
            Utils::LOG("Offset: { %f, %f, %f}", offset.x, offset.y, offset.z);
            transform->translate(offset);
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
    
    
    void Camera::pushMatrix(const mat4 modelMatrix){
        if(mMStack.empty()){
            mMStack.push(modelMatrix);
        }else{
            mMStack.push(mMStack.top() * modelMatrix);
        }
    }
    
    void Camera::popMatrix(){
        mMStack.pop();
    }


}


