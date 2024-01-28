////////////////////////
//
//  Created on Sun Jan 28 2024
//
//  gravity.cpp
//
////////////////////////

#include "components/gravity.hpp"

namespace game
{
    Gravity::Gravity(const engine::ecs::Entity &entity, std::istream &data)
        : vertical_velocity(0)
    { }
}
