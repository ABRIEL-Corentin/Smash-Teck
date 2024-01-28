////////////////////////
//
//  Created on Sun Jan 28 2024
//
//  destroy_timer.cpp
//
////////////////////////

#include "components/destroy_timer.hpp"

namespace game
{
    DestroyTimer::DestroyTimer(const engine::ecs::Entity &entity, std::istream &data)
        : timer(0)
    {
        data >> timer;
    }
}
