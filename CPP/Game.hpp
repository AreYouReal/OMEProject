#pragma once


#include "Utils.hpp"


namespace OME {

    
    class Game{
    public:
        static int StartUp( OME::Context * );
        
        static OME::Context *currentCtx;
      
    private:
        static void OnUpdate    (const float);
        static void OnDraw      ();
        static void OnTouch     (const int count, const int id, const int event, const int x, const int y);
        static void OnDestroy   ();        
        
        static void initOGL(const float, const float);
        

        static bool initContext(OME::Context*);
        static void initCamera();
        
    };
    
}
