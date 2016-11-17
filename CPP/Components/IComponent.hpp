#pragma once

namespace OME {
    
    class GameObject;
    
    
    
    struct IComponent{
        enum Type{ CAMERA };
        
        Type mType;
        GameObject *go;
        
        IComponent(GameObject * const gameObject) : go(gameObject){};
        virtual ~IComponent(){};
        virtual bool init(){return true;};
        virtual void update(){};
        virtual void draw(){};
        virtual void destroy(){};
        
    };
    
}


