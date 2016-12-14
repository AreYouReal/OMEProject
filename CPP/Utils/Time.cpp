#include "Time.hpp"

namespace OME {
    
    std::chrono::time_point<std::chrono::system_clock> Time::lastFrame;
    std::chrono::time_point<std::chrono::system_clock> Time::gameStart; 
    
    std::chrono::duration<double> Time::chronoDeltaTime;
    
    float Time::deltaTime(){
        return std::chrono::duration_cast<std::chrono::milliseconds>(chronoDeltaTime).count()/1000.0f;
    }
    
    void Time::init(){
        gameStart = std::chrono::system_clock::now();
        lastFrame = gameStart;
    }
    
    void Time::update(){
        chronoDeltaTime = std::chrono::system_clock::now() - lastFrame;
        lastFrame = std::chrono::system_clock::now();
    }
    
    float Time::sinceStart(){
        return std::chrono::duration_cast<std::chrono::milliseconds>(lastFrame - gameStart).count()/1000.0f;
    }
    
}
