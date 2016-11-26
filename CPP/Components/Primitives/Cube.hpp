#pragma once

#include "MeshRenderer.hpp"
#include "ShaderProgram.hpp"

namespace OME {
    class Cube : public MeshRenderer{
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

        unsigned int UBO;
        
        void uniformBufferObject();
        
    };
}
