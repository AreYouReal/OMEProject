#pragma once

#include "Utils.hpp"

struct TextureMemData{
    string name;
    int width;
    int height;
    unsigned char* bitsraw;
    unsigned int texID;
};


class Texture2D{
public:
    Texture2D();
    virtual ~Texture2D();
    
    virtual bool loadTexture(const string filename, bool generateMipMaps = true);
    void bind(GLuint texUnit = 0);
    
protected:
    TextureMemData data;
};
