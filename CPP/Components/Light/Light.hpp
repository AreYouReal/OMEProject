#pragma once


#include "IComponent.hpp"

#include <string>

using string = std::string;
using vec3 = glm::vec3;

namespace OME {
    class Light : public IComponent{
    public:
        
        enum LightType{ POINT, DIRECTION, SPOT };
        
        Light(LightType type = LightType::POINT );
        virtual ~Light();
        
        virtual string type() override{
            return typeid(Light).name();
        }
        
        virtual bool init() override;
        virtual void update() override;
        virtual void destroy() override;
        
        const LightType lightType() const;
        const vec3  ambient() const { return mAmbient; }
        const vec3  diffuse() const {return mDiffuse; }
        const vec3  specular() const {return mSpecular; }
        
    private:
        
        LightType mType;
        
        vec3    mAmbient;
        vec3    mDiffuse;
        vec3    mSpecular;
        
    };
}
