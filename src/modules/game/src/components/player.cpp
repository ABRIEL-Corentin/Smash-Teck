////////////////////////
//
//  Created on Wed Jan 17 2024
//
//  player.cpp
//
////////////////////////

#include "ecs/world.hpp"
#include "components/player.hpp"
#include "components/shape.hpp"
#include "components/tag.hpp"
#include "systems/player_movement.hpp"

namespace game
{
    Player::Player(const engine::ecs::Entity &entity, std::istream &)
        : horizontal_speed(750)
        , vertical_velocity(0)
        , entity(entity)
    { }

    void Player::move_to_position(const render::math::Vector2f &position)
    {
        move_to_position(position.x, position.y);
    }

    void Player::move_to_position(float x, float y)
    {
        engine::ecs::Component<render::Shape> &shape = engine::ecs::World::getInstance().getComponent<render::Shape>(entity);
        engine::ecs::Component<Tag> &tag = engine::ecs::World::getInstance().getComponent<Tag>(entity);

        if (!shape.has_value() || !tag.has_value())
            return;

        render::math::Vector2f offset = render::math::Vector2f(
            x - shape->getPosition().x,
            y - shape->getPosition().y
        );

        shape->move(offset);
        move_player_parts(
            tag->tag,
            offset,
            engine::ecs::World::getInstance().getComponents<Tag>(),
            engine::ecs::World::getInstance().getComponents<render::Shape>()
        );
    }
}
