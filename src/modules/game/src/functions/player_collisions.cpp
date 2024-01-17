////////////////////////
//
//  Created on Wed Jan 17 2024
//
//  player_collisions.cpp
//
////////////////////////

#include "components/player.hpp"
#include "components/tag.hpp"
#include "functions/player_collisions.hpp"
#include "ecs/world.hpp"

namespace game
{
    static void move_player(const std::string &player_tag, render::Shape &other_shape)
    {
        engine::ecs::Components<Player> &players = engine::ecs::World::getInstance().getComponents<Player>();
        engine::ecs::Components<render::Shape> &shapes = engine::ecs::World::getInstance().getComponents<render::Shape>();

        for (std::size_t i = 0; i < players.size(); ++i) {
            if (!players.at(i).has_value())
                continue;

            if (shapes.size() <= i || !shapes.at(i).has_value())
                continue;

            players.at(i)->vertical_velocity = 0;
            players.at(i)->move_to_position({
                shapes.at(i)->getPosition().x,
                other_shape.getPosition().y - other_shape.getSize().y / 2 - shapes.at(i)->getSize().y / 2
            });
        }
    }

    void onPlayerCollisionStay(render::CollisionBox &box, render::CollisionBox &other)
    {
        engine::ecs::Component<Tag> &tag = engine::ecs::World::getInstance().getComponent<Tag>(box.entity);
        engine::ecs::Component<render::Shape> &shape = engine::ecs::World::getInstance().getComponent<render::Shape>(box.entity);
        engine::ecs::Component<Tag> &other_tag = engine::ecs::World::getInstance().getComponent<Tag>(other.entity);
        engine::ecs::Component<render::Shape> &other_shape = engine::ecs::World::getInstance().getComponent<render::Shape>(other.entity);

        if (!tag.has_value() ||
            !shape.has_value() ||
            !other_tag.has_value() ||
            !other_shape.has_value())
            return;

        if (other_tag->tag == "DOWN_PLATFORM")
            move_player(tag->tag.substr(0, tag->tag.find('_')), other_shape.value());
    }
}
