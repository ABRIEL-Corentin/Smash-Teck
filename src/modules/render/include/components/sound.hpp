////////////////////////
//
//  Created on Wed Oct 11 2023
//
//  sound.hpp
//
////////////////////////

#pragma once

#include "ecs/world.hpp"

namespace render
{
    using Sound = struct Sound
    {
        std::size_t id;
        std::size_t sound_buffer_id;

        void play();
        void pause();
        void stop();
        bool getLoop() const;
        void setLoop(bool loop);
        float getVolume() const;
        void setVolume(float volume);

        Sound(const engine::ecs::Entity &entity, std::istream &data);

        void onDestroy();
    };
}
