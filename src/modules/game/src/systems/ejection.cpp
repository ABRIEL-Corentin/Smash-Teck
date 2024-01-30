////////////////////////
//
//  Created on Mon Jan 29 2024
//
//  ejection.cpp
//
////////////////////////

#include "ecs/world.hpp"
#include "components/shape.hpp"
#include "components/ejectable.hpp"
#include "systems/ejection.hpp"

namespace game
{
    void ejection()
    {
        engine::ecs::Components<render::Shape> &shapes = engine::ecs::World::getInstance().getComponents<render::Shape>();
        engine::ecs::Components<Ejectable> &ejectables = engine::ecs::World::getInstance().getComponents<Ejectable>();

        for (std::size_t i = 0; i < ejectables.size(); ++i) {
            if (!ejectables.at(i).has_value())
                continue;

            if (shapes.size() <= i || !shapes.at(i).has_value())
                continue;

            if (shapes.at(i)->getPosition().y >= 2000) {
                engine::ecs::World::getInstance().destroyEntity(i);
                if (ejectables.at(i)->callable)
                    ejectables.at(i)->callable();
            }
        }
    }
}
