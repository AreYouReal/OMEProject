#include "WFObj.hpp"

using vec3 = glm::vec3;

namespace OME {
    
    bool OBJMesh::calculateNormal(bool flatShading){
        if(objMeshModel.normals.size() == 0){
            objMeshModel.normals.resize(objMeshModel.positions.size());
            int index0, index1, index2;
            vec3 a, b, c;
            for(int i = 0; i < objMeshModel.indices.size(); i+=3){
                index0 = objMeshModel.indices[i];
                index1 = objMeshModel.indices[i + 1];
                index2 = objMeshModel.indices[i + 2];
            
                a = objMeshModel.positions[index0];
                b = objMeshModel.positions[index1];
                c = objMeshModel.positions[index2];
                
                vec3 faceNormal = glm::cross((b - a), (c - a));
                
                if(flatShading){
                    objMeshModel.vertices[i].normal += faceNormal;
                    objMeshModel.vertices[i + 1].normal += faceNormal;
                    objMeshModel.vertices[i + 2].normal += faceNormal;
                }else{
                    objMeshModel.normals[index0] += faceNormal;
                    objMeshModel.normals[index1] += faceNormal;
                    objMeshModel.normals[index2] += faceNormal;
                }
            }
            
            if(!flatShading){
                for(int i = 0; i < objMeshModel.faces.size(); ++i){
                    int index = objMeshModel.faces[i].vertexIndex;
                    objMeshModel.vertices[i].normal = objMeshModel.normals[index];
                }
                
                for(int i = 0; i < objMeshModel.vertices.size(); ++i){
                    objMeshModel.vertices[i].normal = glm::normalize(objMeshModel.vertices[i].normal);
                }
            }
            return true;
        }else{
            Utils::LOG("Normals already exist!");
            return false;
        }

    }
    
