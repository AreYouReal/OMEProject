#pragma once

#include "IComponent.hpp"
#include "Singleton.h"

#include "../Transform/Transform.hpp"


#include "glm.hpp"

using mat4 = glm::mat4;
using vec3 = glm::vec3;

namespace OME {
    class Camera : public IComponent, public Singleton<Camera>{
    public:
        
        Camera();
        virtual ~Camera();
        
        
        virtual bool init()     override;
        virtual void update()   override;
        virtual void draw()     override;
        virtual void destroy()  override;
        
        void camInit(float width, float height, float fov, float near, float far );
        
        mat4 getViewMatrix();
        mat4 getProjectionMatrix();
        mat4 getNormalMatrix();       
        
        virtual void setPosition(const vec3& position){}
        virtual void rotate(float yaw, float pitch){}
        virtual void move(const vec3& offsetPos){}
        
    private:
        
        float mWidth;
        float mHeight;
        float mFOV; // in degrees
        float mNearPlane;
        float mFarPlane;
        
        
        Transform *transform;
        
    };
}
