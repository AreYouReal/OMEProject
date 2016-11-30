#pragma once

#include "Singleton.hpp"

#include "Light.hpp"

namespace OME {
    class Illuminator : public Singleton<Illuminator>{
    public:
        
        void addLight(Light* lightComp);
        void removeLight(Light* lightComp);
        
    private:
        
        std::vector<Light*> mLights;
        
    };
}
