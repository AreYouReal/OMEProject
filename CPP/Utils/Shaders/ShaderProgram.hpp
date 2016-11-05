#pragma once

#include "Utils.hpp"

class ShaderProgram{
public:
    ShaderProgram();
    ~ShaderProgram();
    
    enum ShaderType{ VERTEX, FRAGMENT, PROGRAM };

    bool loadShaders( string vertFileName, string fragFilename );
    void use();
    
    
    // Set uniforms goes here...
    
private:
    string fileToString(const string filename);
    void checkCompileErrors(GLuint shader, ShaderType type);
    GLint getUniformLocation(string name);
    
    GLuint mHandle;
    
    map<string, GLint> mUniformLocations;
};
