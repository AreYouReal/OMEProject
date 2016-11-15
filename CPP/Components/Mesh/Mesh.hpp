#pragma once

#include "IComponent.hpp"

class Mesh : public IComponent{
public:
    Mesh(GameObject *const gameObject);
    virtual ~Mesh();    
};
