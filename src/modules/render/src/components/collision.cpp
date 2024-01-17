////////////////////////
//
//  Created on Sun Sep 24 2023
//
//  collision.cpp
//
////////////////////////

#include "components/collision.hpp"
#include "patterns.hpp"

namespace render
{
    CollisionEntityStatus::CollisionEntityStatus(engine::ecs::Entity entity)
        : entity(entity),
          collide(true)
    { }

    bool CollisionEntityStatus::operator==(engine::ecs::Entity entity)
    {
        return this->entity == entity;
    }

    CollisionBox::CollisionBox(const engine::ecs::Entity &entity, std::istream &data)
        : entity(entity),
          on_collision_enter(nullptr),
          on_collision_exit(nullptr),
          on_collision_stay(nullptr),
          collides()
    {
        data >> collision_enter_name;
        on_collision_enter = reinterpret_cast<CollisionCallback>(engine::getFunctionPattern(collision_enter_name));
        data >> collision_exit_name;
        on_collision_exit = reinterpret_cast<CollisionCallback>(engine::getFunctionPattern(collision_exit_name));
        data >> collision_stay_name;
        on_collision_stay = reinterpret_cast<CollisionCallback>(engine::getFunctionPattern(collision_stay_name));
    }
}
