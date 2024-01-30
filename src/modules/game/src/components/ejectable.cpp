////////////////////////
//
//  Created on Mon Jan 29 2024
//
//  ejectable.cpp
//
////////////////////////

#include "components/ejectable.hpp"

namespace game
{
    Ejectable::Ejectable(const engine::ecs::Entity &entity, std::istream &data)
        : callable(nullptr)
    {
        std::string callable_label = std::string();

        data >> callable_label;
        callable = reinterpret_cast<void (*)()>(engine::getFunctionPattern(callable_label));
    }
}
