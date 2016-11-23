#pragma once

#include "Mesh.hpp"
#include "ShaderProgram.hpp"

namespace OME {
    class Cube : public Mesh{
    public:
        Cube();
        virtual ~Cube();
        
        virtual bool init() override;
        virtual void update() override;
        virtual void draw() override;
        
        virtual string type() override{
            return typeid(Cube).name();
        }

    private:
        
        ShaderProgram program;
        
        unsigned int vertexColorBuffer;
        unsigned int indexBuffer;
        
    };
}
