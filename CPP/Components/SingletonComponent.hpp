#pragma once

namespace OME {


template<typename T>
class SingletonComponent{
public:
    
    virtual ~SingletonComponent(){}
    
    static T* instance(){
        if(!mInstance){
            Create();
        }
        return mInstance;
    }
    
    static void Create(){
        GameObject *go = new GameObject();
        mInstance = (T*)go->addComponent(std::move(up<T>(new T())));
    }
    
    static void destroy(){
        if(mInstance){
            delete mInstance;
            mInstance = nullptr;
        }
    }

protected:
    SingletonComponent(){}
    static T* mInstance;
};

template<typename T>
T* SingletonComponent<T>::mInstance;
    
}
