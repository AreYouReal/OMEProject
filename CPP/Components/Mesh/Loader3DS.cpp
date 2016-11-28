#include "Loader3DS.hpp"

#ifdef __APPLE__
#define VERTEX_SHADER "3ds.vert"
#define FRAGMENT_SHADER "3ds.frag"
#else
#define VERTEX_SHADER "shaders/3ds.vert"
#define FRAGMENT_SHADER "shaders/3ds.frag"
#endif


#include "GameObject.hpp"
#include "Camera.hpp"

namespace OME {
    
    bool Loader3DS::init(){
        program.loadShaders( VERTEX_SHADER, FRAGMENT_SHADER );
    
        string filename = Utils::extractPath(getenv("FILESYSTEM")) + "car.3DS";
        
        file = load3dsModel(filename);
        

        
        return true;
    }
    
    
    void Loader3DS::draw(){
        Lib3dsNode *node;
        for(node = file->nodes; node != nullptr; node = node->next){
            renderNodes(file, node);
        }
    }
    
    void Loader3DS::destroy(){
        clear(file);
    }
    
    
    
    
#pragma mark Helpers
    
    Lib3dsFile* Loader3DS::load3dsModel(string filename){
        Lib3dsFile *file = lib3ds_file_open(filename.c_str());
        if(!file){
            Utils::LOG("ERROR! Failed to load file: %s", filename.c_str() );
            return nullptr;
        }
        
        if(!file->nodes){
            Lib3dsNode *node;
            for(int i = 0; i < file->nmeshes; ++i){
                Lib3dsMesh *mesh = file->meshes[i];
                node = lib3ds_node_new(LIB3DS_NODE_MESH_INSTANCE);
                strcpy(node->name, mesh->name);
                lib3ds_file_insert_node(file, node, nullptr);
            }
        }
        
        for(int i = 0; i < file->nmaterials; ++i){
            Lib3dsMaterial *mat = file->materials[i];
            Utils::LOG("3ds material: %s  -> %d\n", mat->name, mat->blur);
        }
        

        return file;
    }
    
