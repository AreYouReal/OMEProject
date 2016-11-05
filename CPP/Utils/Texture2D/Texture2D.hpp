#pragma once

#include "Utils.hpp"

class Texture2D{
public:
    Texture2D();
    virtual ~Texture2D();
    
    bool loadTexture(const string filename, bool generateMipMaps = true);
    void bind(GLuint texUnit = 0);
    
private:
    
    GLuint mTexture;
    
};
