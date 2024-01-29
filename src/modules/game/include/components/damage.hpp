////////////////////////
//
//  Created on Mon Jan 29 2024
//
//  damage.hpp
//
////////////////////////

#pragma once

#include "ecs/world.hpp"

namespace game
{
    using Damage = struct Damage
    {
        float damage;

        Damage(const engine::ecs::Entity &entity, std::istream &data);
    };
}
