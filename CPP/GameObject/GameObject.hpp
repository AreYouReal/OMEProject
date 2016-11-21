#pragma once

#include "Utils.hpp"
#include "IComponent.hpp"
#include "../Components/Transform/Transform.hpp"

using string = std::string;

namespace OME {
    
class GameObject{
    public:
        string mName;
        
        bool mActive;
        
        GameObject(string name = "Unnamed");
        ~GameObject();
        
        void init();
        void update();
        void draw();
        void destroy();
        
        IComponent* addComponent(up<IComponent>);
        bool removeComponent(string type);
        
        IComponent *getComponent(string type);
    
        Transform* transform();
    
    private:
        
        std::map<string, up<IComponent>> mComponents;
        
    };
}


