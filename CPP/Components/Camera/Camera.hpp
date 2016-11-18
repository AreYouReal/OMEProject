#pragma once

#include "IComponent.hpp"
#include "../Transform/Transform.hpp"

#include "glm.hpp"

using mat4 = glm::mat4;
using vec3 = glm::vec3;

namespace OME {
    class Camera : public IComponent{
    public:
        Camera(GameObject *const gameObject);
        virtual ~Camera();
        
        
        virtual bool init()     override;
        virtual void update()   override;
        virtual void draw()     override;
        virtual void destroy()  override;
        
        void camInit(/*parameters*/);
        
        const float width();
        const float height();
        
        
        
        const mat4& getViewMatrix() const;
        const mat4& getProjectionMatrix() const;
        const mat4& getNormalMatrix() const;
        
        
        virtual void setPosition(const vec3& position){}
        virtual void rotate(float yaw, float pitch){}
        virtual void move(const vec3& offsetPos){}
        
    private:
        
        Transform *transform;
        
    };
}
