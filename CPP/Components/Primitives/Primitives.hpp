#pragma once

#include "Mesh.hpp"

class Primitives : public Mesh{
public:
    Primitives(GameObject *const gameObject);
    virtual ~Primitives();
    
    
    
private:
    unsigned int primitive;
    char mvp;
    char aPosition;
    char aColor;
    

};
