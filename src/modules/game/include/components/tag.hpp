////////////////////////
//
//  Created on Wed Jan 17 2024
//
//  tag.hpp
//
////////////////////////

#pragma once

#include "ecs/types.hpp"

namespace game
{
    using Tag = struct Tag
    {
        std::string tag;

        Tag(const engine::ecs::Entity &entity, std::istream &stream);
    };
}
