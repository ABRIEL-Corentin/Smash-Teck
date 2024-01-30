////////////////////////
//
//  Created on Mon Jan 29 2024
//
//  ejectable.hpp
//
////////////////////////

#pragma once

#include "ecs/world.hpp"

namespace game
{
    using Ejectable = struct Ejectable
    {
        void (*callable)();

        Ejectable(const engine::ecs::Entity &entity, std::istream &data);
    };
}
