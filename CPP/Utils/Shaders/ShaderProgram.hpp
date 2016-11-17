#pragma once

#include "Utils.hpp"

namespace OME {
    class ShaderProgram{
    public:
        ShaderProgram();
        ~ShaderProgram();
        
        bool loadShaders( string vertFileName, string fragFilename );
        void use();
        
        
        // Set uniforms goes here...
        
    private:
        
        void checkCompileErrors(GLuint object, bool program);
        GLint getUniformLocation(string name);
        
        GLuint mHandle;
        
        map<string, GLint> mUniformLocations;
    };
}


