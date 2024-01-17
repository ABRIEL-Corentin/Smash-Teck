////////////////////////
//
//  Created on Thu Sep 21 2023
//
//  animation.cpp
//
////////////////////////

#include "systems/animation.hpp"
#include "events/time.hpp"

namespace render
{
    void animationPlayer()
    {
        engine::ecs::Components<render::Shape> &shapes = engine::ecs::World::getInstance().getComponents<render::Shape>();
        engine::ecs::Components<render::Animation> &animations = engine::ecs::World::getInstance().getComponents<render::Animation>();

        for (std::size_t i = 0; i < shapes.size(); ++i) {
            if (!shapes.at(i).has_value())
                continue;

            if (animations.size() <= i || !animations.at(i).has_value())
                continue;

            render::Shape &shape = shapes.at(i).value();
            render::Animation &animation = animations.at(i).value();

            animation.timer += Time::getInstance().getDeltaTime();

            while (animation.timer >= 1.0f / animation.frame_rate) {
                animation.timer -= 1.0f / animation.frame_rate;
                animation.frame = (animation.frame + 1) % animation.textures_ids.size();
                shape.setTexture(animation.textures_ids.at(animation.frame));
            }
        }
    }
}
