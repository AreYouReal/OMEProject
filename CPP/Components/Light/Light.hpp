#pragma once


#include "IComponent.hpp"

#include <string>

using string = std::string;

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
        
        LightType lightType();
        
    private:
        
        LightType mType;
        
    };
}
