#pragma once
#include "Utils.hpp"

struct FileContent{
    FileContent(unsigned char *contentChar, const long cSize, string cName): content(contentChar), size(cSize){}
    ~FileContent(){if(content) delete[] content; }
    
    string name;
    unsigned char *content;
    unsigned int size;
    unsigned int position = 0;

};
