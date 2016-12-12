#include "Light.hpp"

#include "Illuminator.hpp"

namespace OME {
    
    Light::Light(LightType type) : mType(type), mAmbient(1.0f), mDiffuse(1.0f), mSpecular(1.0f){
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
    
    const Light::LightType Light::lightType() const{
        return mType;
    }

}
