#pragma once

namespace OME {


template<typename T>
class Singleton{
public:
    
    virtual ~Singleton(){}
    
    static T* instance(){
        if(!mInstance){
            Create();
        }
        return mInstance;
    }
    
    static void Create(){
        GameObject *go = new GameObject();
        mInstance = (T*)go->addComponent(up<T>(new T()));
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
};

template<typename T>
T* Singleton<T>::mInstance;
    
}
