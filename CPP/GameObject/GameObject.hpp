#pragma once

#include "Utils.hpp"
#include "IComponent.hpp"

using string = std::string;

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
    bool removeComponent(IComponent::Type);
    
    IComponent *getComponent(IComponent::Type);
    
private:
    
    std::map<IComponent::Type, up<IComponent>> mComponents;

};
