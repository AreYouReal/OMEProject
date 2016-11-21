#pragma once

#include "Mesh.hpp"
#include "ShaderProgram.hpp"

namespace OME {
    class Primitives : public Mesh{
    public:
        Primitives();
        virtual ~Primitives();
        
        virtual bool init() override;
        virtual void draw() override;
        
    private:
        unsigned int primitive;
        char mvp;
        char aPosition;
        char aColor;
        
        void renderPrimitive();
        
        
        ShaderProgram program;
        
    };
}


