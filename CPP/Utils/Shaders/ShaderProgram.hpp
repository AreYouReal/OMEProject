#pragma once

#include "Utils.hpp"

#include "glm.hpp"

using vec3 = glm::vec3;
using mat4 = glm::mat4;

namespace OME {
    class ShaderProgram{
    public:
        ShaderProgram();
        ~ShaderProgram();
        
        bool loadShaders( string vertFileName, string fragFilename );
        void use();
        
        
        // Set uniforms goes here...
        
        void setUniform(string name, mat4 mat);
        
    private:
        
        void checkCompileErrors(GLuint object, bool program);
        GLint getUniformLocation(string name);
        
        GLuint mHandle;
        
        map<string, GLint> mUniformLocations;
    };
}


