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
    enum class PlayerAnimationState
    {
        IDLE,
        RUNNING,
        JUMPING,
        ATTACK,
    };

    using Player = struct Player
    {
        float horizontal_speed;
        float vertical_velocity;
        float attack_cooldown;
        float attack_cooldown_timer;
        engine::ecs::Entity entity;
        bool double_jump;
        bool is_grounded;
        PlayerAnimationState animation_state;

        void move_to_position(const render::math::Vector2f &position);
        void move_to_position(float x, float y);

        Player(const engine::ecs::Entity &entity, std::istream &istream);
    };
}
