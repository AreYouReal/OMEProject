#pragma once

#include "Mesh.hpp"

#include "ShaderProgram.hpp"

namespace OME {
    class Grid : public Mesh{
        public:
        
        virtual bool init() override;
        
        virtual void update() override;
        virtual void draw() override;
      
        virtual string type() override{
            return typeid(Grid).name();
        }
        
        private:
        
        void createGrid(float, float, int, int);

        unsigned int vertexBuffer;
        unsigned int indexBuffer;
        
        unsigned int vao;
        
        ShaderProgram program;
        
        
        int xDimension = 100, zDimension = 100;
        int xDivision = 10, zDivision = 10;
        
        
    };
}

