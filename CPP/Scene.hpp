#pragma once

#include <vector>

#include "Singleton.hpp"
#include "Shortcuts.hpp"
#include "GameObject.hpp"

namespace OME {
    class Scene : public Singleton<Scene>{
    public:
        
        Scene();
        ~Scene();
        
        bool init();
        void update();
        void draw();
        void destroy();
        
        void addObject(up<GameObject> go);
    
    private:
        
        std::vector<up<GameObject>> mObjects;
        
    };
}
