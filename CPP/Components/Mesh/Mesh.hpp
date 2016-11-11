#pragma once

#include "IComponent.hpp"

class Mesh : public IComponent{
public:
    Mesh(GameObject *const gameObject);
    virtual ~Mesh();
    
    virtual bool init()     override;
    virtual void update()   override;
    virtual void draw()     override;
    virtual void destroy()  override;
    
};
