#pragma once

#include <vector>
#include "Utils.hpp"

template <typename T>
using list = std::vector<T>;

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;


namespace OME {
    
    struct Vertex{
        vec3 position   {0.0f, 0.0f, 0.0f};
        vec2 uv         {0.0f, 0.0f};
        vec3 normal     {0.0f, 0.0f, 0.0f};
        vec4 tangent    {0.0f, 0.0f, 0.0f, 0.0f};
    };
    
    struct FaceIndex{
        short vertexIndex;
        short normalIndex;
        short uvIndex;
        
        FaceIndex(short v, short u, short n){
            vertexIndex = v;
            uvIndex     = u;
            normalIndex = n;
        }
    };
    
    struct Mesh{
        string              name{"OME_Name_not_set"};
        list<FaceIndex>     faces;
        list<Vertex>        vertices;
        list<vec3>          positions;
        list<vec2>          uvs;
        list<vec3>          normals;
        list<vec4>          tangents;
        list<unsigned short> indices;
    };
    
    class OBJMesh{
        Mesh objMeshModel;
        
        int indexCount;
    
    public:
        OBJMesh();
        ~OBJMesh();
        
        Mesh* parseObjModel(string path, bool flatShading = false);
        
        int indexTotal(){ return indexCount; }
    
    private:
        
        bool parseFileInfo(string path);
        bool scanVertexUVAndNormal(FILE *pFile, char c);
        bool scanFaceIndex(FILE *pFile, char c);
        bool calculateNormal(bool flatShading);
        bool calculateTangents();
        bool createInterleavedArray();
        bool clearMesh();
        
    };
    
}

