////////////////////////
//
//  Created on Wed Jan 17 2024
//
//  player.cpp
//
////////////////////////

#include "ecs/world.hpp"
#include "components/player.hpp"
#include "components/shape.hpp"

namespace game
{
    Player::Player(const engine::ecs::Entity &, std::istream &)
        : horizontal_speed(750)
        , vertical_velocity(0)
    { }
}
