#pragma once


#include "Utils.hpp"


namespace OME {

    
    class Game{
    public:
        static int StartUp( OME::Context * );
      
    private:
        static void initOGL(const float, const float);
        
    };
    
}
