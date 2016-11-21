#pragma once

#include <string>

#include "Utils.hpp"

namespace OME {
    
    class GameObject;
    
    struct IComponent{
        
        GameObject *go;
        
        IComponent(){};
        virtual ~IComponent(){};

        virtual std::string type() = 0;
        
        virtual bool init(){return true;};
        virtual void update(){};
        virtual void draw(){};
        virtual void destroy(){};
        
    };
    
}


