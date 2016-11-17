#include "ShaderProgram.hpp"

namespace OME {


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
    
    checkCompileErrors(vs, false);
    
    glCompileShader(fs);
    
    checkCompileErrors(fs, false);
    
    
    mHandle = glCreateProgram();
    
    glAttachShader(mHandle, vs);
    glAttachShader(mHandle, fs);
    glLinkProgram(mHandle);
    
    checkCompileErrors(mHandle, true);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    mUniformLocations.clear();
    
    return true;
}


void ShaderProgram::use(){
    if(mHandle){
        glUseProgram(mHandle);
    }
}


#pragma mark Helpers
void ShaderProgram::checkCompileErrors(GLuint object, bool program){
    int status = 0;
    if(program){
        glGetProgramiv(object, GL_LINK_STATUS, &status);
        if(status == GL_FALSE){
            GLint length = 0;
            glGetProgramiv(object, GL_INFO_LOG_LENGTH, &length);
            string errorLog(length, ' ');
            glGetProgramInfoLog(object, length, &length, &errorLog[0]);
            OME::Utils::LOG("Error! Program failed to link. {0}\n", errorLog.c_str());
        }
    }else{ // VERTEX or FRAGMENT
        glGetShaderiv(object, GL_COMPILE_STATUS, &status);
        if(status == GL_FALSE){
            GLint length = 0;
            glGetShaderiv(object, GL_INFO_LOG_LENGTH, &length);
            string errorLog(length, ' ');
            glGetShaderInfoLog(object, length, &length, &errorLog[0]);
            OME::Utils::LOG("Error! Shader failed to compile. {0}\n", errorLog.c_str());
        }
    
    }
}

GLint ShaderProgram::getUniformLocation(string name){
    if(mUniformLocations.find(name) == mUniformLocations.end()){
        mUniformLocations[name] = glGetUniformLocation(mHandle, name.c_str());
    }
    return mUniformLocations[name];
}
}
