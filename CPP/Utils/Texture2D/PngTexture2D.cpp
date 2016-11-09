#include "PngTexture2D.hpp"

bool PngTexture2D::loadTexture(const string filename, bool generateMipMaps ){
    
    data.bitsraw = readPNGFile(filename);
    
    
    
    
    return false;

}


unsigned char* PngTexture2D::readPNGFile(string filename){
    
    char header[8];
    
    png_structp pngPointer;
    png_infop   infoPointer;
    png_byte    bitDepth;
    
    int numberOfPasses;
    
    string path = OME::Utils::extractPath(getenv("FILESYSTEM"));
    
    filename = path+filename;
    
    FILE *fp = fopen(filename.c_str(), "rb");
    if(!fp){
        OME::Utils::LOG("Unable to load png file! [%s]", filename.c_str());
        return nullptr;
    }
    fread(header, 1, 8, fp);
    
    if(png_sig_cmp((png_const_bytep)header, 0, 8) ){
        return nullptr;
    }
    
    pngPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    
    if(!pngPointer){
        return nullptr;
    }
    
    infoPointer = png_create_info_struct(pngPointer);
    if(!infoPointer){
        return nullptr;
    }
    
    png_init_io(pngPointer, fp);
    png_set_sig_bytes(pngPointer, 8);
    
    png_read_info(pngPointer, infoPointer);
    
    data.width = png_get_image_width(pngPointer, infoPointer);
    data.height = png_get_image_height(pngPointer, infoPointer);
    colorType = png_get_color_type(pngPointer, infoPointer);
    bitDepth = png_get_bit_depth(pngPointer, infoPointer);
    numberOfPasses = png_set_interlace_handling(pngPointer);
    
    if(colorType == PNG_COLOR_TYPE_PALETTE){
        png_set_expand(pngPointer);
    }
    
    if(colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8){
        png_set_expand(pngPointer);
    }
    
    if(png_get_valid(pngPointer, infoPointer, PNG_INFO_tRNS)){
        png_set_expand(pngPointer);
    }
    
    if(bitDepth == 16){
        png_set_strip_16(pngPointer);
    }
    
    if(colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA){
        png_set_gray_to_rgb(pngPointer);
    }
    
    unsigned int byte = 4;
    switch (colorType) {
        case PNG_COLOR_TYPE_GRAY:
        byte = 1;
        break;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
        byte = 2;
        break;
        case PNG_COLOR_TYPE_RGB:
        byte = 3;
        break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
        byte = 4;
        break;
    }
    
    png_read_update_info(pngPointer, infoPointer);
    png_bytep *bytep;
    unsigned char* textureArray = (unsigned char *) malloc(data.width * data.height * 4);
    
    bytep = (png_bytep *) malloc(data.height * sizeof(png_bytep));
    int i = 0, n;
    while( i != data.height ){
        n = data.height - (i + 1);
        bytep[n] = textureArray + (n * data.width * byte);
        ++i;
    }
    
    png_read_image(pngPointer, bytep);
    png_read_end(pngPointer, NULL);
    png_destroy_read_struct(&pngPointer, &infoPointer, NULL);
    
    fclose(fp);
    free(bytep);
    
    return textureArray;
}
