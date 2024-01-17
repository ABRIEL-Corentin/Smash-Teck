////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  player_movement.hpp
//
////////////////////////

#pragma once

#include "components/tag.hpp"

namespace game
{
    void playerMovement();
    void move_player_parts(
        const std::string &player_tag,
        render::math::Vector2f offset,
        engine::ecs::Components<Tag> &tags,
        engine::ecs::Components<render::Shape> &shapes
    );
}
