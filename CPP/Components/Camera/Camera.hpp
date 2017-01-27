#pragma once

#include <stack>

#include "IComponent.hpp"
#include "SingletonComponent.hpp"

#include "../Transform/Transform.hpp"


#include "glm.hpp"



using vec2 = glm::vec2;
using mat4 = glm::mat4;
using mat3 = glm::mat3;
using vec3 = glm::vec3;

namespace OME {
    class Camera : public IComponent, public SingletonComponent<Camera>{
    public:
        
        Camera();
        virtual ~Camera();
        
        virtual string type() override{
            return typeid(Camera).name();
        }
        
        virtual bool init()     override;
        virtual void update()   override;
        virtual void draw()     override;
        virtual void destroy()  override;
        
        void camInit(float width, float height, float fov, float near, float far );
        
        const mat4& getViewMatrix() const;
        const mat4& getProjectionMatrix() const;
        const mat3& getNormalMatrix();

        void setWindthAndHeight(const int, const int);

        
        void onTouch(const int count, const int id, const int event, const int x, const int y);
        
        void pushMatrix(const mat4 modelMatrix);
        void popMatrix();
        
    private:
        
        float mWidth;
        float mHeight;
        float mFOV; // in degrees
        float mNearPlane;
        float mFarPlane;
        
        
        mat4 mViewMatrix;
        mat4 mProjectinoMatrix;
        mat3 mNormalMatrix;
        
        std::stack<mat4> mMStack;
        
        Transform *transform;
        
        
        // TOUCH RELATED
        std::vector<vec2> mPrevTouch{vec2(0.0f), vec2(0.0f)};
        std::vector<vec2> mCurrentTouch{vec2(0.0f), vec2(0.0f)};
        std::vector<vec2> mDeltaTouch{vec2(0.0f), vec2(0.0f)};
        float mTouchSensetivity = 0.01;
        
    };
}
