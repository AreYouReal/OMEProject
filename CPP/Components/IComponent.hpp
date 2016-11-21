#pragma once

#include <string>

namespace OME {
    
    class GameObject;
    
    struct IComponent{
        
        GameObject *go;
        
        IComponent(){};
        virtual ~IComponent(){};

        std::string type(){
            return typeid(this).name();
        }
        
        virtual bool init(){return true;};
        virtual void update(){};
        virtual void draw(){};
        virtual void destroy(){};
        
    };
    
}


