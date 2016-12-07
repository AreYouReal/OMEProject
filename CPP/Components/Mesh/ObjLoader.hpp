#pragma once

#include "Shortcuts.hpp"

#include "IComponent.hpp"

#include "WFObj.hpp"

#include "ShaderProgram.hpp"




namespace OME {

    
    class ObjLoader : public IComponent{
    public:
        ObjLoader();
        virtual ~ObjLoader();

        virtual string type() override{
            return typeid(ObjLoader).name();
        }
    
        virtual bool init() override;
        virtual void draw() override;
        
        void switchModel();
        
    private:
        
        ShaderProgram gouraud;
        ShaderProgram phong;
        
        ShaderProgram program;
        
        int modelNum = 0;
        
        void loadMesh();
        
        OBJMesh wfObj;
        
        Mesh* objMeshModel;
        
        int indexCount;
        
        unsigned int vertexBuffer;
        unsigned int vao;
        
    };
}
