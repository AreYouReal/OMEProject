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
        
        
        static const int VERTEX_ATTRIB_LOCATION;
        static const int NORMAL_ATTRIB_LOCATION;
        static const int TEXCOORD_ATTRIB_LOCATION;
        
        GLuint id;
        
    private:
        
        void checkCompileErrors(GLuint object, bool program);
        GLint getUniformLocation(string name);
        

        
        map<string, GLint> mUniformLocations;
    };
}


