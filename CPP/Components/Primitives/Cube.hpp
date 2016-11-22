#pragma once

#include "Mesh.hpp"

namespace OME {
    class Cube : public Mesh{
    public:
        Cube();
        virtual ~Cube();
        
        virtual bool init() override;
        virtual void draw() override;
        
        virtual string type() override{
            return typeid(Cube).name();
        }
        
    };
}
