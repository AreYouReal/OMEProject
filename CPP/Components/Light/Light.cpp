#include "Light.hpp"

#include "Illuminator.hpp"

namespace OME {
    
    Light::Light(LightType type) : mType(type){
        Illuminator::instance()->addLight(this);
    }

    Light::~Light(){ }
    
    bool Light::init(){
        return true;
    }
    
    void Light::update(){ }
    
    void Light::destroy(){
        Illuminator::instance()->removeLight(this);
    }
    
    Light::LightType Light::lightType(){
        return mType;
    }

}
