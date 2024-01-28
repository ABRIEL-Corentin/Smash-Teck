////////////////////////
//
//  Created on Sun Jan 28 2024
//
//  destroy_timer.hpp
//
////////////////////////

#pragma once

#include "ecs/world.hpp"

namespace game
{
    using DestroyTimer = struct DestroyTimer
    {
        float timer;

        DestroyTimer(const engine::ecs::Entity &entity, std::istream &data);
    };
}
