#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() : mHandle(0){}


ShaderProgram::~ShaderProgram(){
    glDeleteProgram(mHandle);
}


bool ShaderProgram::loadShaders( string vertFileName, string fragFilename ){
    up<FileContent> vertContent = OME::Utils::readTextFile(vertFileName);
    up<FileContent> fragContent = OME::Utils::readTextFile(fragFilename);
    
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
    glCompileShader(fs);
    
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


