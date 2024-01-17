////////////////////////
//
//  Created on Wed Jan 17 2024
//
//  tag.cpp
//
////////////////////////

#include "components/tag.hpp"

namespace game
{
    Tag::Tag(const engine::ecs::Entity &entity, std::istream &stream)
        : tag()
    {
        stream >> tag;
    }
}
