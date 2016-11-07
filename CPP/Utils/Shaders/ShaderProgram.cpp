#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() : mHandle(0){}


ShaderProgram::~ShaderProgram(){
    glDeleteProgram(mHandle);
}


bool ShaderProgram::loadShaders( string vertFileName, string fragFilename ){
    up<Cache> vertContent = OME::Utils::loadFile(vertFileName, true);
    up<Cache> fragContent = OME::Utils::loadFile(fragFilename, true);
    
    
    
    
    OME::Utils::LOG("Vertex shader content: %s", vertContent->content);
    
    
    OME::Utils::LOG("Vertex shader size: %d", vertContent->size);
    
    if(!vertContent || !fragContent){
        return false;
    }
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    
    char* vertexString = (char*)vertContent->content;
    char* fragmentString = (char*)fragContent->content;
    
    glShaderSource(vs, 1, &vertexString, NULL);
    glShaderSource(fs, 1, &fragmentString, NULL);
    
    glCompileShader(vs);
    
    OME::Utils::LOG_GL_ERROR();
    
    glCompileShader(fs);
    
    OME::Utils::LOG_GL_ERROR();
    
    
    mHandle = glCreateProgram();
    
    glAttachShader(mHandle, vs);
    glAttachShader(mHandle, fs);
    glLinkProgram(mHandle);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    mUniformLocations.clear();
    
    
    OME::Utils::LOG("Create shader program!!!");
    
    return true;
}


