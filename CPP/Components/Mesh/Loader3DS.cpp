#include "Loader3DS.hpp"

#ifdef __APPLE__
#define VERTEX_SHADER "3ds.vert"
#define FRAGMENT_SHADER "3ds.frag"
#else
#define VERTEX_SHADER "shaders/3ds.vert"
#define FRAGMENT_SHADER "shaders/3ds.frag"
#endif

namespace OME {
    
    bool Loader3DS::init(){
        program.loadShaders( VERTEX_SHADER, FRAGMENT_SHADER );
    
        string filename = Utils::extractPath(getenv("FILESYSTEM")) + "car.3DS";
        
        file = load3dsModel(filename);
        
        return true;
    }
    
    
    void Loader3DS::draw(){
    
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
        
        
        }
        
        
        
        
        
    }
    
}
