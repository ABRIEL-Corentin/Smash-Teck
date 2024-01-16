////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  player_movement.cpp
//
////////////////////////

#include "ecs/world.hpp"
#include "components/player.hpp"
#include "systems/player_movement.hpp"

namespace game
{
    void playerMovement()
    {
        engine::ecs::Components<Player> &players = engine::ecs::World::getInstance().getComponents<Player>();

        for (auto player = players.begin(); player != players.end(); ++player) {
            if (!player->has_value())
                continue;


        }
    }
}