    void Loader3DS::buildMesh(Lib3dsMesh *mesh){
        
        Utils::LOG("BUILD MESH: %s", mesh->name);
        
        int sizeMeshVert = 0;
        int sizeMeshTexture = 0;
        int sizeMeshNormal = 0;
        int sizeFaceIndex = 0;
        int indexNumber = 0;
        GLuint vId = 0;
        GLuint VAOid = 0;
        GLuint iId = 0;
        int idx = 0;
        float* meshVert = nullptr;
        float* meshTexture = nullptr;
        float *meshNormal = nullptr;
        unsigned short* faceIndex = nullptr;
        lib3dsUserData *userData = (lib3dsUserData*)mesh->user_ptr;

        
        meshVert = new float[mesh->nvertices * 3];
        for(int i = 0; i < mesh->nvertices; ++i){
            meshVert[idx++] = mesh->vertices[i][0];
            meshVert[idx++] = mesh->vertices[i][1];
            meshVert[idx++] = mesh->vertices[i][2];
        }
        
        idx = 0;
        meshTexture = new float[mesh->nvertices * 2];
        if(mesh->texcos != nullptr){
            for(int i = 0; i < mesh->nvertices; ++i){
                meshTexture[idx++] = mesh->texcos[i][0];
                meshTexture[idx++] = mesh->texcos[i][1];
            }
        }

        
        meshNormal = new float[mesh->nvertices * 3];
            // MESH NORMALS
        
        idx = 0;
        faceIndex = new unsigned short(mesh->nfaces * 3);
        for(int i = 0; i < mesh->nfaces; ++i){
            faceIndex[idx++] = mesh->faces[i].index[0];
            faceIndex[idx++] = mesh->faces[i].index[1];
            faceIndex[idx++] = mesh->faces[i].index[2];
        }
        
        int faceIndexNum = 0;
        faceIndexNum = mesh->nfaces * 3;
        userData->strip = 0;
        
        sizeMeshVert = sizeof(float) * mesh->nvertices * 3;
        sizeMeshTexture = sizeof(float) * mesh->nvertices * 2;
        sizeFaceIndex = sizeof(unsigned short) * faceIndexNum;
        sizeMeshNormal = sizeof(float) * mesh->nfaces * 3;
        indexNumber = faceIndexNum;
        
        

        
        // Create and Bind the VBO. Fill the VBO with Vertex position, texture, normal information.
        glGenBuffers( 1, (GLuint *)&vId );
        glBindBuffer( GL_ARRAY_BUFFER, vId );
        glBufferData( GL_ARRAY_BUFFER, sizeMeshVert + sizeMeshTexture, 0, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0,			sizeMeshVert,	meshVert );
        glBufferSubData( GL_ARRAY_BUFFER, sizeMeshVert, sizeMeshTexture, meshTexture );
        glBufferSubData( GL_ARRAY_BUFFER, sizeMeshVert + sizeMeshTexture, sizeMeshNormal, meshNormal );
        
        // Create and Bind the IBO. Fill the IBO with index information.
        glGenBuffers( 1, (GLuint *)&iId );
        glBindBuffer( GL_ARRAY_BUFFER, iId );
        glBufferData( GL_ARRAY_BUFFER, sizeFaceIndex, 0, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeFaceIndex, faceIndex );
        
        
        
        // Create and Bind Vertex Array Object
        glGenVertexArrays(1, &VAOid);
        glBindVertexArray(VAOid);
        glBindBuffer( GL_ARRAY_BUFFER, vId );
        
        
        // Cache the information in the User data structure
        userData->indexNum     = indexNumber;
        userData->vertexSize	  = sizeMeshVert;
        userData->normalOffset = sizeMeshVert + sizeMeshTexture;
        userData->vbo	  = vId;
        userData->ibo	  = iId;
        userData->vao		  = VAOid;
        userData->textureId    = 0;
        
        
        
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(int)userData->normalOffset );
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(int)userData->vertexSize );
        
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, iId );
        glBindVertexArray(0);
        
        Utils::LOG("VAO: %d", userData->vao);

        
        delete []faceIndex;
        delete []meshVert;
        delete []meshTexture;
        delete []meshNormal;
    }
    
    void Loader3DS::renderNodes(Lib3dsFile* file, Lib3dsNode* node){
        if(!file || !node) return;
        
        program.use();
        
        Lib3dsNode* tempNode;
        for(tempNode = node->childs; tempNode != nullptr; tempNode = tempNode->next){
            renderNodes(file, tempNode);
        }
        
        
        if( node -> type != LIB3DS_NODE_MESH_INSTANCE || strcmp(node->name, "$$$DUMMY") == 0){
            return;
        }
        
        int index;
        Lib3dsMesh *mesh;
        Lib3dsMeshInstanceNode *n = (Lib3dsMeshInstanceNode*)node;
        
        
        index = lib3ds_file_mesh_by_name(file, n->instance_name);
        if(index < 0){
            index = lib3ds_file_mesh_by_name(file, node->name);
        }
        if(index < 0){
            return;
        }
        
        mesh = file->meshes[index];

        if(!mesh->user_ptr){
            lib3dsUserData *userData = new lib3dsUserData();
            mesh->user_ptr = (void*)userData;
        }
        
        lib3dsUserData *userData = (lib3dsUserData*)mesh->user_ptr;
        
        if(!userData->vao){
            buildMesh(mesh);
        }else{
        
            glm::mat4 modelMatrix   = go->transform()->getMatrix();
            glm::mat4 viewMat       = Camera::instance()->getViewMatrix();
            glm::mat4 projMatrix    = Camera::instance()->getProjectionMatrix();
            
            program.setUniform("model",      modelMatrix);
            program.setUniform("view",       viewMat);
            program.setUniform("projection", projMatrix);
            
            glBindVertexArray(userData->vao);
            
            glDrawElements(GL_LINES, userData->indexNum, GL_UNSIGNED_SHORT, 0);
            
            glBindVertexArray(0);
        }
        glFlush();
    }
    
    
    bool Loader3DS::clear(Lib3dsFile *file){
        if(!file) return false;
        
        for(int i = 0; i < file->nmeshes; ++i){
            Lib3dsMesh *mesh = file->meshes[i];
            lib3ds_mesh_free(mesh);
        }
        
        
        Utils::LOG("3DS MODEL CLEAR!");
        return true;
    }
    
}
