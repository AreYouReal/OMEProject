#pragma once



namespace OME {
    struct Time{
        
        static float lastFrame;
        static float deltaTime;
        static float scaleCoef;
        static float startTime;
        
        static unsigned int micro();
        static unsigned int milli();
        
        static float scaledTime();
        static float sinceStart();
        
        static void update();
        
        
    };
}


