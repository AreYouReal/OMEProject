#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() : mHandle(0){}


ShaderProgram::~ShaderProgram(){
    glDeleteProgram(mHandle);
}


bool ShaderProgram::loadShaders( string vertFileName, string fragFilename ){
    up<FileContent> vertContent = OME::Utils::readTextFile(vertFileName);
    
    if(!vertContent){
        OME::Utils::LOG("Failed to load shader! [%s]", vertFileName.c_str());
        return false;
    }
    
    OME::Utils::LOG("Loaded vertex fragment file!");
    
//    omFile *vertexFile = OME::Utils::fileOpen(OME::Game::currentCtx , vertFileName);
    
    
    
    return true;
}


