#include "Light.hpp"


namespace OME {
    
    Light::Light(LightType type) : mType(type){ }

    Light::~Light(){ }
    
    bool Light::init(){
        return true;
    }
    
    void Light::update(){ }
    
    Light::LightType Light::lightType(){
        return mType;
    }

}
