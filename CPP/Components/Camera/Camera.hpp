#pragma once

#include "IComponent.hpp"

namespace OME {
    class Camera : public IComponent{
    public:
        Camera(GameObject *const gameObject);
        virtual ~Camera();
        
    private:
        
        
        
    };
}
