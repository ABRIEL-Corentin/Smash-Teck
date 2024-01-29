////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  player_movement.cpp
//
////////////////////////

#include "ecs/world.hpp"
#include "application.hpp"
#include "components/player.hpp"
#include "components/shape.hpp"
#include "components/tag.hpp"
#include "components/animation.hpp"
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
        engine::ecs::Components<render::Animation> &animations = engine::ecs::World::getInstance().getComponents<render::Animation>();
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

            if (animations.size() <= i || !animations.at(i).has_value())
                continue;

            Player &player = players.at(i).value();
            Tag &tag = tags.at(i).value();
            render::Animation &animation = animations.at(i).value();
            render::Shape &shape = shapes.at(i).value();

            PlayerAnimationState new_animation_state = PlayerAnimationState::IDLE;

            if (render::Keyboard::isKeyPressed(render::Keyboard::Key::Q)) {
                offset.x = -player.horizontal_speed;
                shape.setScale(-1, 1);
                new_animation_state = PlayerAnimationState::RUNNING;
            }

            if (render::Keyboard::isKeyPressed(render::Keyboard::Key::D)) {
                offset.x = player.horizontal_speed;
                shape.setScale(1, 1);
                new_animation_state = PlayerAnimationState::RUNNING;
            }

            if (render::Keyboard::isKeyPressedAsButton(render::Keyboard::Space) && (player.double_jump || player.is_grounded)) {
                player.vertical_velocity = -JUMP_FORCE;
                player.double_jump = player.is_grounded;
            }

            if (!player.is_grounded)
                new_animation_state = PlayerAnimationState::JUMPING;

            offset.y = player.vertical_velocity;
            shape.move(offset * render::Time::getInstance().getDeltaTime());

            if (render::Keyboard::isKeyPressedAsButton(render::Keyboard::Z) && !player.attack_cooldown_timer) {
                engine::Application::getInstance().loadScene({
                    "scene/attack_box.txt",
                    {
                        "1",
                        std::to_string(shape.getPosition().x + 20 * shape.getScale().x),
                        std::to_string(shape.getPosition().y),
                    },
                    nullptr
                });
                player.attack_cooldown_timer = player.attack_cooldown;
                new_animation_state = PlayerAnimationState::ATTACK;
            }

            move_player_parts(tag.tag, offset * render::Time::getInstance().getDeltaTime(), tags, shapes);
            player.vertical_velocity += GRAVITY * render::Time::getInstance().getDeltaTime();
            player.is_grounded = false;

            if (player.attack_cooldown_timer) {
                new_animation_state = PlayerAnimationState::ATTACK;
                player.attack_cooldown_timer -= render::Time::getInstance().getDeltaTime();
            }

            if (player.attack_cooldown_timer <= 0)
                player.attack_cooldown_timer = 0;

            if (new_animation_state != player.animation_state) {
                player.animation_state = new_animation_state;

                switch (new_animation_state) {
                    case PlayerAnimationState::IDLE:
                        animation.loadFromLabel("piranha_plant_idle", 10);
                        break;
                    case PlayerAnimationState::RUNNING:
                        animation.loadFromLabel("piranha_plant_running", 10);
                        break;
                    case PlayerAnimationState::JUMPING:
                        animation.loadFromLabel("piranha_plant_jump", 10);
                        break;
                    case PlayerAnimationState::ATTACK:
                        animation.loadFromLabel("piranha_plant_attack", 20);
                        break;
                    default:
                        break;
                }
            } else if (player.animation_state == PlayerAnimationState::JUMPING && animation.frame == animation.textures_ids.size() - 1)
                animation.pause();
        }
    }
}