    // Mathematics for 3D Game Programming and Computer Graphics, 3rd edition
    bool OBJMesh::calculateTangents(){
        list<vec3> tan1Accum;
        list<vec3> tan2Accum;
        
        objMeshModel.tangents.resize(objMeshModel.positions.size());
        
        for( unsigned int i = 0; i < objMeshModel.positions.size(); ++i){
            tan1Accum.push_back(vec3(0.0f));
            tan2Accum.push_back(vec3(0.0f));
            objMeshModel.tangents.push_back(vec4(0.0f));
        }
        
        int index0, index1, index2;
        int index0uv, index1uv, index2uv;
        
        for(unsigned int i = 0; i < objMeshModel.faces.size(); i += 3){
            index0 = objMeshModel.faces[i].vertexIndex;
            index1 = objMeshModel.faces[i + 1].vertexIndex;
            index2 = objMeshModel.faces[i + 2].vertexIndex;
            
            const vec3 &p0 = objMeshModel.positions[index0];
            const vec3 &p1 = objMeshModel.positions[index1];
            const vec3 &p2 = objMeshModel.positions[index2];
            
            index0uv = objMeshModel.faces[i].uvIndex;
            index1uv = objMeshModel.faces[i + 1].uvIndex;
            index2uv = objMeshModel.faces[i + 2].uvIndex;
            
            const vec2 &tc0 = objMeshModel.uvs[index0uv];
            const vec2 &tc1 = objMeshModel.uvs[index1uv];
            const vec2 &tc2 = objMeshModel.uvs[index2uv];
        
            // Equation 1:
            // Q1 = P1 − P0
            // Q2 = P2 − P0
            
            vec3 q1 = p1 - p0;
            vec3 q2 = p2 - p0;

            
            // Equation 2:
            // (s1, t1) = (u1 − u0, v1 − v0)
            // (s2, t2) = (u2 − u0, v2 − v0)
            
            float s1 = tc1.x - tc0.x, s2 = tc2.x - tc0.x;
            float t1 = tc1.y - tc0.y, t2 = tc2.y - tc0.y;
            
            // Equation 3:
            // Q1 = s1T + t1B
            // Q2 = s2T + t2B
            
            

            // Equation 4:
            // [ (Q1)x   (Q1)y  (Q1)z ]       [(s1,  t1)] [(Tx   Ty  Tz)]
            //                            =
            // [ (Q2)x   (Q2)y  (Q2)z ]       [(s2,  t2)] [(Bx   By  Bz)]
            
            // Equation 5:
            // [(Tx   Ty  Tz)]      [      1       ]  [(s1,  -t1)] [ (Q1)x   (Q1)y  (Q1)z ]
            //                  =   ----------------
            // [(Bx   By  Bz)]      [(-s1t2 - s2t1)]  [(-s2,  t2)] [ (Q2)x   (Q2)y  (Q2)z ]

            float r = 1.0f / (s1 * t2 - s2 * t1);

            vec3 tan1((s1 * q1.x - t1 * q2.x) * r,
                      (s1 * q1.y - t1 * q2.y) * r,
                      (s1 * q1.z - t1 * q2.z) * r ); // Tangent
            
            vec3 tan2((t2 * q2.x - s2 * q1.x) * r,
                      (t2 * q2.y - s2 * q1.y) * r,
                      (t2 * q2.z - s2 * q1.z) * r ); // BiTangent
            
            tan1Accum[index0] += tan1;
            tan1Accum[index1] += tan1;
            tan1Accum[index2] += tan1;
            
            tan2Accum[index0] += tan2;
            tan2Accum[index1] += tan2;
            tan2Accum[index2] += tan2;
            
        }
        
        for(unsigned int i = 0; i < objMeshModel.positions.size(); ++i){
            objMeshModel.tangents[i] = vec4(glm::normalize(tan1Accum[i]), 1.0);
            // It is advise to store the BiTangents into an array also instead of calclating at fly time in vertex shader.
//            Utils::LOG("\nT: %f, %f, %f", objMeshModel.tangents[i].x, objMeshModel.tangents[i].y, objMeshModel.tangents[i].z);
        }
        
        for(int i = 0; i < objMeshModel.faces.size(); ++i){
            int index = objMeshModel.faces[i].vertexIndex;
            objMeshModel.vertices[i].tangent = objMeshModel.tangents[index];
//            Utils::LOG("\nP: %f, %f, %f", objMeshModel.vertices[i].tangent.x, objMeshModel.vertices[i].tangent.y, objMeshModel.vertices[i].tangent.z);
        }
        
        tan1Accum.clear();
        tan2Accum.clear();
        
        return true;
    
    }
    
    
    bool OBJMesh::createInterleavedArray(){
        int faceIdxSize = (int)objMeshModel.faces.size();
        objMeshModel.vertices.resize(faceIdxSize);
        objMeshModel.indices.resize(faceIdxSize);
        
        indexCount = (int)objMeshModel.indices.size();
        
        for(int i = 0; i < faceIdxSize; ++i){
            int index = objMeshModel.faces[i].vertexIndex;
            objMeshModel.vertices[i].position = objMeshModel.positions[index];
            objMeshModel.indices[i] = (GLushort)objMeshModel.faces[i].vertexIndex;
            
            if(objMeshModel.uvs.size()){
                index = objMeshModel.faces[i].uvIndex;
                objMeshModel.vertices[i].uv = objMeshModel.uvs[index];
            }
            
            if(objMeshModel.normals.size()){
                index = objMeshModel.faces[i].normalIndex;
                objMeshModel.vertices[i].normal = objMeshModel.normals[index];
            }
        }
        
        if(faceIdxSize){
            return true;
        }else{
            return false;
        }
    
    }
    
    bool OBJMesh::scanVertexUVAndNormal(FILE *pFile, char c){
        float x, y, z, u, v;
        switch (c) {
            case ' ':
                fscanf(pFile, "%f %f %f\n", &x, &y, &z);
                objMeshModel.positions.push_back(vec3(x, y, z));
                break;
            case 'n':
                fscanf(pFile, "%f %f %f\n", &x, &y, &z);
                objMeshModel.normals.push_back(vec3(x, y, z));
                break;
            case 't':
                fscanf(pFile, "%f %f\n", &u, &v);
                objMeshModel.uvs.push_back(vec2(u, v));
                break;
            default:
                return false;
        }
        return true;
    }
    
