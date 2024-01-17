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
#include "systems/player_movement.hpp"
#include "events/keyboard.hpp"
#include "events/time.hpp"

#define GRAVITY 2000
#define JUMP_FORCE 1000

namespace game
{
    void playerMovement()
    {
        engine::ecs::Components<Player> &players = engine::ecs::World::getInstance().getComponents<Player>();
        engine::ecs::Components<render::Shape> &shapes = engine::ecs::World::getInstance().getComponents<render::Shape>();
        float horizontal_movement = 0;

        for (std::size_t i = 0; i < players.size(); ++i) {
            if (!players.at(i).has_value() || !shapes.at(i).has_value())
                continue;

            Player &player = players.at(i).value();
            render::Shape &shape = shapes.at(i).value();

            if (render::Keyboard::isKeyPressed(render::Keyboard::Key::Q))
                horizontal_movement = -player.horizontal_speed;

            if (render::Keyboard::isKeyPressed(render::Keyboard::Key::D))
                horizontal_movement = player.horizontal_speed;

            if (render::Keyboard::isKeyPressedAsButton(render::Keyboard::Space))
                player.vertical_velocity = -JUMP_FORCE;

            shape.move(render::math::Vector2f(horizontal_movement, player.vertical_velocity) * render::Time::getInstance().getDeltaTime());
            player.vertical_velocity += GRAVITY * render::Time::getInstance().getDeltaTime();
        }
    }
}
