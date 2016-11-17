#pragma once

#include "IComponent.hpp"

namespace OME {
    class Mesh : public IComponent{
    public:
        Mesh(GameObject *const gameObject);
        virtual ~Mesh();
    };
}


