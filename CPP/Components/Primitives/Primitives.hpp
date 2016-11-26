#pragma once

#include "MeshRenderer.hpp"
#include "ShaderProgram.hpp"

namespace OME {
    class Primitives : public MeshRenderer{
    public:
        Primitives();
        virtual ~Primitives();
        
        virtual bool init() override;
        virtual void draw() override;
        
        virtual string type() override{
            return typeid(Primitives).name();
        }
        
        
        unsigned int primitive;
    
    private:
        
        void renderPrimitive();
        
        
        ShaderProgram program;
        
    };
}


