////////////////////////
//
//  Created on Sun Jan 28 2024
//
//  gravity.hpp
//
////////////////////////

#pragma once

#include "ecs/world.hpp"

namespace game
{
    using Gravity = struct Gravity
    {
        float vertical_velocity;
        float horizontal_velocity;

        Gravity(const engine::ecs::Entity &entity, std::istream &data);
    };
}
