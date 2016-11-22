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
        
        virtual string type() override{
            return typeid(Primitives).name();
        }
        
        
                unsigned int primitive;
    private:

        char mvp;
        char aPosition;
        char aColor;
        
        void renderPrimitive();
        
        
        ShaderProgram program;
        
    };
}


