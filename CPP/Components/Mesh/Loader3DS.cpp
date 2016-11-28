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
    
}