    bool OBJMesh::scanFaceIndex(FILE *pFile, char c){
        int vIndex, uvIndex, nIndex;
        float scanCount;
        
        if(objMeshModel.normals.size() && objMeshModel.uvs.size()){
        // If Normal and UV information availble. Format => v/u/n
            while(fgetc(pFile) != '\n'){
                vIndex = uvIndex = nIndex = 0;
                
                scanCount = fscanf(pFile, "%d/%d/%d", &vIndex, &uvIndex, &nIndex);
                if((scanCount != 3) || (vIndex == 0) || (uvIndex == 0) || (nIndex == 0)){
                    break;
                }
                
                objMeshModel.faces.push_back(FaceIndex(vIndex - 1, uvIndex - 1, nIndex - 1));
            }
        }else if(objMeshModel.normals.size() && !objMeshModel.uvs.size()){
            // If Normal information avialbe and UV missing. Format => v//n
            while (fgetc(pFile) != '\n') {
                vIndex = nIndex = uvIndex = 0;
                scanCount = fscanf(pFile, "%d//%d/", &vIndex, &uvIndex);
                if((scanCount != 2) || (vIndex == 0) || (uvIndex == 0)){
                    break;
                }
                objMeshModel.faces.push_back(FaceIndex(vIndex - 1, uvIndex - 1, nIndex - 1));
            }
        }else if( !objMeshModel.normals.size() && objMeshModel.uvs.size()){
            // If Normal information missing and UV avialbe. Format => v/u/
            while(fgetc(pFile) != '\n'){
                vIndex = nIndex = uvIndex = 0;
                scanCount = fscanf(pFile, "%d/%d/", &vIndex, &uvIndex);
                if((scanCount != 2) || (vIndex == 0) || (uvIndex == 0)){
                    break;
                }
                
                objMeshModel.faces.push_back(FaceIndex(vIndex - 1, uvIndex - 1, nIndex - 1));
            }
        }else if(!objMeshModel.normals.size() && !objMeshModel.uvs.size()){
            // If both Normal and UV information missing. Format => v
            vIndex = uvIndex = nIndex = 0;
            while(fgetc(pFile) != '\n'){
                scanCount = fscanf(pFile, "%d", &vIndex);
                if((scanCount != 1) || (vIndex == 0)){
                    break;
                }
                objMeshModel.faces.push_back(FaceIndex(vIndex - 1, uvIndex - 1, nIndex - 1));
            }
        }
        return true;
    }
    
    bool OBJMesh::parseFileInfo(string path){
        FILE *pFile;
        bool eofReached = false;
        char c;
        
        pFile = fopen(path.c_str(), "r");
        if(pFile == nullptr){
            Utils::LOG("Fail to open OBJ mesh file: %s", path.c_str());
            fclose(pFile);
            return false;
        }
        
        objMeshModel.name = path;
        while(!eofReached){
            c = fgetc(pFile);
            switch (c) {
                case '#':
                case 'u':
                case 's':
                case 'g':
                    while(fgetc(pFile) != '\n');
                    break;
#ifdef __APPLE__
                case EOF:
#else
                case (unsigned char)EOF:
#endif
                    eofReached = true;
                    break;
                case 'v':
                    c = fgetc(pFile);
                    scanVertexUVAndNormal(pFile, c);
                    break;
                case 'f':
                    scanFaceIndex(pFile, c);
                    break;
            }
        }
        fclose(pFile);
        return true;
    }
    
    Mesh* OBJMesh::parseObjModel(string path, bool flatShading){
        if(!parseFileInfo(path)){
            return nullptr;
        }
        
        createInterleavedArray();
        calculateNormal(flatShading);
        
        if(objMeshModel.uvs.size()){
            calculateTangents();
        }
        clearMesh();
        
        return &objMeshModel;
    }
    
    bool OBJMesh::clearMesh(){
        objMeshModel.positions.clear();
        objMeshModel.normals.clear();
        objMeshModel.uvs.clear();
        objMeshModel.tangents.clear();
        objMeshModel.indices.clear();
        objMeshModel.faces.clear();
        return true;
    }
    
    
    
}
