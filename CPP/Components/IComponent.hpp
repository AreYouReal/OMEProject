#pragma once

class GameObject;

struct IComponent{
    enum Type{ CAMERA };
    
    Type mType;
    GameObject *go;
    
    IComponent(GameObject * const gameObject) : go(gameObject){};
    virtual ~IComponent(){};
    virtual bool init()     = 0;
    virtual void update()   = 0;
    virtual void draw()     = 0;
    virtual void destroy()  = 0;
    
};
