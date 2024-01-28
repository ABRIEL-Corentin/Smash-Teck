////////////////////////
//
//  Created on Sun Jan 28 2024
//
//  gravity.cpp
//
////////////////////////

#include "components/shape.hpp"
#include "ecs/world.hpp"
#include "systems/gravity.hpp"
#include "components/gravity.hpp"
#include "events/time.hpp"

#define GRAVITY_FORCE 2000

namespace game
{
    void gravity()
    {
        engine::ecs::Components<Gravity> &gravities = engine::ecs::World::getInstance().getComponents<Gravity>();
        engine::ecs::Components<render::Shape> &shapes = engine::ecs::World::getInstance().getComponents<render::Shape>();

        for (std::size_t i = 0; i < gravities.size(); ++i) {
            if (!gravities.at(i).has_value())
                continue;

            if (shapes.size() <= i || !shapes.at(i).has_value())
                continue;

            shapes.at(i)->move(0, gravities.at(i)->vertical_velocity * render::Time::getInstance().getDeltaTime());
            gravities.at(i)->vertical_velocity += GRAVITY_FORCE * render::Time::getInstance().getDeltaTime();
        }
    }
}
