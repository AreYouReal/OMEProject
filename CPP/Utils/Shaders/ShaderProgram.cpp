#include "ShaderProgram.hpp"

#include "../../3dPart/glm/gtc/type_ptr.hpp"

namespace OME {

const int ShaderProgram::VERTEX_ATTRIB_LOCATION         = 0;
const int ShaderProgram::NORMAL_ATTRIB_LOCATION         = 1;
const int ShaderProgram::TEXCOORD_ATTRIB_LOCATION       = 2;

ShaderProgram::ShaderProgram() : id(0){}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(id);
}

bool ShaderProgram::loadShaders( string vertFileName, string fragFilename ){
    up<Cache> vertContent = OME::Utils::loadFile(vertFileName, true);
    up<Cache> fragContent = OME::Utils::loadFile(fragFilename, true);

//    OME::Utils::LOG("Vertex shader content: %s\n", vertContent->content);
//    OME::Utils::LOG("Vertex shader size: %d\n", vertContent->size);
//    
//    
//    OME::Utils::LOG("Fragment shader content: %s\n", fragContent->content);
//    OME::Utils::LOG("Fragment shader size: %d\n", fragContent->size);
    
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
    
    
    id = glCreateProgram();
    
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    
    checkCompileErrors(id, true);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    mUniformLocations.clear();
    
    return true;
}


void ShaderProgram::use(){
    if(id){
        glUseProgram(id);
    }
}
    
void ShaderProgram::setUniform(string name, mat4 mat){
    int uniformLoc = getUniformLocation(name);
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat));
}
    
void ShaderProgram::setUniform(string name, mat3 mat){
    int uniformLoc = getUniformLocation(name);
    glUniformMatrix3fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat));
}
    
void ShaderProgram::setUniform(string name, vec3 v3){
    int uniformLoc = getUniformLocation(name);
    glUniform3fv(uniformLoc, 1, glm::value_ptr(v3));
}
    
void ShaderProgram::setUniform(string name, vec4 v4){
    int uniformLoc = getUniformLocation(name);
    glUniform4fv(uniformLoc, 1, glm::value_ptr(v4));
}
    
void ShaderProgram::setUniform(string name, float val){
    int uniformLoc = getUniformLocation(name);
    glUniform1f(uniformLoc, val);
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
            OME::Utils::LOG("Error! Program failed to link. %s\n", errorLog.c_str());
        }
    }else{ // VERTEX or FRAGMENT
        glGetShaderiv(object, GL_COMPILE_STATUS, &status);
        if(status == GL_FALSE){
            GLint length = 0;
            glGetShaderiv(object, GL_INFO_LOG_LENGTH, &length);
            string errorLog(length, ' ');
            glGetShaderInfoLog(object, length, &length, &errorLog[0]);
            OME::Utils::LOG("Error! Shader failed to compile. %s\n", errorLog.c_str());
        }
    
    }
}

GLint ShaderProgram::getUniformLocation(string name){
    if(mUniformLocations.find(name) == mUniformLocations.end()){
        mUniformLocations[name] = glGetUniformLocation(id, name.c_str());
    }
    return mUniformLocations[name];
}
}
