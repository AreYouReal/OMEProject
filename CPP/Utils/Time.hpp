#pragma once

#include <chrono>
#include <ctime>

namespace OME {
    class Time{
    public:
        
        static void init();
       
        static void update();
        
        static float deltaTime();
    
    private:
        

        static std::chrono::time_point<std::chrono::system_clock> gameStart;
        static std::chrono::time_point<std::chrono::system_clock> lastFrame;
        static std::chrono::duration<double> chronoDeltaTime;
        
    };
}


