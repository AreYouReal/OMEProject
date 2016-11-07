#pragma once

#include <string>

#include "../../3dPart/zlib/zlib.h"
#include "../../3dPart/zlib/unzip.h"
#include "../../3dPart/zlib/zutil.h"


struct Cache{
    Cache();
    ~Cache();
    
    std::string name;
    unsigned char *content  = 0;
    unsigned int size       = 0;
    unsigned int position   = 0;
};
