////////////////////////
//
//  Created on Wed Jan 17 2024
//
//  player.hpp
//
////////////////////////

#pragma once

#include "math/vector2.hpp"
#include "ecs/types.hpp"

namespace game
{
    using Player = struct Player
    {
        float horizontal_speed;
        float vertical_velocity;
        engine::ecs::Entity entity;
        bool double_jump;
        bool is_grounded;

        void move_to_position(const render::math::Vector2f &position);
        void move_to_position(float x, float y);

        Player(const engine::ecs::Entity &entity, std::istream &istream);
    };
}
