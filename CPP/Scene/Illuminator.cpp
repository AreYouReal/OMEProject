#include "Illuminator.hpp"



namespace OME {
    
    void Illuminator::addLight(OME::Light *lightComp){
        if(lightComp){
            Utils::LOG("ADD LIGHT! %d", lightComp);
            mLights.push_back(lightComp);
        }
    }
    
    
    void Illuminator::removeLight(OME::Light *lightComp){
        for(int i = 0; i < mLights.size(); ++i){
            if(mLights[i] == lightComp){
                mLights.erase(mLights.begin() + i);
                Utils::LOG("REMOVE LIGHT! %d", lightComp);
            }
        }
    
    }

    
    Light* Illuminator::getLight(int pos){
        if(pos < 0 || pos >= mLights.size())
            return nullptr;
        
        return mLights[pos];
    }
    
}
