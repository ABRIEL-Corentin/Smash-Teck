////////////////////////
//
//  Created on Wed Jan 17 2024
//
//  player.hpp
//
////////////////////////

#pragma once

#include "ecs/types.hpp"

namespace game
{
    using Player = struct Player
    {
        Player(const engine::ecs::Entity &entity, std::istream &istream);
    };
}
