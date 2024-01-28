////////////////////////
//
//  Created on Sun Jan 28 2024
//
//  destroy_timer.cpp
//
////////////////////////

#include "ecs/world.hpp"
#include "systems/destroy_timer.hpp"
#include "components/destroy_timer.hpp"
#include "events/time.hpp"

namespace game
{
    void destroyTimer()
    {
        engine::ecs::Components<DestroyTimer> &timers = engine::ecs::World::getInstance().getComponents<DestroyTimer>();

        for (std::size_t i = 0; i < timers.size(); ++i) {
            if (!timers.at(i).has_value())
                continue;

            timers.at(i)->timer -= render::Time::getInstance().getDeltaTime();

            if (timers.at(i)->timer <= 0)
                engine::ecs::World::getInstance().destroyEntity(i);
        }
    }
}
