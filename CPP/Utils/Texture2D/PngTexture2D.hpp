#include "Texture2D.hpp"

#include "png.h"

class PngTexture2D : public Texture2D{
public:
    
    unsigned int byte;
    unsigned int format;
    png_byte colorType;
    
    bool loadTexture(const string filename, bool generateMipMaps = true) override;
    
    
private:
    
    unsigned char* readPNGFile(string filename);
};
