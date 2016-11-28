#pragma once

#include "MeshRenderer.hpp"

#include "ShaderProgram.hpp"

#include <string>
#include "Utils.hpp"

#include "lib3ds.h"


struct lib3dsUserData{
    GLint vbo = 0, ibo = 0;
    GLuint vao = 0;
    int vertexSize = 0, normalOffset = 0, indexNum = 0;
    unsigned int strip = 0;
    long landmarkID = 0;
    GLuint textureId;
};

namespace OME {
    class Loader3DS : public MeshRenderer{
    public:
        
        virtual string type() override{
            return typeid(Loader3DS).name();
        }
        
        virtual bool init() override;
        virtual void draw() override;
        
        virtual void destroy() override;
        
        
        
    private:
        ShaderProgram program;
        
        Lib3dsFile *file;
        unsigned char renderPrimitive;

        Lib3dsFile* load3dsModel(string filename);
        
        void buildMesh(Lib3dsMesh* mesh);
        
        void renderNodes(Lib3dsFile* file, Lib3dsNode* node);
        
        bool clear(Lib3dsFile* file);
        
        
    };
}
