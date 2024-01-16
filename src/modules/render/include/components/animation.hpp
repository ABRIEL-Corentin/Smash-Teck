////////////////////////
//
//  Created on Thu Sep 21 2023
//
//  animation.hpp
//
////////////////////////

#pragma once

#include "ecs/world.hpp"

#include <vector>
#include <sstream>

namespace render
{
    using Animation = struct Animation
    {
        std::vector<std::size_t> textures_ids;
        std::string animation_label;
        float frame_rate;
        float timer;
        std::size_t frame;
        bool is_playing;

        /// @brief Stop the animation
        void pause();

        /// @brief Continue to play the animation
        void resume();

        /// @brief Restart the animation
        void reset();

        /// @brief Change to another animation
        void loadFromLabel(const std::string &label, float frame_rate);

        /// @brief Update frame rate
        /// @param frame_rate new frame rate
        void setFrameRate(float frame_rate);

        /// @brief Container for playing animations
        /// @param textures all textures to be in the animation
        /// @param frame_rate frame rate to play the animation
        Animation(const engine::ecs::Entity &entity, std::istream &data);
    };
}
