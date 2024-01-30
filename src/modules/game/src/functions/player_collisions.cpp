////////////////////////
//
//  Created on Wed Jan 17 2024
//
//  player_collisions.cpp
//
////////////////////////

#include "components/player.hpp"
#include "components/tag.hpp"
#include "components/gravity.hpp"
#include "components/damage.hpp"
#include "functions/player_collisions.hpp"
#include "ecs/world.hpp"
#include "application.hpp"

namespace game
{
    static void move_player(const std::string &player_tag, render::Shape &other_shape)
    {
        engine::ecs::Components<Player> &players = engine::ecs::World::getInstance().getComponents<Player>();
        engine::ecs::Components<render::Shape> &shapes = engine::ecs::World::getInstance().getComponents<render::Shape>();
        engine::ecs::Components<Tag> &tags = engine::ecs::World::getInstance().getComponents<Tag>();

        for (std::size_t i = 0; i < players.size(); ++i) {
            if (!players.at(i).has_value())
                continue;

            if (shapes.size() <= i || !shapes.at(i).has_value())
                continue;

            if (tags.size() <= i || !tags.at(i).has_value() || tags.at(i)->tag != player_tag)
                continue;

            players.at(i)->vertical_velocity = 0;
            players.at(i)->is_grounded = true;
            players.at(i)->double_jump = true;
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

    void onSandbagCollisionStag(render::CollisionBox &box, render::CollisionBox &other)
    {
        engine::ecs::Component<render::Shape> &shape = engine::ecs::World::getInstance().getComponent<render::Shape>(box.entity);
        engine::ecs::Component<Gravity> &gravity = engine::ecs::World::getInstance().getComponent<Gravity>(box.entity);
        engine::ecs::Component<render::Shape> &other_shape = engine::ecs::World::getInstance().getComponent<render::Shape>(other.entity);
        engine::ecs::Component<Tag> &other_tag = engine::ecs::World::getInstance().getComponent<Tag>(other.entity);

        if (!shape.has_value() || !other_tag.has_value() || !other_shape.has_value())
            return;

        if (other_tag->tag == "DOWN_PLATFORM") {
            shape->setPosition(shape->getPosition().x,
                other_shape->getPosition().y - shape->getSize().y / 2 - other_shape->getSize().y / 2
            );

            if (gravity.has_value()) {
                gravity->vertical_velocity = 0;
                gravity->horizontal_velocity = 0;
            }
        }
    }

    void onAttackCollisionStay(render::CollisionBox &box, render::CollisionBox &other)
    {
        engine::ecs::Component<render::Shape> &shape = engine::ecs::World::getInstance().getComponent<render::Shape>(box.entity);
        engine::ecs::Component<render::Shape> &other_shape = engine::ecs::World::getInstance().getComponent<render::Shape>(other.entity);
        engine::ecs::Component<Tag> &other_tag = engine::ecs::World::getInstance().getComponent<Tag>(other.entity);
        engine::ecs::Component<Gravity> &other_gravity = engine::ecs::World::getInstance().getComponent<Gravity>(other.entity);
        engine::ecs::Component<Damage> &other_damage = engine::ecs::World::getInstance().getComponent<Damage>(other.entity);

        if (!shape.has_value() ||
            !other_shape.has_value() ||
            !other_tag.has_value() ||
            !other_gravity.has_value() ||
            !other_damage.has_value())
            return;

        float direction = other_shape->getPosition().x < shape->getPosition().x ? -1 : 1;

        if (other_tag->tag == "SANDBAG") {
            other_gravity->vertical_velocity = -1500 * other_damage->damage - 200;
            other_gravity->horizontal_velocity = (500 * other_damage->damage + 100) * direction;
            other_shape->move(0, -1);
            engine::ecs::World::getInstance().destroyEntity(box.entity);
            other_damage->damage += 0.20;
        }
    }

    void spawnPlayer()
    {
        engine::Application::getInstance().loadScene({
            "./scene/player.txt",
            {"1", "(1920 / 2)", "300"}
        });
    }

    void spawnSandbag()
    {
        engine::Application::getInstance().loadScene({
            "./scene/sandbag.txt"
        });
    }
}
