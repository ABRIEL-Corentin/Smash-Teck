////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  player_movement.cpp
//
////////////////////////

#include "ecs/world.hpp"
#include "components/player.hpp"
#include "components/shape.hpp"
#include "components/tag.hpp"
#include "systems/player_movement.hpp"
#include "events/keyboard.hpp"
#include "events/time.hpp"

#define GRAVITY 2000
#define JUMP_FORCE 1000

namespace game
{
    void move_player_parts(
        const std::string &player_tag,
        render::math::Vector2f offset,
        engine::ecs::Components<Tag> &tags,
        engine::ecs::Components<render::Shape> &shapes
    ) {
        std::string part_tag = player_tag + "_PART";

        for (std::size_t i = 0; i < tags.size(); ++i) {
            if (!tags.at(i).has_value())
                continue;

            if (shapes.size() <= i || !shapes.at(i).has_value())
                continue;

            if (tags.at(i)->tag == part_tag)
                shapes.at(i)->move(offset);
        }
    }

    void playerMovement()
    {
        engine::ecs::Components<Player> &players = engine::ecs::World::getInstance().getComponents<Player>();
        engine::ecs::Components<Tag> &tags = engine::ecs::World::getInstance().getComponents<Tag>();
        engine::ecs::Components<render::Shape> &shapes = engine::ecs::World::getInstance().getComponents<render::Shape>();
        render::math::Vector2f offset = render::math::Vector2f();

        for (std::size_t i = 0; i < players.size(); ++i) {
            if (!players.at(i).has_value())
                continue;

            if (shapes.size() <= i || !shapes.at(i).has_value())
                continue;

            if (tags.size() <= i || !tags.at(i).has_value())
                continue;

            Player &player = players.at(i).value();
            Tag &tag = tags.at(i).value();
            render::Shape &shape = shapes.at(i).value();

            if (render::Keyboard::isKeyPressed(render::Keyboard::Key::Q))
                offset.x = -player.horizontal_speed;

            if (render::Keyboard::isKeyPressed(render::Keyboard::Key::D))
                offset.x = player.horizontal_speed;

            if (render::Keyboard::isKeyPressedAsButton(render::Keyboard::Space))
                player.vertical_velocity = -JUMP_FORCE;

            offset.y = player.vertical_velocity;
            shape.move(offset * render::Time::getInstance().getDeltaTime());
            move_player_parts(tag.tag, offset * render::Time::getInstance().getDeltaTime(), tags, shapes);
            player.vertical_velocity += GRAVITY * render::Time::getInstance().getDeltaTime();
        }
    }
}
