////////////////////////
//
//  Created on Sun Sep 24 2023
//
//  collision.hpp
//
////////////////////////

#pragma once

#include "ecs/types.hpp"
#include "components/shape.hpp"
#include "ecs/world.hpp"

namespace render
{
    using CollisionBox = struct CollisionBox;
    using CollisionCallback = void(*)(CollisionBox &, CollisionBox &);

    using CollisionEntityStatus = struct CollisionEntityStatus
    {
        engine::ecs::Entity entity;
        bool collide;

        /// @brief Overload equals operator with entity
        /// @param entity entity to check
        /// @return true if there is the same entity
        bool operator==(engine::ecs::Entity entity);

        /// @brief Create a new CollisionEntityStatus with an entity
        /// @param entity entity to set
        CollisionEntityStatus(engine::ecs::Entity entity);
    };

    struct CollisionBox
    {
        engine::ecs::Entity entity;
        std::string collision_enter_name;
        std::string collision_exit_name;
        std::string collision_stay_name;
        CollisionCallback on_collision_enter;
        CollisionCallback on_collision_exit;
        CollisionCallback on_collision_stay;
        std::vector<CollisionEntityStatus> collides;

        /// @brief Container fo manager collisions
        ///        (Collision System is not required for detect collision from another entity)
        /// @param on_collision_enter callback when the collision is tarting
        /// @param on_collision_exit callback when there are collision with another entity
        /// @param on_collision_stay callback when the collision is ending
        CollisionBox(const engine::ecs::Entity &entity, std::istream &data);
    };
}
