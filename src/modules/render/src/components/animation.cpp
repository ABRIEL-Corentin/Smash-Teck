////////////////////////
//
//  Created on Thu Sep 21 2023
//
//  animation.cpp
//
////////////////////////

#include "components/animation.hpp"
#include "render_data.hpp"

namespace render
{
    Animation::Animation(const engine::ecs::Entity &, std::istream &data)
        : textures_ids(),
          frame_rate(0),
          timer(0),
          frame(0),
          is_playing(true)
    {
        std::string animation_label = std::string();

        data >> animation_label;
        data >> frame_rate;

        textures_ids = RenderData::getInstance().getAnimation(animation_label);
    }

    void Animation::pause()
    {
        is_playing = false;
    }

    void Animation::resume()
    {
        is_playing = true;
    }

    void Animation::reset()
    {
        is_playing = true;
        frame = 0;
    }

    void Animation::loadFromLabel(const std::string &label, float frame_rate)
    {
        reset();
        this->frame_rate = frame_rate;
        textures_ids = RenderData::getInstance().getAnimation(label);
    }

    void Animation::setFrameRate(float frame_rate)
    {
        this->frame_rate = frame_rate;
    }
}
