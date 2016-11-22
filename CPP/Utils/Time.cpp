#include "Time.hpp"

#include <sys/time.h>

namespace OME {
    
    float Time::lastFrame = -1.0f;
    float Time::deltaTime = 0.0f;
    
    
    float Time::scaleCoef = 1.0f;
    float Time::startTime = time(nullptr);
    
    unsigned int Time::micro(){
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        return (tv.tv_sec * 1000000) + tv.tv_usec;
        return -1;
    }
    
    unsigned int Time::milli(){
        struct timeval tv;
        gettimeofday( &tv, NULL );
        return tv.tv_usec / 1000 + tv.tv_sec * 1000;
        return -1;
    }
    
    void Time::update(){
        if(lastFrame < 0.0f){
            lastFrame = milli();
        }else{
            deltaTime = 1.0f/(milli() - lastFrame);
        }
    }
}
