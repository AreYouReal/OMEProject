#include "Cache.hpp"

#include "Utils.hpp"

Cache::Cache(){

}

Cache::~Cache(){
    if(content) delete[] content;
    OME::Utils::LOG("Cache destructor!");
}



