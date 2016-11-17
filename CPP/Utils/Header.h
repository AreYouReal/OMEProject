#pragma once

namespace OME {


template<typename T>
class Singleton{
public:
    
    virtual ~Singleton(){}
    
    static T* instance(){
        if(!mInstance){
            mInstance = new T();
        }
        return mInstance;
    }
    
    static void destroy(){
        if(mInstance){
            delete mInstance;
            mInstance = nullptr;
        }
    }

protected:
    Singleton(){}
    static T* mInstance;
}

template<typename T>
T* Singletom<T>::mInstance;
    
}
